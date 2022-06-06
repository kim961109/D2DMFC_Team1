#pragma once
#include "Obj.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Bullet_KS.h"

class CPlayer_KS :
	public CObj
{
public:
	CPlayer_KS();
	virtual ~CPlayer_KS();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	const int& Get_PlayerKS_Hp(void) { return m_iHp; }
	void Set_Damage(void) { m_iHp -= 1; }

	void Set_KSPosX(float _fX) { m_tInfo.vPos.x += _fX; }
	void Set_KSPosY(float _fY) { m_tInfo.vPos.y += _fY; }
	const float& Get_KSPosX(void) { return m_tInfo.vPos.x; }
	const float& Get_KSPosY(void) { return m_tInfo.vPos.y; }

private:
	void		Key_Input(void);
	void		Key_Shoot(void);
	void        Change_GunAngle(void);
	void        Offset(void);
	void        Update_RectKS(void);


private:
	D3DXVECTOR3			m_vGunPoint[4];//총의 4개 점의 좌표.
	D3DXVECTOR3			m_vOriginGunPoint[4];//총의 로컬 좌표를 기억해줄 벡터.

	D3DXVECTOR3			m_vBodyPoint[4];//몸체의 4개 점의 좌표.
	D3DXVECTOR3			m_vOriginBodyPoint[4];//몸체의 로컬 좌표를 기억해줄 벡터.

	float				m_fGunAngle;//총구가 바라보는 방향.
	float               m_fBodyAngle;//몸체가 바라보는 방향.
	float               m_fSpeed;//플레이어의 이동속도.

	int                 m_iHp;

	DWORD               dwPastTime;
};

