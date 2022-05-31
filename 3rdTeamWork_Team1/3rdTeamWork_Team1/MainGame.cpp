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

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/stardewPanorama.bmp", L"stardewPanorama"); //Back Î≤ÑÌçº???¥Îãπ?òÎäî Í∑∏Î¶º??Ï∂îÍ?Î•??¥Ïïº?úÎã§.

	CSceneMgr::Get_Instance()->Scene_Change(SC_Main);
}

void CMainGame::Update(void)
{
	//CScrollMgr::Get_Instance()->Scroll_Lock(); //?§ÌÅ¨Î°??ΩÏ? ?òÏ§ë???ÑÏöî???¨Ïö©.
	CSceneMgr::Get_Instance()->Update();

}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stardewPanorama"); // Back Î≤ÑÌçº??Í∑∏Î¶¥ Í∑∏Î¶º

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hMemDC); // Î∞?Î≤ÑÌçº?êÎã§Í∞Ä Í∑∏Î¶º??Í∑∏Î¶∞??


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
	CObjMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	CBmpMgr::Get_Instance()->Destroy_Instance();
	CScrollMgr::Get_Instance()->Destroy_Instance();
	CKeyMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}
