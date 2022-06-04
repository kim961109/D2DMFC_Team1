#include "stdafx.h"
#include "Apple.h"
#include"BmpMgr.h"


CApple::CApple()
{
	m_bDead = false;
	m_iApple = 0;
}


CApple::~CApple()
{
}

void CApple::Initialize(void)
{
	m_tObjInfo.fCX = 20;
	m_tObjInfo.fCY = 20;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Apple.bmp", L"Apple");
}

int  CApple::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void  CApple::Late_Update(void)
{
}

void  CApple::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Apple");
	GdiTransparentBlt(hDC, int(m_tRect.left), int(m_tRect.top), int(m_tObjInfo.fCX ), int( m_tObjInfo.fCY), hMemDC, 0, 0, m_tObjInfo.fCX, m_tObjInfo.fCY, RGB(255, 255, 255));

}

void  CApple::Release(void)
{
}
