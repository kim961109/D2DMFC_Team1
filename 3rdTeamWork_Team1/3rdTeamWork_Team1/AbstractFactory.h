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


	static CObj*	Create(float _fX, float _fY,float _fZ)
	{
		CObj*	pObj = new T;

		pObj->Set_Pos(_fX, _fY, _fZ);
		pObj->Initialize();
		return pObj;
	}

	static CObj*& Create_SetPos(float _fX, float _fY, float _fZ)
	{
		CObj* pObj = new T();
		pObj->Set_Pos(_fX, _fY, _fZ);
		pObj->Initialize();

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
};