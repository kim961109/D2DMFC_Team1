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
	float m_fAngle;//�Ѿ��� ���ư� ����.
	float m_fSpeed;//�Ѿ��� ���ư� �ӵ�.

	D3DXVECTOR3 vA;
	D3DXVECTOR3 vB;//�Ѿ��� ������ �ѱ� �������� ���� ��ǥ.//�Ѿ��� �κ����� x,y�� ������������.
};

