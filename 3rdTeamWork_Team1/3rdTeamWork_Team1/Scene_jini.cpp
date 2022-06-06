#include "stdafx.h"
#include "Scene_jini.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"

#include "PlayerJini.h"
#include "Jelly.h"
#include "MonsterJini.h"


bool g_bZoomOut_Jini = false;
bool g_bZoomIn_Jini = false;

float g_fRenderPercent = 1.0f;
float g_fScaleCount = 0.f;

float g_fScore = 0.f;

CScene_jini::CScene_jini()
{
}

CScene_jini::~CScene_jini()
{
	Release();
}

void CScene_jini::Initialize(void)
{
	// 여기부터
	m_dwJellyCreate = GetTickCount();
	m_dwJellyCreate2 = GetTickCount();
	m_dwCollisionJelly = GetTickCount() - long(1000);

	m_pPlayer = CAbstractFactory<CPlayerJini>::Create_SetPos(1200.f, 900.f, 0.f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, m_pPlayer);

	
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterJini>::Create_SetPos(1500.f, 800.f, 0.f));
	CObj* m_pMonster = CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER);
	m_pMonster->Set_Dir(-1.0f, 0.f, 0.f);
	dynamic_cast<CMonsterJini*>(m_pMonster)->Set_Player(m_pPlayer);
}


void CScene_jini::Update(void)
{
	if (GetTickCount() - m_dwJellyCreate > 500)
	{
		srand(unsigned int(time(NULL)));
		float m_fPosXRandom = float(rand() * rand() % 800 + 800);
		float m_fPosYRandom = float(rand() % 600 + 600);

		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom, m_fPosYRandom, 0.f));
		m_dwJellyCreate = GetTickCount();
	}

	if (GetTickCount() - m_dwJellyCreate2 > 200)
	{
		srand(unsigned int(time(NULL)));
		float m_fPosXRandom2 = float(rand() * rand() % 2350 + 10);
		float m_fPosYRandom2 = float(rand() % 1750 + 10);

		CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom2, m_fPosYRandom2, 0.f));
		m_dwJellyCreate2 = GetTickCount();
	}

	CObjMgr::Get_Instance()->Update();
}

void CScene_jini::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (GetTickCount() - m_dwCollisionJelly > 300)
	{
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_List(OBJ_ITEM), 2);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERCHILD), CObjMgr::Get_Instance()->Get_List(OBJ_ITEM), 2);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERCHILD), 1);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER), 3);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTERCHILD), 3);

		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERCHILD), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER), 3);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_List(OBJ_ITEM), 6);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTERCHILD), 7);

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
	Rectangle(hDC, WINCX - JINIMAPCX, WINCY - JINIMAPCY, WINCX, WINCY);
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
