#include "stdafx.h"
#include "Jelly.h"
#include "ScrollMgr.h"

CJelly::CJelly()
{
}

CJelly::~CJelly()
{
}

void CJelly::Initialize(void)
{
	////임시 위치
	//m_tInfo.vPos = { 600.f, 450.f, 0.f };

	// 색상 랜덤 설정
	int m_iColor = rand() % 100;
	srand(unsigned int(time(NULL)));
	m_iPlayerColorR = (rand() % 256 * m_iColor) % 256;
	m_iPlayerColorG = (rand() % 256 * m_iColor) % 256;
	m_iPlayerColorB = (rand() % 256 * m_iColor) % 256;

	m_iScale = rand() % 6 + 8;

	// 여기
	m_fPlusScale = m_iScale * 0.0005f;
	m_fRadius = m_iScale;
}

int CJelly::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CJelly::Late_Update(void)
{
}

void CJelly::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Ellipse(hDC,
		int(m_tInfo.vPos.x - m_iScale * g_fRenderPercent + iScrollX),
		int(m_tInfo.vPos.y - m_iScale * g_fRenderPercent + iScrollY),
		int(m_tInfo.vPos.x + m_iScale * g_fRenderPercent + iScrollX),
		int(m_tInfo.vPos.y + m_iScale * g_fRenderPercent + iScrollY));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);
}

void CJelly::Release(void)
{
}
