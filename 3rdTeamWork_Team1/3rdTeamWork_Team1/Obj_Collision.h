#pragma once
#include "Obj.h"
#include "BmpMgr.h"

class CObj_Collision :
	public CObj
{
public:
	CObj_Collision();
	CObj_Collision(float _fX, float _fY, float _fCX, float _fCY);
	virtual ~CObj_Collision();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Update_Rect(void);
};

