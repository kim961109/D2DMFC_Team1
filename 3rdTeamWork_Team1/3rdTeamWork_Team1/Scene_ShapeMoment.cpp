#include "stdafx.h"
#include "Scene_ShapeMoment.h"


CScene_ShapeMoment::CScene_ShapeMoment()
{
}


CScene_ShapeMoment::~CScene_ShapeMoment()
{
	Release();
}

void CScene_ShapeMoment::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/ㄱ자이동.bmp", L"ㄱ자이동");

	m_pFrameKey = L"ㄱ자이동";
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerMS>::Create_SetPos(100.f,200.f,0.f));
}

void CScene_ShapeMoment::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_ShapeMoment::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_ShapeMoment::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		0,	// 2,3 인자 :  복사받을 위치 X, Y
		0,
		WINCX,				// 4,5 인자 : 복사받을 가로, 세로 길이
		WINCY,
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		801,				// 복사할 비트맵의 가로, 세로 길이
		601,
		RGB(0, 0, 0));			// 제거하고자 하는 색상

								//Rectangle(hDC, 0, 0, WINCX, WINCY);
								//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_ShapeMoment::Release(void)
{
}
