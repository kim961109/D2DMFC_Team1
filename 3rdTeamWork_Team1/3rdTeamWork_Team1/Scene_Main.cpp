#include "stdafx.h"
#include "Scene_Main.h"
#include "AbstractFactory.h"

CScene_Main::CScene_Main()
{
}


CScene_Main::~CScene_Main()
{
	Release();
}

void CScene_Main::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MainGame.bmp", L"MainGame");//메인 게임 화면.

	CObjMgr::Get_Instance()->Add_Object(OBJ_BALL, CAbstractFactory<CBall>::Create_Ball({ 230.f, (WINCY >> 1), 0.f }));
	CObjMgr::Get_Instance()->Add_Object(OBJ_STICK, CAbstractFactory<CStick>::Create_Stick());

	//충돌체 생성.
	CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 120.f, 280.f,10.f));//상좌
	CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 475.f, 280.f, 10.f));//하좌
	CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CObj_Collision>::Create_CollisionKS(580.f, 120.f, 280.f, 10.f));//상우
	CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CObj_Collision>::Create_CollisionKS(580.f, 475.f, 280.f, 10.f));//하우
	CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CObj_Collision>::Create_CollisionKS(755.f, 295.f, 10.f, 270.f));//우
	CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CObj_Collision>::Create_CollisionKS(55.f, 295.f, 10.f, 270.f));//좌

	// 6개의 구멍에 각각 오브젝트를 놓아 충돌 처리를 해줌.(씬 전환)-씬 체인지를 할 객체를 담을 vector에 6개 객체 담고 
	CObjMgr::Get_Instance()->Add_ObjectMain(CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 120.f, 50.f, 50.f));//나가기
	//CObjMgr::Get_Instance()->Add_ObjectMain(CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 120.f, 280.f, 10.f));//jini
	//CObjMgr::Get_Instance()->Add_ObjectMain(CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 120.f, 280.f, 10.f));//KMS
	//CObjMgr::Get_Instance()->Add_ObjectMain(CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 120.f, 280.f, 10.f));//Random
	//CObjMgr::Get_Instance()->Add_ObjectMain(CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 120.f, 280.f, 10.f));//KJE
	//CObjMgr::Get_Instance()->Add_ObjectMain(CAbstractFactory<CObj_Collision>::Create_CollisionKS(230.f, 120.f, 280.f, 10.f));//KS

}

void CScene_Main::Update(void)
{
	// 키 입력을 받아서 부동한 씬(게임)으로 전환.
	Key_Input();

	CObjMgr::Get_Instance()->Update();
}

void CScene_Main::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CCollisionMgr::Collision_RectEx(CObjMgr::Get_Instance()->Get_List(OBJ_COLLISIONKS), CObjMgr::Get_Instance()->Get_List(OBJ_BALL));
}

void CScene_Main::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MainGame");  //게임 시작시 버튼 뒤의 화면.
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_Main::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_COLLISIONKS);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BALL);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_STICK);
}

void CScene_Main::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_JINI);
	}
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_KMS);
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
