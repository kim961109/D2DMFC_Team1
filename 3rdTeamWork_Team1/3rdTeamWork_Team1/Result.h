#pragma once
#include "Obj.h"
class CResult :
	public CObj
{
public:
	CResult();
	virtual ~CResult();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public :
	void  Key_Input();
private:
	TCHAR	m_szTitle[64];
	TCHAR	m_szGameOver[64];
	
	TCHAR	m_szName[64];
	TCHAR	m_szScore[64];
	TCHAR	m_szTime[64];

	TCHAR	m_szSelect[64];


	int		m_iSelect;

};

