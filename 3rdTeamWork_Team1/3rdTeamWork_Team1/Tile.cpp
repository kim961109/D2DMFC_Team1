#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CTile::CTile()
{
	m_bDead = false;
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_tObjInfo.fCX = TILECX;
	m_tObjInfo.fCY = TILECY;

	m_iDrawID = 0;
	m_iOption = 0;
	
	//타일색상랜덤
	
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/Tile.bmp", L"Tile");
}

int CTile::Update(void)
{

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
	{ }
	//Rectangle(hDC, m_tInfo.vPos.x - (TILECX * 0.5), m_tInfo.vPos.y - (TILECY * 0.5), m_tInfo.vPos.x + (TILECX * 0.5), m_tInfo.vPos.y + (TILECY * 0.5));
	if (m_iOption == 1)
	{
		srand(unsigned int(time(NULL)));
		m_iTileColorR = rand() % 256;
		m_iTileColorG = rand() % 256;
		m_iTileColorB = rand() % 256;
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iTileColorR, m_iTileColorG, m_iTileColorB));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right,m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}

}

void CTile::Release(void)
{
	
}
