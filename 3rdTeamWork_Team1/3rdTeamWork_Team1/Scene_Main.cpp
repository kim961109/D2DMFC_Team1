#include "stdafx.h"
#include "Scene_Main.h"


CScene_Main::CScene_Main()
{
}


CScene_Main::~CScene_Main()
{
	Release();
}

void CScene_Main::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/stardewPanorama.bmp", L"stardewPanorama");//메인 게임 화면.


}

void CScene_Main::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	// 키 입력을 받아서 부동한 씬(게임)으로 전환.
	Key_Input();
}

void CScene_Main::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_Main::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stardewPanorama");  //게임 시작시 버튼 뒤의 화면.
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_Main::Release(void)
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_MyButton);// 신이 바뀔때 그 신의 객체 모두 삭제
}

void CScene_Main::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_jini);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MinSungJJang);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_KJE);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_KS);
	}
}
