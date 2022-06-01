#pragma once
#include "Obj.h"
class CPlayerMS :
	public CObj
{
public:
	CPlayerMS();
	virtual ~CPlayerMS();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;


private:
	void		Key_Input(void);

private:
	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];
	D3DXVECTOR3			vLook;

	float		m_fSpeed;
	float		m_fAngle = 0;
};

