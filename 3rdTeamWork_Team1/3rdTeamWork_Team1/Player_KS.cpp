#include "stdafx.h"
#include "Player_KS.h"


CPlayer_KS::CPlayer_KS()
{
}


CPlayer_KS::~CPlayer_KS()
{
	Release();
}

void CPlayer_KS::Initialize(void)
{
	m_iHp = 100;

	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fSpeed = 5.f;
	m_fGunAngle = 0.f;
	m_fBodyAngle = 0.f;
	m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_vGunPoint[0] = { m_tInfo.vPos.x, m_tInfo.vPos.y - 5.f, 0.f };
	m_vGunPoint[1] = { m_tInfo.vPos.x + 40.f, m_tInfo.vPos.y - 5.f, 0.f };
	m_vGunPoint[2] = { m_tInfo.vPos.x + 40.f, m_tInfo.vPos.y + 5.f, 0.f };
	m_vGunPoint[3] = { m_tInfo.vPos.x, m_tInfo.vPos.y + 5.f, 0.f };

	m_vBodyPoint[0] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - 20.f , 0.f };
	m_vBodyPoint[1] = { m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y - 20.f , 0.f };
	m_vBodyPoint[2] = { m_tInfo.vPos.x + 20.f, m_tInfo.vPos.y + 20.f , 0.f };
	m_vBodyPoint[3] = { m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y + 20.f , 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginGunPoint[i] = m_vGunPoint[i];
		m_vOriginBodyPoint[i] = m_vBodyPoint[i];//���� ���� ��ǥ�� ����ص���.
	}
}

void CPlayer_KS::Update(void)
{
	//�ѱ��� �ٶ󺸴� ���������� ������ ����.
	Change_GunAngle();

	Key_Input();

	D3DXMATRIX		matScale, matRotZ, matRotBodyZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fGunAngle);//�ѱ��� ȸ��.
	D3DXMatrixRotationZ(&matRotBodyZ, m_fBodyAngle);//��ü�� ȸ��.
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;//�ѱ��� ���庯ȯ.
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vGunPoint[i], &m_vGunPoint[i], &m_tInfo.matWorld);
	}

	m_tInfo.matWorld = matScale * matRotBodyZ * matTrans;//��ü�� ���庯ȯ.
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vBodyPoint[i], &m_vBodyPoint[i], &m_tInfo.matWorld);
	}

	Key_Shoot();// ���⼭ �Ѿ� ����.

#ifdef _DEBUG

	//system("cls");
	cout << "�÷��̾� DIR��ǥ : " << m_tInfo.vDir.x << "\t" << m_tInfo.vDir.y << "\t" << m_tInfo.vDir.z << endl;
	cout << "�÷��̾� POS��ǥ : " << m_tInfo.vPos.x << "\t" << m_tInfo.vPos.y << "\t" << m_tInfo.vPos.z << endl;
	cout << "���콺 POS��ǥ : " << ::Get_Mouse().x << "\t" << ::Get_Mouse().y << "\t" << ::Get_Mouse().z << endl;

#endif // _DEBUG
}

void CPlayer_KS::Late_Update(void)
{
}

void CPlayer_KS::Render(HDC hDC)
{
	//��ü
	//Ellipse(hDC,
	//	(int)(m_vBodyPoint[0].x) ,
	//	(int)(m_vBodyPoint[0].y) ,
	//	(int)(m_vBodyPoint[2].x) ,
	//	(int)(m_vBodyPoint[2].y));//���븸 ǥ��

	//��ü
	MoveToEx(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vBodyPoint[i].x, (int)m_vBodyPoint[i].y);
	}
	LineTo(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y);

	//�ѹ���.
	MoveToEx(hDC, (int)m_vGunPoint[0].x, (int)m_vGunPoint[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vGunPoint[i].x, (int)m_vGunPoint[i].y);
	}
	LineTo(hDC, (int)m_vGunPoint[0].x, (int)m_vGunPoint[0].y);



	//���� ��ǥ�� ��� �ʱ�ȭ.
	for (int i = 0; i < 4; ++i)
	{
		m_vBodyPoint[i] = m_vOriginBodyPoint[i];

		m_vBodyPoint[i] -= { 400.f, 300.f, 0.f };

		m_vGunPoint[i] = m_vOriginGunPoint[i];

		m_vGunPoint[i] -= { 400.f, 300.f, 0.f };
	}
}

void CPlayer_KS::Release(void)
{
}

void CPlayer_KS::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos.y -= 1.f * m_fSpeed;
	}
	if (GetAsyncKeyState('S'))
	{
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos.y += 1.f * m_fSpeed;
	}
	if (GetAsyncKeyState('A'))
	{
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos.x -= 1.f * m_fSpeed;
	}
	if (GetAsyncKeyState('D'))
	{
		//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos.x += 1.f * m_fSpeed;
	}

}

void CPlayer_KS::Key_Shoot(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_Bullet, CAbstractFactory<CBullet_KS>::Create_Bullet(m_fGunAngle, m_vGunPoint[1], m_vGunPoint[2]));
	}
}

void CPlayer_KS::Change_GunAngle(void)
{
	m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;//�ѱ��� �ٶ������ ����.

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	m_fGunAngle = acosf(fDot);

	if (m_tInfo.vPos.y > Get_Mouse().y)
		m_fGunAngle = 2.f * D3DX_PI - m_fGunAngle;
}
