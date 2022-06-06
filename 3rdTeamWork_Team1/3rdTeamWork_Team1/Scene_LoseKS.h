#pragma once
#include "Scene.h"
#include "BmpMgr.h"

class CScene_LoseKS :
	public CScene
{
public:
	CScene_LoseKS();
	virtual ~CScene_LoseKS();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

