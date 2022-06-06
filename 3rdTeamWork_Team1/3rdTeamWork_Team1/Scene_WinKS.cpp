#include "stdafx.h"
#include "Scene_WinKS.h"


CScene_WinKS::CScene_WinKS()
{
}


CScene_WinKS::~CScene_WinKS()
{
	Release();
}

void CScene_WinKS::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/win.bmp", L"win");
}

void CScene_WinKS::Update(void)
{
}

void CScene_WinKS::Late_Update(void)
{
}

void CScene_WinKS::Render(HDC hDC)
{
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"win");
	BitBlt(hDC, 300, 275, 200, 50, hGroundMemDC, 0, 0, SRCCOPY);
}

void CScene_WinKS::Release(void)
{
}
