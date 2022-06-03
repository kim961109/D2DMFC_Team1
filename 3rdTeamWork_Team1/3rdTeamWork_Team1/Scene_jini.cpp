#include "stdafx.h"
#include "Scene_jini.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"

#include "PlayerJini.h"
#include "Jelly.h"

CScene_jini::CScene_jini()
{
}

CScene_jini::~CScene_jini()
{
}

void CScene_jini::Initialize(void)
{
	// 여기부터
	m_dwJellyCreate = GetTickCount();
	m_dwJellyCreate2 = GetTickCount();
	m_dwCollisionJelly = GetTickCount() - long(1000);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerJini>::Create_SetPos(1200.f, 900.f, 0.f));
	// 여기까지

	//for (int i = 0; i < 1000; ++i)
	//{
	//srand(unsigned int(time(NULL)));
	//float m_fPosXRandom2 = float(rand() * rand() % 2350 + 10);
	//float m_fPosYRandom2 = float(rand() * (int)m_fPosXRandom2 % 1750 + 10);

	//CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom2, m_fPosYRandom2, 0.f));
	//}

	//for (int i = 0; i < 20; ++i)
	//{
	//	srand(unsigned int(time(NULL)));
	//	float m_fPosXRandom = float((rand() * rand()) % 800 + 800);
	//	float m_fPosYRandom = float((rand() * (int)m_fPosXRandom) % 600 + 600);

	//	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom, m_fPosYRandom, 0.f));
	//}
	
}


void CScene_jini::Update(void)
{
	srand(unsigned int(time(NULL)));
	float m_fPosXRandom = float(rand() * rand() % 800 + 800);
	float m_fPosYRandom = float(rand() % 600 + 600);

	if (GetTickCount() - m_dwJellyCreate > 500)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom, m_fPosYRandom, 0.f));
		m_dwJellyCreate = GetTickCount();
	}

	srand(unsigned int(time(NULL)));
	float m_fPosXRandom2 = float(rand() * rand() % 2350 + 10);
	float m_fPosYRandom2 = float(rand() % 1750 + 10);

	if (GetTickCount() - m_dwJellyCreate2 > 100)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom2, m_fPosYRandom2, 0.f));
		m_dwJellyCreate2 = GetTickCount();
	}

	CObjMgr::Get_Instance()->Update();
}

void CScene_jini::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (GetTickCount() - m_dwCollisionJelly > 400)
	{
	CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_List(OBJ_ITEM), 2);
	CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERCHILD), CObjMgr::Get_Instance()->Get_List(OBJ_ITEM), 2);

	CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERCHILD), 1);

	m_dwCollisionJelly = GetTickCount();
	}
}

void CScene_jini::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 10, 17));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, 0.f + iScrollX, 0.f + iScrollY, 2400.f + iScrollX, 1800.f + iScrollY);

	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);
	Rectangle(hDC, WINCX - JINIMAPCX , WINCY - JINIMAPCY, WINCX , WINCY );
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_jini::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
}
