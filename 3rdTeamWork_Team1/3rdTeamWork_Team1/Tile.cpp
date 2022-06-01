#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_tObjInfo.fX = m_tInfo.vPos.x;
	m_tObjInfo.fY = m_tInfo.vPos.y;

	m_tObjInfo.fCX = TILECX;
	m_tObjInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iOption = 0;

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
}

int CTile::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CTile::Late_Update(void)
{
	
}

void CTile::Render(HDC hDC)
{
	//int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");
	
	//BitBlt(hDC, 
		//m_tRect.left + iScrollX,
		//m_tRect.top + iScrollY,
		//TILECX,
		//TILECY,
		//hMemDC,
		//TILECX * m_iDrawID,
		//0,
		//SRCCOPY);
	if(m_iOption==0)
	Rectangle(hDC, m_tInfo.vPos.x - (TILECX * 0.5), m_tInfo.vPos.y - (TILECY * 0.5), m_tInfo.vPos.x + (TILECX * 0.5), m_tInfo.vPos.y + (TILECY * 0.5));
	if (m_iOption == 1)
	{
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Rectangle(hDC, m_tInfo.vPos.x - (TILECX * 0.5), m_tInfo.vPos.y - (TILECY * 0.5), m_tInfo.vPos.x + (TILECX * 0.5), m_tInfo.vPos.y + (TILECY * 0.5));
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}

	
}

void CTile::Release(void)
{
	
}
