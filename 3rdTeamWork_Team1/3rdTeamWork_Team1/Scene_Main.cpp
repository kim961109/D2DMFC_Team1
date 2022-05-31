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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/stardewPanorama.bmp", L"stardewPanorama");//���� ���� ȭ��.


}

void CScene_Main::Update(void)
{
	CObjMgr::Get_Instance()->Update();

	// Ű �Է��� �޾Ƽ� �ε��� ��(����)���� ��ȯ.
	Key_Input();
}

void CScene_Main::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_Main::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"stardewPanorama");  //���� ���۽� ��ư ���� ȭ��.
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_Main::Release(void)
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_MyButton);// ���� �ٲ� �� ���� ��ü ��� ����
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
