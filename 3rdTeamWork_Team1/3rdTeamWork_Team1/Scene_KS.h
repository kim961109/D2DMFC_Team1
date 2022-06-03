#pragma once
#include "Scene.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "UIFactory.h"
#include "Player_KS.h"


class CScene_KS :
	public CScene
{
public:
	CScene_KS();
	virtual ~CScene_KS();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

