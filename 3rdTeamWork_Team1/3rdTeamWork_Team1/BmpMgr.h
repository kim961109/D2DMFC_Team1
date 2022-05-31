#pragma once
#include "MyBmp.h"
#include "Include.h"

class CBmpMgr
{
public:
	CBmpMgr();
	~CBmpMgr();

public:
	static CBmpMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CBmpMgr;
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

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImageKey);
	HDC			Find_Image(const TCHAR* pImageKey);
	void		Release(void);

private:
	static CBmpMgr* m_pInstance;
	map<const TCHAR*, CMyBmp*>		m_mapBit;
};

