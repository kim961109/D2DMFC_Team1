#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(SC_End), m_ePreScene(SC_End)
{
}


CSceneMgr::~CSceneMgr()
{
}

void CSceneMgr::Scene_Change(SCENEID eID)    // ���� SceneExchange�Լ� ����� ���� ��:farm�� ���� ��Ŵ.���������.
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_Main:
			m_pScene = new CScene_Main;
			break;

		case SC_jini:
			m_pScene = new CScene_jini;
			break;

		case SC_MinSungJJang:
			m_pScene = new CScene_MinSungJJang;
			break;

		case SC_KJE:
			m_pScene = new CScene_KJE;
			break;

		case SC_KS:
			m_pScene = new CScene_KS;
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