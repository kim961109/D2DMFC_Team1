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

};