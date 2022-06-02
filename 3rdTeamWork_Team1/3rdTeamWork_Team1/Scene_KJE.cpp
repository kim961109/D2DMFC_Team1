#include "stdafx.h"
#include "Scene_KJE.h"
#include "BmpMgr.h"
#include"ObjMgr.h"
#include"Snake_Head.h"
#include"Snake_Body.h"
#include "AbstractFactory.h"
#include"TileMgr.h"
#include"Apple.h"
#include"CollisionMgr.h"

CScene_KJE::CScene_KJE()
{
}


CScene_KJE::~CScene_KJE()
{
	Release();
}

void CScene_KJE::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene_KJE.bmp", L"Scene_KJE");
	CTileMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKE, CAbstractFactory<CSnake_Head>::Create_SetPos(300.f, 400.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKE, CAbstractFactory<CSnake_Body>::Create_SetPos(300.f, 425.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKE, CAbstractFactory<CSnake_Body>::Create_SetPos(300.f, 450.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_Item, CAbstractFactory<CApple>::Create(300.f, 400.f));
	m_SnakeList = CObjMgr::Get_Instance()->Get_List(OBJ_SNAKE);
	m_AppleList = CObjMgr::Get_Instance()->Get_List(OBJ_Item);
}

void CScene_KJE::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();

}

void CScene_KJE::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CCollisionMgr::Collision_Snake_Apple(m_SnakeList,m_AppleList);

}

void CScene_KJE::Render(HDC hDC)
{
	
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Scene_KJE");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_KJE::Release(void)
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_MyButton);// 신이 바뀔때 그 신의 객체 모두 삭제

}
