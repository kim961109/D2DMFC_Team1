#pragma once
#include "Include.h"
#include "Scene.h"
#include "Scene_Main.h"
#include "Scene_jini.h"
#include "Scene_KJE.h"
#include "Scene_KS.h"
#include "Scene_MinSungJJang.h"

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENEID eID);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);

public:
	static		CSceneMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	const SCENEID& Get_SceneID(void) { return m_eCurScene; }

private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;

	SCENEID					m_eCurScene;
	SCENEID					m_ePreScene;
};

