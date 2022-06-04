#pragma once

#include "Obj.h"

class CTileMS : public CObj
{
public:
	CTileMS();
	virtual ~CTileMS();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	const int& Get_DrawID(void) { return m_iDrawID; }
	const int& Get_Option(void) { return m_iOption; }

public:
	void		Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void		Set_Option(int _iOption) { m_iOption = _iOption; }

private:
	int			m_iDrawID;
	int			m_iOption;




};

