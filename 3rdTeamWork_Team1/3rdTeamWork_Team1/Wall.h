#pragma once
#include "Obj.h"
#include "ScrollMgr.h"

class CWall :
	public CObj
{
public:
	CWall();
	CWall(float _fX, float _fY, float _fCX, float _fCY);
	virtual ~CWall();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void Update_RectWall();
};

