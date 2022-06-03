#include "stdafx.h"
#include "Scene_KS.h"


CScene_KS::CScene_KS()
{
}


CScene_KS::~CScene_KS()
{
	Release();
}

void CScene_KS::Initialize(void)
{
	//플레이어 생성.
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_KS>::Create_Player());
	//몬스터 생성.
	D3DXVECTOR3 vMonsterPos[5];//몬스터의 초기화 위치를 담을 벡터배열.
	vMonsterPos[0] = { 300, 200,0 };

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_KS>::Create_Monster(vMonsterPos[0]));

	//UI 생성.
	CUIMgr::Get_Instance()->Add_UI(CUIFactory<CUI_PlayerHp>::Create_UIPlayerHP());

	//배경 이미지추가.
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround_KS.bmp", L"BackGround_KS");
}

void CScene_KS::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CScene_KS::Late_Update(void)
{
	if (CObjMgr::Get_Instance()->Get_List(OBJ_BULLET).empty())
	{
		cout << "0000000000000000000000000000000000000000000000000000000000000" << endl;
	}
	CCollisionMgr::Collision_BulletKS(CObjMgr::Get_Instance()->Get_List(OBJ_BULLET), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER));
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_KS::Render(HDC hDC)
{
	//Rectangle(hDC, 0, 0, WINCX, WINCY); //테스트용 흰색 배경.

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BackGround_KS");
	BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CScene_KS::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CUIMgr::Get_Instance()->Delete_UI();
}
