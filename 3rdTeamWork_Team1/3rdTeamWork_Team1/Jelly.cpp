#include "stdafx.h"
#include "Jelly.h"


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

	m_iScale = rand() % 6 + 5;
	
	// 여기
	m_fPlusScale = m_iScale * 0.1f;
}

int CJelly::Update(void)
{

	return 0;
}

void CJelly::Late_Update(void)
{
}

void CJelly::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Ellipse(hDC,
		int(m_tInfo.vPos.x - m_iScale),
		int(m_tInfo.vPos.y - m_iScale),
		int(m_tInfo.vPos.x + m_iScale),
		int(m_tInfo.vPos.y + m_iScale));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);
}

void CJelly::Release(void)
{
}
