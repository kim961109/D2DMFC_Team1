#pragma once
#include "Obj.h"
#include "KeyMgr.h"
#include "Ball.h"
#include "ObjMgr.h"

class CStick :
	public CObj
{
public:
	CStick();
	virtual ~CStick();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Key_Input(void);
	void Key_Start(void);
	void Check_Angle(void);
	void Move_Stick(void);

private:
	float m_fAngle;

	D3DXVECTOR3 m_vPointPos[4];
	D3DXVECTOR3 m_vOriginPointPos[4];

	D3DXVECTOR3 m_vMoveDir;

	bool m_bMove; // 막대기를 움직이냐 안 움직이냐.
	bool m_bHit; //공을 쳤냐 안 쳤냐 
	bool m_bGameStart;
	int m_iMoveTimeUp;
	int m_iMoveTimeDown;
};

