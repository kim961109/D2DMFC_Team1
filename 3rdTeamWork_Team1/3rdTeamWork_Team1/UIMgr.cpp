#include "stdafx.h"
#include "UIMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;
CUIMgr::CUIMgr()
{
}


CUIMgr::~CUIMgr()
{
}

void CUIMgr::Add_UI(CUI * pUI)
{
	m_UIList.push_back(pUI);
}

void CUIMgr::Update(void)
{
	for (auto& iter : m_UIList)
	{
		iter->Update();
	}
}

void CUIMgr::Render(HDC hDC)
{
	for (auto& iter : m_UIList)
	{
		iter->Render(hDC);
	}
}

void CUIMgr::Delete_UI(void)
{
	for (auto& iter : m_UIList)
	{
		Safe_Delete(iter);
	}
	m_UIList.clear();
}
