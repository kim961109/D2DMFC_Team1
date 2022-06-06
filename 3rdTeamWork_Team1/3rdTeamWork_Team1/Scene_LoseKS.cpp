#include "stdafx.h"
#include "Scene_LoseKS.h"


CScene_LoseKS::CScene_LoseKS()
{
}


CScene_LoseKS::~CScene_LoseKS()
{
}

void CScene_LoseKS::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/lose.bmp", L"lose");
}

void CScene_LoseKS::Update(void)
{
}

void CScene_LoseKS::Late_Update(void)
{
}

void CScene_LoseKS::Render(HDC hDC)
{
	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"lose");
	BitBlt(hDC, 300, 275, 200, 50, hGroundMemDC, 0, 0, SRCCOPY);
}

void CScene_LoseKS::Release(void)
{
}
