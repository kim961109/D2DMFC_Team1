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
	CObjMgr::Get_Instance()->Add_Object(OBJ_Player, CAbstractFactory<CPlayer_KS>::Create_Player());
}

void CScene_KS::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_KS::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_KS::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_KS::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_Player);
}
