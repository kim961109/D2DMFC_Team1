#pragma once
#include "Scene.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"
#include "PlayerMS.h"
class CScene_ShapeMoment :
	public CScene
{
public:
	CScene_ShapeMoment();
	virtual ~CScene_ShapeMoment();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
public:
	void Reset(void);
	void Win_MS(void);
	void LoseCount();

private:
	TCHAR*		m_pFrameKey;
	int         m_iLoseCount;
};

