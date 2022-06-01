#include "stdafx.h"
#include "PlayerJini.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CPlayerJini::CPlayerJini()
{
}


CPlayerJini::~CPlayerJini()
{
	Release();
}

void CPlayerJini::Initialize(void)
{
	m_tInfo.vPos	= { 400.f, 300.f, 0.f };
	m_tInfo.vDir	= { 1.f, 0.f, 0.f };
	m_vDirLocal		= { 1.f, 0.f, 0.f };

	m_tInfo.vLook	= { 1.f, 0.f, 0.f };
	m_fSpeed		= 2.f;
	m_fAngle		= 0.f;
	m_fScale		= 1.5f;
	//m_fEllipse		= 50.f;

	m_vBodyLocal[0] = { -50.f, 0.f, 0.f }; //left
	m_vBodyLocal[1] = { 0.f, -50.f, 0.f }; //top
	m_vBodyLocal[2] = { 50.f, 0.f, 0.f }; //right
	m_vBodyLocal[3] = { 0.f, 50.f, 0.f }; //bottom

	// ���� ���� ����
	srand(unsigned int(time(NULL)));
	m_iPlayerColorR = rand() % 256;
	m_iPlayerColorG = rand() % 256;
	m_iPlayerColorB = rand() % 256;

	m_strName = "��������";
	m_strTag = "�θ�"; 
}

void CPlayerJini::Update(void)
{
	// ����
	Key_Input();

	m_fSpeed = m_fScale * 3 / (m_fScale * m_fScale) ;

	// ���콺 ���⿬��
	m_vDirLocal = ::Get_Mouse() - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_vDirLocal);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_vLookLocal);
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
	m_fAngle = acosf(fDot);

	if (m_tInfo.vPos.y < Get_Mouse().y)
		m_fAngle = 2.f * D3DX_PI - m_fAngle;

	// ���콺 ���� �̵�
	m_tInfo.vPos.x += m_tInfo.vDir.x * m_fSpeed;
	m_tInfo.vPos.y += m_tInfo.vDir.y * m_fSpeed;

	// ������� �����
	D3DXMATRIX		matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// ������� ����
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vBody[i], &m_vBodyLocal[i], &m_tInfo.matWorld);
	}
}

void CPlayerJini::Late_Update(void)
{
}

void CPlayerJini::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Ellipse(hDC,
		int(m_vBody[0].x),
		int(m_vBody[1].y),
		int(m_vBody[2].x),
		int(m_vBody[3].y));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	// ���� �׸���
	//MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	//LineTo(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y - 50.f);
}

void CPlayerJini::Release(void)
{
}

// ����
void CPlayerJini::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		Attack();

		// �Լ��� ���� ������
		// ���� ũ�⸦ ������ ������
		//m_fScale *= 0.5;

		// �н� ���� �� ũ�� ����
		//CObjMgr::Get_Instance()->Add_Object(OBJ_Player, CAbsractFactory<CPlayer>::Create(0.f, 0.f, 0.f)); // (���콺��������), Pos ������ ���� ������ŭ.
		//CObjMgr::Get_Instance()->Get_ListBack(OBJ_Player)->Set_Scale(m_fScale);
		//CObjMgr::Get_Instance()->Get_ListBack(OBJ_Player)->Set_Tag("�ڽ�");

		// 
	}
}

// ����
void CPlayerJini::Attack()
{
	m_fScale *= 0.5;

	CObjMgr::Get_Instance()->Add_Object(OBJ_Player, CAbstractFactory<CPlayerJini>::Create_SetPos(m_tInfo.vPos.x + 50.f, m_tInfo.vPos.y + 50.f, 0.f)); // (���콺��������), Pos ������ ���� ������ŭ.
	dynamic_cast<CPlayerJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_Player))->Set_Scale(m_fScale);
	dynamic_cast<CPlayerJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_Player))->Set_Tag("�ڽ�");
}

