#include "stdafx.h"
#include "ObjMgr.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}

void CObjMgr::Add_Object(OBJID eID, CObj * pObj)
{
	if ((eID >= OBJ_END) || (pObj == nullptr))
	{
		return;
	}
	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Add_ObjectMain(CObj * pObj)
{
	m_MainCollisionVec.push_back(pObj);
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Render(hDC);
		}
	}

	for (auto& iter : m_MainCollisionVec)
	{
		iter->Render(hDC);
	}
}

void CObjMgr::Update(void)
{
	
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;

		//for (auto& iter : m_ObjList[i])
		/*for (auto& iter = m_ObjList[i].begin() ; iter != m_ObjList[i].end();)
		{
			if ((*iter)->Update() == OBJ_DEAD)
			{
				Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}*/

		}
	}
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	
	for (auto& iter = m_MainCollisionVec.begin();iter != m_MainCollisionVec.end();++iter)
	{
		int iResult = (*iter)->Update();
	}
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty()) // 신이 바뀔때 오브젝트를 전부 삭제하여 Late_Update에서 런타임에러가 나는걸 방지.
			{
				return;
			}
		}
	}

	for (auto& iter : m_MainCollisionVec)
	{
		iter->Late_Update();
	}

}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();

	for (auto& iter : m_MainCollisionVec)
	{
		Safe_Delete(iter);
	}
	m_MainCollisionVec.clear();
}
