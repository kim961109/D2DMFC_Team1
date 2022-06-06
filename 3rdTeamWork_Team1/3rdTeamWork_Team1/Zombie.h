#pragma once
#include "Obj.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

class CZombie :
	public CObj
{
public:
	CZombie();
	CZombie(D3DXVECTOR3 vPos, CObj* pObj);
	virtual ~CZombie();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	
public:
	void Update_RectZombie(void);
	void Motion_Change(void);
	void ChaseAngle(void);
	void Set_Damage(void) { m_iHp -= 1; }

private:
	float m_fSpeed;
	int m_iHp;
	CObj* m_pTarget;
	float fRadian;//쫓아갈 각도.
	float fAngleA;
	bool m_bChase;//플레이어를 쫓아갈지말지.

	enum MotionID
	{
		WALK_DOWN,
		WALK_RIGHT,
		WALK_UP,
		WALK_LEFT,
		IDLE,
		END
	}STATEID;

	MotionID m_eCurState;
	MotionID m_ePreState;
};

