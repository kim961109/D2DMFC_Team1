#include "stdafx.h"
#include "UI_PlayerHp.h"


CUI_PlayerHp::CUI_PlayerHp()
{
}


CUI_PlayerHp::~CUI_PlayerHp()
{
	Release();
}

void CUI_PlayerHp::Initialize(void)
{
}

void CUI_PlayerHp::Update(void)
{
}

void CUI_PlayerHp::Late_Update(void)
{
}

void CUI_PlayerHp::Render(HDC hDC)
{
	Rectangle(hDC, 730.f, 440.f, 770.f, 590.f);//HP표시할 렉트.


}

void CUI_PlayerHp::Release(void)
{
}
