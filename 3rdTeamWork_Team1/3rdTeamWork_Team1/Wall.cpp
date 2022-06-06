#include "stdafx.h"
#include "Wall.h"


CWall::CWall()
{
}

CWall::CWall(float _fX, float _fY, float _fCX, float _fCY)
{
	m_tObjInfo.fX = _fX;
	m_tObjInfo.fY = _fY;
	m_tObjInfo.fCX = _fCX;
	m_tObjInfo.fCY = _fCY;
}


CWall::~CWall()
{
	Release();
}

void CWall::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene_KS2.bmp", L"Scene_KS2");
}

int CWall::Update(void)
{

	Update_RectWall();
	return 0;
}

void CWall::Late_Update(void)
{
}

void CWall::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Scene_KS2");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		int(m_tObjInfo.fCX),
		int(m_tObjInfo.fCY),
		hMemDC,
		0,
		0,
		(int)m_tObjInfo.fCX,
		(int)m_tObjInfo.fCY,
		RGB(254, 255, 255));

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CWall::Release(void)
{
}

void CWall::Update_RectWall()
{
	int		iScrollX =  (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY =  (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tRect.left = m_tObjInfo.fX - 0.5 * m_tObjInfo.fCX + iScrollX;
	m_tRect.top = m_tObjInfo.fY - 0.5 * m_tObjInfo.fCY + iScrollY;
	m_tRect.right = m_tObjInfo.fX + 0.5 * m_tObjInfo.fCX + iScrollX;
	m_tRect.bottom = m_tObjInfo.fY + 0.5 * m_tObjInfo.fCY + iScrollY;
}
