#pragma once
#include "Obj.h"
class CJelly :
	public CObj
{
public:
	CJelly();
	virtual ~CJelly();

// 여기
public :
	const float&	Get_PlusScale() const { return m_fPlusScale; }
	const float&	Get_Radius() { return m_fRadius; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private :
	int		m_iPlayerColorR;
	int		m_iPlayerColorG;
	int		m_iPlayerColorB;

	int		m_iScale;

	// 여기
	float	m_fRadius;
	float	m_fPlusScale;

};

