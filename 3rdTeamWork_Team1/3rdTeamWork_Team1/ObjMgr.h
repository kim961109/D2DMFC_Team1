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
	void Add_ObjectMain(CObj* pObj);

	CObj* Get_ListBack(OBJID eID)	{ return m_ObjList[eID].back(); }
	list<CObj*>& Get_List(OBJID eID) {return m_ObjList[eID];}
	vector<CObj*>& Get_Vector(void) { return m_MainCollisionVec; }

	void Render(HDC hDC);
	void Update(void);
	void Late_Update(void);

	void Delete_ID(OBJID eID);

private:
	std::list<CObj*> m_ObjList[OBJ_END];
	std::vector<CObj*> m_MainCollisionVec;//메인화면에서 충돌하여 부동한 씬으로 가게하는 충돌체.

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

