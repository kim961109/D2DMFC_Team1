#pragma once

#include "Obj.h"

class CTile :	public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Option(int _Opt) { m_iOption = _Opt; }

private:
	int			m_iDrawID;
	int			m_iOption;

};

