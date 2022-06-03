#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;
CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::Scroll_Lock(void)
{
	if (SC_KS == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		if (-1100 > m_fScrollX)
			m_fScrollX = -1100;

		if (-660 > m_fScrollY)
			m_fScrollY = -660;
	}
	else
	{
		if (0.f < m_fScrollX)
			m_fScrollX = 0.f;

		if (0.f < m_fScrollY)
			m_fScrollY = 0.f;

		/*if (WINCX - TILECX * TILEX > m_fScrollX)
			m_fScrollX = WINCX - TILECX * TILEX;

		if (WINCY - TILECY * TILEY > m_fScrollY)
			m_fScrollY = WINCY - TILECY * TILEY;*/
	}
}