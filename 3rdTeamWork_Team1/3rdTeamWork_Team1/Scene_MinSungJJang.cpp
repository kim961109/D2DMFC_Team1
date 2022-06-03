#include "stdafx.h"
#include "Scene_MinSungJJang.h"



CScene_MinSungJJang::CScene_MinSungJJang()
{
}


CScene_MinSungJJang::~CScene_MinSungJJang()
{
	Release();
}

void CScene_MinSungJJang::Initialize(void)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerMS>::Create_Player());
}

void CScene_MinSungJJang::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_MinSungJJang::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CScene_MinSungJJang::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_MinSungJJang::Release(void)
{
}
