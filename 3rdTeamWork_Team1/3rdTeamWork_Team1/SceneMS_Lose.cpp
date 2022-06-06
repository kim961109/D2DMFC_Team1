#include "stdafx.h"
#include "SceneMS_Lose.h"


CSceneMS_Lose::CSceneMS_Lose()
{
}


CSceneMS_Lose::~CSceneMS_Lose()
{
}

void CSceneMS_Lose::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/음주운전.bmp", L"음주운전");

	m_pFrameKey = L"음주운전";
}

void CSceneMS_Lose::Update(void)
{
}

void CSceneMS_Lose::Late_Update(void)
{
}

void CSceneMS_Lose::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		265,	// 2,3 인자 :  복사받을 위치 X, Y
		102,
		289,				// 4,5 인자 : 복사받을 가로, 세로 길이
		295,
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		289,				// 복사할 비트맵의 가로, 세로 길이
		295,
		RGB(255, 254, 255));			// 제거하고자 하는 색상

										//Rectangle(hDC, 0, 0, WINCX, WINCY);
										//CTileMgr::Get_Instance()->Render(hDC);
}

void CSceneMS_Lose::Release(void)
{
}
