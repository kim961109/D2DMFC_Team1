#include "stdafx.h"
#include "TileMS.h"
#include "ScrollMgr.h"

CTileMS::CTileMS()
{
}


CTileMS::~CTileMS()
{
	Release();
}

void CTileMS::Initialize(void)
{
	m_tObjInfo.fCX = TILEDX;
	m_tObjInfo.fCY = TILEDY;

	m_iDrawID = 0;
	m_iOption = 0;
}

int CTileMS::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
	
}

void CTileMS::Late_Update(void)
{
}

void CTileMS::Render(HDC hDC)
{
	if (0 == m_iOption)
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);

	}
	
}

void CTileMS::Release(void)
{
}
