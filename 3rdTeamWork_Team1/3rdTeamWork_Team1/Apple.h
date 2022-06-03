#pragma once
#include"Obj.h"
class CApple
	:public CObj
{
public:
	CApple();
	~CApple();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	int Get_Apple() { return m_iApple; }
	void Set_ApplePlus() { m_iApple += 1; }

private:
	int		m_iApple;
};

