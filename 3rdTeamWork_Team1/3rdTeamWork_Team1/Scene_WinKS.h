#pragma once
#include "Scene.h"
#include "BmpMgr.h"

class CScene_WinKS :
	public CScene
{
public:
	CScene_WinKS();
	virtual ~CScene_WinKS();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

