#include "stdafx.h"
#include "GameOver.h"


CGameOver::CGameOver()
{
}


CGameOver::~CGameOver()
{
}
void CGameOver::Initialize(void)
{
}

int CGameOver::Update(void)
{
	return 0;
}

void CGameOver::Late_Update(void)
{
	int iScoreTemp = (int)g_fScore;
	swprintf_s(m_szScore, L"점수 : %d", iScoreTemp);

	int iTimeTemp = (int)g_dwPlayTime;
	swprintf_s(m_szTime, L"플레이 시간 : %d 초", iTimeTemp / 1000);
}

void CGameOver::Render(HDC hDC)
{
	// 창
	//HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
	//HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	//Rectangle(hDC, 300.f, 100.f, 600.f, 140.f);

	//SelectObject(hDC, oldBrush);
	//DeleteObject(myBrush);


	//GameOver
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

	lstrcpy(m_szGameOver, L"GAME OVER");
	TextOut(hDC, 300.f, 280.f, m_szGameOver, lstrlen(m_szGameOver));
	
	SelectObject(hDC, oldFont);
	DeleteObject(textFont);

}

void CGameOver::Release(void)
{
}

