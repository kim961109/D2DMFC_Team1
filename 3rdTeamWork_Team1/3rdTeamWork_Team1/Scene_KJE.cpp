#include "stdafx.h"
#include "Scene_KJE.h"
#include "BmpMgr.h"
#include"ObjMgr.h"
#include"Snake_Head.h"
#include "AbstractFactory.h"
#include"TileMgr.h"


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
	CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKE, CAbstractFactory<CSnake_Head>::Create(300.f, 400.f, 0.f));

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
