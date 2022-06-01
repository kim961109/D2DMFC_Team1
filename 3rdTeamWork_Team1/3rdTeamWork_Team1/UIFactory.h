#pragma once
#include "Include.h"
#include "UI.h"

template<typename T>
class CUIFactory
{
public:

	CUIFactory()
	{
	}

	~CUIFactory()
	{
	}

public:
	static CUI*& Create_UIPlayerHP()
	{
		CUI* pUI = new T();
		pUI->Initialize();

		return pUI;
	}
};