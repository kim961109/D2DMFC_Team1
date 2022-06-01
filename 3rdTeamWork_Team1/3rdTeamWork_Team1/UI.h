#pragma once
#include "Include.h"

class CUI
{
public:
	CUI();
	~CUI();

public:
	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;

	void Update_Rect(void);

protected:
	UIINFO m_tInfo;
	RECT m_tRect;
};

