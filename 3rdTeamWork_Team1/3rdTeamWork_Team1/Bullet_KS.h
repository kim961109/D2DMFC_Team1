#pragma once
#include "Obj.h"
class CBullet_KS :
	public CObj
{
public:
	CBullet_KS();
	CBullet_KS(float _fAngle, D3DXVECTOR3 vA, D3DXVECTOR3 vB);
	virtual ~CBullet_KS();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Move_Bullet_KS(void);

private:
	float m_fAngle;//총알이 나아갈 각도.
	float m_fSpeed;//총알이 날아갈 속도.

	D3DXVECTOR3 vA;
	D3DXVECTOR3 vB;//총알이 생성될 총구 끝방향의 두점 좌표.//총알은 두벡터의 x,y의 중점에서생성.
};

