#pragma once
#include "Obj.h"
class CGameOver :public CObj
{

public:
	CGameOver();
	virtual ~CGameOver();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	TCHAR	m_szGameOver[64];

	TCHAR	m_szName[64];
	TCHAR	m_szScore[64];
	TCHAR	m_szTime[64];


	int		m_iSelect;

};

