#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CBall :
	public CObj
{
public:
	CBall();
	CBall(D3DXVECTOR3 _vPos);
	virtual ~CBall();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Update_CollisionPos(void);
	void Update_BallRect(void);

public:
	void Set_Move(D3DXVECTOR3 _vMove) { m_vMoveDir = _vMove; }
	void Set_MoveBool(bool _b) { m_bMove = _b; }
	void Reset_Ball(void);

	void Change_MoveX(void) { m_vMoveDir.x *= -1;}
	void Change_MoveY(void) { m_vMoveDir.y *= -1; }

private:
	float m_fAngle; // È¸Àü°¢.

	D3DXVECTOR3 m_vFirstPos;
	D3DXVECTOR3 m_vCurPos;
	D3DXVECTOR3 m_vMoveDir;

	bool m_bMove;
};

