#include "stdafx.h"
#include "Scene_KJE.h"
#include "BmpMgr.h"
#include"ObjMgr.h"
#include"Snake_Head.h"
#include"Snake_Body.h"
#include "AbstractFactory.h"
#include"TileMgr.h"
#include"Apple.h"
#include"CollisionMgr.h"

#define m_SnakeList CObjMgr::Get_Instance()->Get_List(OBJ_SNAKE)
#define m_AppleList CObjMgr::Get_Instance()->Get_List(OBJ_ITEM)
#define m_vecTile   CTileMgr::Get_Instance()->Get_Tile()

CScene_KJE::CScene_KJE()
{
	m_iMilliSecond = 0;
	m_iSecond = 0;
	m_iApple = 0;
}


CScene_KJE::~CScene_KJE()
{
	Release();
}

void CScene_KJE::Initialize(void)
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene_KJE.bmp", L"Scene_KJE");
	CTileMgr::Get_Instance()->Initialize();
	CObjMgr::Get_Instance()->Add_Object(OBJ_SNAKE, CAbstractFactory<CSnake_Head>::Create_SetPos(300.f, 400.f, 0.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_ITEM, CAbstractFactory<CApple>::Create(300.f, 370.f));
	//m_SnakeList = CObjMgr::Get_Instance()->Get_List(OBJ_SNAKE);
	//m_AppleList = CObjMgr::Get_Instance()->Get_List(OBJ_ITEM);
	//m_vecTile = CTileMgr::Get_Instance()->Get_Tile();
}

void CScene_KJE::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	m_iMilliSecond += 3;
	if (m_iMilliSecond > 100)
	{
		m_iMilliSecond = 0;
		m_iSecond += 1;
	}
}

void CScene_KJE::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();
	CCollisionMgr::Collision_Snake_Apple(m_SnakeList, m_AppleList);
	m_iApple = dynamic_cast<CApple*>(CObjMgr::Get_Instance()->Get_List(OBJ_ITEM).front())->Get_Apple();
	CCollisionMgr::Collision_Snake_Tile(m_SnakeList, m_vecTile);
}

void CScene_KJE::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Scene_KJE");
	BitBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
	//타이머
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"%d : %d", m_iSecond, m_iMilliSecond);
	TextOut(hDC, 70, 30, szBuff, lstrlen(szBuff));
	//사과
	TCHAR	szApple[32] = L"";
	swprintf_s(szApple, L"Apple: %d", m_iApple);
	TextOut(hDC, 620, 30, szApple, lstrlen(szApple));
}


void CScene_KJE::Release(void)
{
	//CObjMgr::Get_Instance()->Delete_ID(OBJ_MyButton);// 신이 바뀔때 그 신의 객체 모두 삭제

}
