#pragma once
#include "Scene.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

class CScene_Main :
	public CScene
{
public:
	CScene_Main();
	virtual ~CScene_Main();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void    Key_Input(void);
};

