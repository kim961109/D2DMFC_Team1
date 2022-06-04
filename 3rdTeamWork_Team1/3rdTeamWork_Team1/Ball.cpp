#include "stdafx.h"
#include "Ball.h"


CBall::CBall()
{
}

CBall::CBall(D3DXVECTOR3 _vPos)
	:m_fAngle(0.f), m_bMove(false)
{
	m_tInfo.vPos = _vPos;
}


CBall::~CBall()
{
	Release();
}

void CBall::Initialize(void)
{
	m_tObjInfo.fCX = 30.f;
	m_tObjInfo.fCY = 30.f;

	m_vFirstPos = { 0.f,0.f,0.f };//���� ��ǥ.
	m_vCurPos = m_vFirstPos;
	m_vMoveDir = { 0.f,0.f,0.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ball.bmp", L"Ball");
}

int CBall::Update(void)
{
	m_vCurPos = m_vFirstPos;

	m_fAngle += float(D3DX_PI / 6);

	if (m_bMove == true)
	{
		D3DXVECTOR3 m_vFriction = m_vMoveDir;// ������ ���� ���ӽ�ų ����.
		D3DXVec3Normalize(&m_vFriction, &m_vFriction);//���� ������ ����ȭ
		m_tInfo.vPos -= 3.f * m_vMoveDir;// ���� ������.
		m_vMoveDir -= 0.0015f * m_vFriction; // ����
		if (D3DXVec3Length(&m_vMoveDir) < 0.01f)// ���� ������ �ӵ��� ��������� �۾����� �����.
		{
			m_bMove = false;
		}
	}

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	
	D3DXVec3TransformCoord(&m_vCurPos, &m_vCurPos, &m_tInfo.matWorld);
	
	cout << m_tInfo.vPos.x << "\t" << m_tInfo.vPos.y << endl;

	Update_CollisionPos();
	return OBJ_NOEVENT;
}

void CBall::Late_Update(void)
{
}

void CBall::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ball");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tInfo.vPos.x - 15.f),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tInfo.vPos.y - 15.f),
		int(30.f),				// 4,5 ���� : ������� ����, ���� ����
		int(30.f),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		int(30.f),				// ������ ��Ʈ���� ����, ���� ����
		int(30.f),
		RGB(255, 255, 255));			// �����ϰ��� �ϴ� ����
}

void CBall::Release(void)
{
}

void CBall::Update_CollisionPos(void)
{
	m_tObjInfo.fX = m_tInfo.vPos.x;
	m_tObjInfo.fY = m_tInfo.vPos.y;
}

void CBall::Reset_Ball(void)
{
	m_bMove = false;
	m_vMoveDir = { 0.f,0.f,0.f };
	m_tInfo.vPos = { 230.f, 300.f, 0.f };
}
