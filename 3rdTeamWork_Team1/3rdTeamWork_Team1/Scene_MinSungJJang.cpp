#include "stdafx.h"
#include "Scene_MinSungJJang.h"
#include "TileMgr.h"



CScene_MinSungJJang::CScene_MinSungJJang()
{
}


CScene_MinSungJJang::~CScene_MinSungJJang()
{
	Release();
}

void CScene_MinSungJJang::Initialize(void)
{
	m_iLoseCount = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/경사로.bmp", L"경사로");

	m_pFrameKey = L"경사로";
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerMS>::Create_PlayerMS(200.f,100.f,0.f));
	//CTileMgr::Get_Instance()->Initialize();
}

void CScene_MinSungJJang::Update(void)
{
	//CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CScene_MinSungJJang::Late_Update(void)
{
	//CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	Reset();
	Change_Rail();
	LoseCount();
}

void CScene_MinSungJJang::Render(HDC hDC)
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
		800,				// 복사할 비트맵의 가로, 세로 길이
		600,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	//Rectangle(hDC, 0, 0, WINCX, WINCY);
	//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

}

void CScene_MinSungJJang::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	//CTileMgr::Get_Instance()->Release();
}

void CScene_MinSungJJang::Key_Input()
{
	
}

void CScene_MinSungJJang::Change_Rail(void)
{
	if ((CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_Info().vPos.x >= 750.f)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_KMS2);
	}
}

void CScene_MinSungJJang::Reset(void)
{
	float m_fYY = (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_Info().vPos.y;
	if ((m_fYY < 110) || (m_fYY > 205))
	{
		static_cast<CPlayerMS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Set_PlayerMSPos({ 100.f,130.f,0.f });
		m_iLoseCount += 1;
	}
}

void CScene_MinSungJJang::LoseCount()
{
	if (m_iLoseCount >= 10)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MSLOSE);
	}
}
