#pragma once
#include "Obj.h"

class CPlayerJini :
	public CObj
{
public:
	CPlayerJini();
	virtual ~CPlayerJini();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fScale;
	float	m_fEllipse;

	D3DXVECTOR3		m_vBodyLocal[4];
	D3DXVECTOR3		m_vBody[4];

	D3DXVECTOR3		m_vDirLocal;
	D3DXVECTOR3		m_vLookLocal;

	int		m_iPlayerColorR;
	int		m_iPlayerColorG;
	int		m_iPlayerColorB;


};

