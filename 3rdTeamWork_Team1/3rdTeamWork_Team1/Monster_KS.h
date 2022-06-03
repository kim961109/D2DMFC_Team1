#pragma once
#include "Obj.h"
#include "ScrollMgr.h"

class CMonster_KS :
	public CObj
{
public:
	CMonster_KS();
	CMonster_KS(D3DXVECTOR3 _vPos);
	virtual ~CMonster_KS();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Set_Damage(void) { m_iHp -= 1; }
	const int& Get_Hp(void) const { return m_iHp; }

private:
	int                 m_iHp;

	D3DXVECTOR3			m_vFirstPos;//¸öÃ¼ÀÇ 4°³ Á¡ÀÇ ÁÂÇ¥.
};

