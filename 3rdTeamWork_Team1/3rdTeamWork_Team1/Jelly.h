#pragma once
#include "Obj.h"
class CJelly :
	public CObj
{
public:
	CJelly();
	virtual ~CJelly();

	// ¿©±â
public:
	const float&	Get_PlusScale() const { return m_fPlusScale; }
	const float&	Get_Scale() const { return m_iScale; }
	const float&	Get_Radius() { return m_fRadius; }

	void	Set_ScaleZero() { m_iScale = 0; m_fPlusScale = 0; }


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		m_iPlayerColorR;
	int		m_iPlayerColorG;
	int		m_iPlayerColorB;

	int		m_iScale;

	float	m_fRadius;
	float	m_fPlusScale;
};

