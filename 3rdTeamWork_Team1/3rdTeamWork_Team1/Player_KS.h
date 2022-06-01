#pragma once
#include "Obj.h"
class CPlayer_KS :
	public CObj
{
public:
	CPlayer_KS();
	virtual ~CPlayer_KS();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void        Change_GunAngle(void);


private:
	D3DXVECTOR3			m_vGunPoint[4];//총의 4개 점의 좌표.
	D3DXVECTOR3			m_vOriginGunPoint[4];//총의 로컬 좌표를 기억해줄 벡터.

	D3DXVECTOR3			m_vBodyPoint[4];//몸체의 4개 점의 좌표.
	D3DXVECTOR3			m_vOriginBodyPoint[4];//몸체의 로컬 좌표를 기억해줄 벡터.

	float				m_fGunAngle = 0.f;//총구가 바라보는 방향.
	float               m_fSpeed;//플레이어의 이동속도.
};

