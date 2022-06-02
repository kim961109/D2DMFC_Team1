#pragma once
#include "Obj.h"

class CPlayerJini :
	public CObj
{
public:
	CPlayerJini();
	virtual ~CPlayerJini();

public:
	virtual void Initialize()		override;
	virtual void Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;
	
public :
	void	Offset();


private:
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fScale;
	float	m_fEllipse;

	D3DXVECTOR3		m_vBodyLocal[4];
	D3DXVECTOR3		m_vBody[4];

	D3DXVECTOR3		m_vDirLocal;
	D3DXVECTOR3		m_vLookLocal;

	D3DXVECTOR3		m_vPosScreen;
	D3DXVECTOR3		m_vDirBefore;

	D3DXVECTOR3		m_vMouseTemp;



	int		m_iPlayerColorR;
	int		m_iPlayerColorG;
	int		m_iPlayerColorB;

	float	m_fDistanceMouse;

	bool	m_bScroll;

	int		m_iScrollXBefore;
	int		m_iScrollYBefore;
};

