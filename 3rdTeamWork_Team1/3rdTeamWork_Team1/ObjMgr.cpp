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
	if ((eID >= OBJ_End) || (pObj == nullptr))
	{
		return;
	}
	m_ObjList[eID].push_back(pObj);
}

// ����
CObj * CObjMgr::Get_ListBack(OBJID eID)
{
	return m_ObjList[eID].back();
}

void CObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_End; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Render(hDC);
		}
	}
}

void CObjMgr::Update(void)
{
	
	for (int i = 0; i < OBJ_End; ++i)
	{
		//for (auto& iter : m_ObjList[i])
		for (auto& iter = m_ObjList[i].begin() ; iter != m_ObjList[i].end();)
		{
			if ((*iter)->Update() == OBJ_DEAD)
			{
				Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJ_End; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty()) // ���� �ٲ� ������Ʈ�� ���� �����Ͽ� Late_Update���� ��Ÿ�ӿ����� ���°� ����.
			{
				return;
			}
		}
	}
}

void CObjMgr::Delete_ID(OBJID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}
