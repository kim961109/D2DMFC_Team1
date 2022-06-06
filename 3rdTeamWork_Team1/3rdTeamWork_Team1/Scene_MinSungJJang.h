#pragma once
#include "Scene.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "PlayerMS.h"
class CScene_MinSungJJang :
	public CScene
{
public:
	CScene_MinSungJJang();
	virtual ~CScene_MinSungJJang();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Key_Input();
private:
	TCHAR*		m_pFrameKey;
};

