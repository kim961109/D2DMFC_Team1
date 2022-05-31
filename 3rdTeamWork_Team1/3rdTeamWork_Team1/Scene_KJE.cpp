#include "stdafx.h"
#include "Scene_KJE.h"
#include "BmpMgr.h"
#include"ObjMgr.h"
#include"PlayerKJE.h"
#include "AbstractFactory.h"


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
	CObjMgr::Get_Instance()->Add_Object(OBJ_Player, CAbstractFactory<CPlayerKJE>::Create_Player());

}

void CScene_KJE::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_KJE::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_KJE::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Scene_KJE");  //게임 시작시 버튼 뒤의 화면.
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_KJE::Release(void)
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_MyButton);// 신이 바뀔때 그 신의 객체 모두 삭제

}
