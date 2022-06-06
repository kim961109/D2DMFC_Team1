#pragma once
#include "Obj.h"
class CPlayerMS :
	public CObj
{
public:
	CPlayerMS();
	CPlayerMS(float _fX, float _fY, float _fZ);
	virtual ~CPlayerMS();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_PlayerMSPos(D3DXVECTOR3 _vPos) { m_tInfo.vPos = _vPos; }

private:
	void		Key_Input(void);

private:
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];
	D3DXVECTOR3			vLook;
	D3DXVECTOR3			m_vFirstPos;

	D3DXVECTOR3			m_vleftPoint[4];
	D3DXVECTOR3			m_vOriginleftPoint[4];

	D3DXVECTOR3			m_vrightPoint[4];
	D3DXVECTOR3			m_vOriginrightPoint[4];

	D3DXVECTOR3			m_vleftDownPoint[4];
	D3DXVECTOR3			m_vOriginleftDownPoint[4];

	D3DXVECTOR3			m_vrightDownPoint[4];
	D3DXVECTOR3			m_vOriginrightDownPoint[4];

	TCHAR*		m_pFrameKey;

	float		m_fSpeed;
	float		m_fAngle;
};

