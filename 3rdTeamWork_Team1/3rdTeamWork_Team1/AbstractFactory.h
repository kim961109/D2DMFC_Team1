#pragma once
#include "Include.h"

template<typename T>
class CAbstractFactory
{
public:

	CAbstractFactory()
	{
	}

	~CAbstractFactory()
	{
	}

public:
	static CObj*& Create_Player()
	{
		CObj* pObj = new T();
		pObj->Initialize();

		return pObj;
	}


	static CObj*&	Create(float _fX, float _fY)//m_tObjInfo Initialize 
	{
		CObj*	pObj = new T;
		pObj->Set_ObjPos(_fX, _fY);
		pObj->Initialize();
		
		return pObj;
	}


	static CObj*& Create_SetPos(float _fX, float _fY, float _fZ)
	{
		CObj* pObj = new T();
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY, _fZ);
		
		return pObj;
	}

	static CObj*& Create_Bullet(float _fAngle, D3DXVECTOR3 vA, D3DXVECTOR3 vB)
	{
		CObj* pObj = new T(_fAngle, vA, vB);
		pObj->Initialize();

		return pObj;
	}

	static CObj*& Create_Monster(D3DXVECTOR3 vPos)
	{
		CObj* pObj = new T(vPos);
		pObj->Initialize();

		return pObj;
	}

	static CObj*& Create_Ball(D3DXVECTOR3 vPos)
	{
		CObj* pObj = new T(vPos);
		pObj->Initialize();

		return pObj;
	}

	static CObj*& Create_Stick()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*& Create_CollisionKS(float _fX, float _fY, float _fCX, float _fCY)
	{
		CObj* pObj = new T(_fX, _fY, _fCX, _fCY);
		pObj->Initialize();

		return pObj;
	}

	static CObj*& Create_Zombie(D3DXVECTOR3 vPos, CObj* _pObj)
	{
		CObj* pObj = new T(vPos, _pObj);
		pObj->Initialize();

		return pObj;
	}
};