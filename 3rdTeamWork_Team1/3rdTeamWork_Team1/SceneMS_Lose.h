#pragma once
#include "Scene.h"
#include "BmpMgr.h"

class CSceneMS_Lose :
	public CScene
{
public:
	CSceneMS_Lose();
	virtual ~CSceneMS_Lose();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	TCHAR*		m_pFrameKey;
};

