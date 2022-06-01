#pragma once
#include "UI.h"
#include "Include.h"
#include "UI_PlayerHp.h"

class CUIMgr
{
public:
	CUIMgr();
	~CUIMgr();

public:
	void Add_UI(CUI* pUI);
	void Update(void);
	void Render(HDC hDC);
	void Delete_UI(void);

private:
	std::list<CUI*> m_UIList;

public:
	static CUIMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CUIMgr;
		}
		return m_pInstance;
	}
	static void Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CUIMgr* m_pInstance;
};

