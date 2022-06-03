#pragma once
#include "Include.h"
#include "Obj.h"

class CObjMgr
{
public:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(OBJID eID, CObj* pObj);
	// ¿©±â
	CObj* Get_ListBack(OBJID eID);
	list<CObj*>& Get_List(OBJID eID) {return m_ObjList[eID];}
	void Render(HDC hDC);
	void Update(void);
	void Late_Update(void);

	void Delete_ID(OBJID eID);

private:
	std::list<CObj*> m_ObjList[OBJ_End];

public:
	static CObjMgr* Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
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
	static CObjMgr* m_pInstance;
};

