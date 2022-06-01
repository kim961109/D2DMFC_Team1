#pragma once
#include "UI.h"
class CUI_PlayerHp :
	public CUI
{
public:
	CUI_PlayerHp();
	virtual ~CUI_PlayerHp();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

