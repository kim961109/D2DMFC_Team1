#include "stdafx.h"
#include "Scene_jini.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"

#include "PlayerJini.h"
#include "Jelly.h"
#include "MonsterJini.h"
#include "Result.h"


bool g_bZoomOut_Jini = false;
bool g_bZoomIn_Jini = false;

float g_fRenderPercent = 1.0f;
float g_fScaleCount = 0.f;

float g_fScore = 0.f;
float g_fScoreKS = 0.f;
float g_fScoreKJE = 0.f;
float g_fScoreKMS = 0.f;

DWORD g_dwPlayTime = long(0);

CScene_jini::CScene_jini()
{
	m_pPlayer = nullptr;
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

	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CResult>::Create_SetPos(200.f, 100.f, 0.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYERJINI, CAbstractFactory<CPlayerJini>::Create_SetPos(1200.f, 900.f, 0.f));
	m_pPlayer = CObjMgr::Get_Instance()->Get_ListBack(OBJ_PLAYERJINI);
	
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterJini>::Create_MonsterJini(1500.f, 800.f, 0.f, 1, 3.f));
	m_pMonster1 = CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER);
	m_pMonster1->Set_Dir(-1.0f, 0.f, 0.f);
	dynamic_cast<CMonsterJini*>(m_pMonster1)->Set_Player(m_pPlayer);

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterJini>::Create_MonsterJini(2200.f, 1500.f, 0.f, 2, 4.5f));
	m_pMonster2 = CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER);
	m_pMonster2->Set_Dir(-0.4f, -0.5f, 0.f);
	dynamic_cast<CMonsterJini*>(m_pMonster2)->Set_Player(m_pPlayer);

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterJini>::Create_MonsterJini(800.f, 1000.f, 0.f, 3, 2.f));
	m_pMonster3 = CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER);
	m_pMonster3->Set_Dir(0.3f, -0.7f, 0.f);
	dynamic_cast<CMonsterJini*>(m_pMonster3)->Set_Player(m_pPlayer);
}


void CScene_jini::Update(void)
{
	//if (m_pPlayer == nullptr)
	//{
	//	//Release();
	//	//CObjMgr::Get_Instance()->Add_Object(OBJ_UI, CAbstractFactory<CResult>::Create_SetPos(200.f, 100.f, 0.f));
	//}

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

	int ListRank[4] = { (int)g_fScore, (int)g_fScoreKS, (int)g_fScoreKJE, (int)g_fScoreKMS };
	m_vecRank = { m_pPlayer, m_pMonster1, m_pMonster2, m_pMonster3 };

	Bublle_Sort(ListRank, 4);

	for (int i = 0; i < 4; ++i)
	{
		m_vecRank[i]->Set_Rank(i);
	}
}

void CScene_jini::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

	if (GetTickCount() - m_dwCollisionJelly > 300)
	{
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERJINI), CObjMgr::Get_Instance()->Get_List(OBJ_ITEM), 2);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERCHILD), CObjMgr::Get_Instance()->Get_List(OBJ_ITEM), 2);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERJINI), CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERCHILD), 1);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERJINI), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER), 3);
		CCollisionMgr::Collision_Sphere(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYERJINI), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTERCHILD), 3);

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
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYERJINI);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYERCHILD);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_ITEM);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTERCHILD);
	CObjMgr::Get_Instance()->Destroy_Instance();

	//Safe_Delete<CObj*>(m_pPlayer);
	//Safe_Delete<CObj*>(m_pMonster1);
	//Safe_Delete<CObj*>(m_pMonster2);
	//Safe_Delete<CObj*>(m_pMonster3);
}

void CScene_jini::Bublle_Sort(int _list[4], int n)
{
	int i, j, temp;
	CObj* pTemp;

	for(i = n-1; i > 0; i--)
	{
		 // 0 ~ (i-1)까지 반복
		for(j = 0; j < i; j++)
		{
			// j번째와 j+1번째의 요소가 크기 순이 아니면 교환
			if(_list[j]<_list[j+1])
			{
				temp = _list[j];
				_list[j] = _list[j+1];
				_list[j+1] = temp;

				pTemp = m_vecRank[j];
				m_vecRank[j] = m_vecRank[j + 1];
				m_vecRank[j + 1] = pTemp;
			}
		}
	}
}
