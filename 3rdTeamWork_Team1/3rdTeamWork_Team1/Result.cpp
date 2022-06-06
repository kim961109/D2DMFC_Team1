#include "stdafx.h"
#include "Result.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CResult::CResult()
{
}


CResult::~CResult()
{
}

void CResult::Initialize(void)
{
	lstrcpy(m_szTitle, L"지니의 세포들");
	lstrcpy(m_szGameOver, L"GAME OVER");
	lstrcpy(m_szName, L"< 순수하짐님 게임결과 >");
	lstrcpy(m_szSelect, L">> 다시하기         >> 메인으로");

	m_iSelect = 2;

}

int CResult::Update(void)
{
	Key_Input();
	return 0;
}

void CResult::Late_Update(void)
{
	int iScoreTemp = (int)g_fScore;
	swprintf_s(m_szScore, L"점수 : %d", iScoreTemp);
	
	int iTimeTemp = (int)g_dwPlayTime;
	swprintf_s(m_szTime, L"플레이 시간 : %d 초", iTimeTemp / 1000);
}

void CResult::Render(HDC hDC)
{
	// 창
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, 200.f, 100.f, 600.f, 500.f);

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);

	// 선택
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Rectangle(hDC, 45.f + 185.f * g_iSelect, 425.f, 45.f + 185.f * g_iSelect + 150.f, 475.f);

	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	// 타이틀
	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfCharSet = 129;
	m_labelFontInfo.lfHeight = 30;
	m_labelFontInfo.lfWidth = 15;
	m_labelFontInfo.lfWeight = FW_BOLD;

	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);
	SetBkMode(hDC, TRANSPARENT); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(255, 255, 255));
	SetTextColor(hDC, RGB(0, 10, 17));

	TextOut(hDC, 300.f, 150.f, m_szTitle, lstrlen(m_szTitle));
	TextOut(hDC, 300.f, 200.f, m_szGameOver, lstrlen(m_szGameOver));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);

	MoveToEx(hDC, 300.f, 260.f, NULL);
	LineTo(hDC, 500.f, 260.f);

	// 순수하짐님 게임결과
	LOGFONT m_labelFontInfo2{};
	m_labelFontInfo2.lfCharSet = 129;
	m_labelFontInfo2.lfHeight = 20;
	m_labelFontInfo2.lfWidth = 10;
	m_labelFontInfo2.lfWeight = FW_BOLD;

	HFONT textFont2, oldFont2;
	textFont2 = CreateFontIndirect(&m_labelFontInfo2);
	oldFont2 = (HFONT)SelectObject(hDC, textFont2);
	SetBkMode(hDC, TRANSPARENT); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(255, 255, 255));
	SetTextColor(hDC, RGB(0, 10, 17));

	TextOut(hDC, 270.f, 300.f, m_szName, lstrlen(m_szName));

	SelectObject(hDC, oldFont2);
	DeleteObject(textFont2);

	// 게임결과
	LOGFONT m_labelFontInfo3{};
	m_labelFontInfo3.lfCharSet = 129;
	m_labelFontInfo3.lfHeight = 20;
	m_labelFontInfo3.lfWidth = 10;

	HFONT textFont3, oldFont3;
	textFont3 = CreateFontIndirect(&m_labelFontInfo3);
	oldFont3 = (HFONT)SelectObject(hDC, textFont3);
	SetBkMode(hDC, TRANSPARENT); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(255, 255, 255));
	SetTextColor(hDC, RGB(0, 10, 17));

	TextOut(hDC, 270.f, 340.f, m_szScore, lstrlen(m_szScore));
	TextOut(hDC, 270.f, 380.f, m_szTime, lstrlen(m_szTime));
	TextOut(hDC, 250.f, 440.f, m_szSelect, lstrlen(m_szSelect));

	SelectObject(hDC, oldFont3);
	DeleteObject(textFont3);

}

void CResult::Release(void)
{
}

void CResult::Key_Input()
{
}
