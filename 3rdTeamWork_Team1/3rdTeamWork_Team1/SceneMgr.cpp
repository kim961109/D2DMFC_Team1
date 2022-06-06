#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_END), m_ePreScene(SC_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_MAIN:
			m_pScene = new CScene_Main;
			break;

		case SC_JINI:
			m_pScene = new CScene_jini;
			break;

		case SC_KMS:
			m_pScene = new CScene_MinSungJJang;
			break;

		case SC_KJE:
			m_pScene = new CScene_KJE;
			break;

		case SC_KS:
			m_pScene = new CScene_KS;
			break;

		case SC_KSWIN:
			m_pScene = new CScene_WinKS;
			break;

		case SC_KSLOSE:
			m_pScene = new CScene_LoseKS;
			break;

		}

		m_pScene->Initialize();
		m_ePreScene = m_eCurScene;
	}

}

void CSceneMgr::Update(void)
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}