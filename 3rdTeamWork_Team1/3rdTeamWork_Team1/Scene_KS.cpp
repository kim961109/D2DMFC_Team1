#include "stdafx.h"
#include "Scene_KS.h"


CScene_KS::CScene_KS()
{
}


CScene_KS::~CScene_KS()
{
	Release();
}

void CScene_KS::Initialize(void)
{
	//敲饭捞绢 积己.
	CObjMgr::Get_Instance()->Add_Object(OBJ_Player, CAbstractFactory<CPlayer_KS>::Create_Player());

	//UI 积己.
	CUIMgr::Get_Instance()->Add_UI(CUIFactory<CUI_PlayerHp>::Create_UIPlayerHP());
}

void CScene_KS::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
}

void CScene_KS::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_KS::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(hDC);
	CUIMgr::Get_Instance()->Render(hDC);
}

void CScene_KS::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_Player);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_Bullet);
	CUIMgr::Get_Instance()->Delete_UI();
}
