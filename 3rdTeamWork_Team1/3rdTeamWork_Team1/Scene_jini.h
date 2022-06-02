#pragma once
#include "Scene.h"
class CScene_jini :
	public CScene
{
public:
	CScene_jini();
	virtual ~CScene_jini();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:

	float	m_fPosXRandom;
	float	m_fPosYRandom;
	float	m_fPosZRandom;

	//¿©±â
	DWORD	m_dwJellyCreate;
};

