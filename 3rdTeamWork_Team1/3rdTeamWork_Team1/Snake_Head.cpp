#include "stdafx.h"
#include "Snake_Head.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Snake_Body.h"


CSnake_Head::CSnake_Head()
{
	m_bDead = false;
}

CSnake_Head::~CSnake_Head()
{
	Release();
}

void CSnake_Head::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y + 10.f, 0.f };
	m_fRadius = 10;
	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i] = m_vPoint[i];//키누를때만움직이게하려고 originpoint 만듬
	}

	m_fAngle = 0;
	m_fSpeed = 1.f;

	// 색상 랜덤 설정
	srand(unsigned int(time(NULL)));
	m_iSnakeColorR = rand() % 256;
	m_iSnakeColorG = rand() % 256;
	m_iSnakeColorB = rand() % 256;
}

int CSnake_Head::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	if (GetTickCount() - m_dKeyInput > 300)
	{
		Key_Input();
	}

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= { 400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	m_tRect.left = m_tInfo.vPos.x - 10.f;
	m_tRect.top = m_tInfo.vPos.y - 10.f;
	m_tRect.right = m_tInfo.vPos.x + 10.f;
	m_tRect.bottom = m_tInfo.vPos.y + 10.f;

	return 0;
}

void CSnake_Head::Late_Update(void)
{
}

void CSnake_Head::Render(HDC hDC)
{
	//MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	/*for (int i = 0; i < 4; ++i)
	{

	LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

	if (i > 1)
	continue;

	Ellipse(hDC,
	(int)m_vPoint[i].x - 5,
	(int)m_vPoint[i].y - 5,
	(int)m_vPoint[i].x + 5,
	(int)m_vPoint[i].y + 5);

	}
	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);*/
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iSnakeColorR, m_iSnakeColorG, m_iSnakeColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iSnakeColorR, m_iSnakeColorG, m_iSnakeColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	//Ellipse(hDC,

	//int(m_vPoint[0].x),
	//int(m_vPoint[1].y),
	//int(m_vPoint[2].x),
	//int(m_vPoint[3].y));

	Ellipse(hDC,
		int(m_tInfo.vPos.x - 10.f),
		int(m_tInfo.vPos.y - 10.f),
		int(m_tInfo.vPos.x + 10.f),
		int(m_tInfo.vPos.y + 10.f));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

}

void CSnake_Head::Release(void)
{
}

void CSnake_Head::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
	}

	if (GetAsyncKeyState('S'))
	{
	}

	if (GetAsyncKeyState(VK_UP))
	{

	}
	if (GetAsyncKeyState(VK_DOWN))
	{
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_fAngle -= D3DXToRadian(3.f);
		//m_dKeyInput = GetTickCount();
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_fAngle += D3DXToRadian(3.f);
		//m_dKeyInput = GetTickCount();
	}
}
void CSnake_Head::GrowUp()
{	//첫번째몸통은 머리뒤에

	/*D3DXVECTOR3 m_vNewPos;
	if (CObjMgr::Get_Instance()->Get_List(OBJ_SNAKEBODY).empty())//
	{
		m_vNewPos = m_tInfo.vPos - m_tInfo.vDir * m_fRadius * 2.0f;*/

		D3DXVECTOR3 m_vNewPos;
	if (CObjMgr::Get_Instance()->Get_List(OBJ_SNAKEBODY).empty())//
	{
		m_vNewPos = m_tInfo.vPos - m_tInfo.vDir * m_fRadius * 2.0f;

		CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKEBODY,
		CAbstractFactory<CSnake_Body>::Create_SetPos(m_vNewPos.x, m_vNewPos.y, 0.f));
		m_vecBody.push_back(CObjMgr::Get_Instance()->Get_ListBack(OBJ_SNAKEBODY));
	}
	//두번째부터는 앞에꺼뒤에
	else 
	{	
		m_FrontBody = CObjMgr::Get_Instance()->Get_ListBack(OBJ_SNAKEBODY);
		m_tFrontBody = m_FrontBody->Get_Info();
		m_vNewPos = m_tFrontBody.vPos - m_tFrontBody.vDir * m_fRadius * 2.f;

		CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKEBODY,
			CAbstractFactory<CSnake_Body>::Create_SetPos(m_vNewPos.x, m_vNewPos.y, 0.f));
		m_vecBody.push_back(CObjMgr::Get_Instance()->Get_ListBack(OBJ_SNAKEBODY));

	}
	/*//두번째부터는 앞에꺼뒤에
	else
	{
		m_FrontBody = CObjMgr::Get_Instance()->Get_ListBack(OBJ_SNAKEBODY);
		m_tFrontBody = m_FrontBody->Get_Info();
		m_vNewPos = m_tFrontBody.vPos - m_tFrontBody.vDir * m_fRadius * 2.f;

		CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKEBODY,
			CAbstractFactory<CSnake_Body>::Create_SetPos(m_vNewPos.x, m_vNewPos.y, 0.f));
		m_vecBody.push_back(CObjMgr::Get_Instance()->Get_ListBack(OBJ_SNAKEBODY));*/

	}
}

