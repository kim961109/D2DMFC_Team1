#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/stardewPanorama.bmp", L"stardewPanorama"); //Back 버퍼에 해당하는 그림을 추가를 해야한다.

	CSceneMgr::Get_Instance()->Scene_Change(SC_JINI);


#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG

}

void CMainGame::Update(void)
{
	//CScrollMgr::Get_Instance()->Scroll_Lock(); //필요시 스크롤락 켜기.
	CSceneMgr::Get_Instance()->Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();// 스크롤 락.
	Reset_Scene();
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stardewPanorama"); // Back 버퍼에 그릴 그림

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hMemDC); // 백 버퍼에다가 그림을 그린다


#ifdef _DEBUG
	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

#endif // _DEBUG
}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG


	CObjMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::Reset_Scene(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_0))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MAIN);
	}
}
