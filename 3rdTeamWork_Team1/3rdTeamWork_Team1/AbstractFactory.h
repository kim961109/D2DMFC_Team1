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
};