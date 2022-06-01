#include "stdafx.h"
#include "Scene_jini.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "PlayerJini.h"
#include "Jelly.h"

CScene_jini::CScene_jini()
{
}

CScene_jini::~CScene_jini()
{
}

void CScene_jini::Initialize(void)
{
	// 여기부터
	m_dwJellyCreate = GetTickCount();

	CObjMgr::Get_Instance()->Add_Object(OBJ_Player, CAbstractFactory<CPlayerJini>::Create_Player());
	// 여기까지
}


void CScene_jini::Update(void)
{
	// 여기부터
	srand(unsigned int(time(NULL)));
	m_fPosXRandom = float(rand() * rand() % 800);
	m_fPosYRandom = float(rand() % 600);

	if (GetTickCount() - m_dwJellyCreate > 300)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_Item, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom, m_fPosYRandom, 0.f));
		m_dwJellyCreate = GetTickCount();
	}
	// 여기까지

	CObjMgr::Get_Instance()->Update();
}

void CScene_jini::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene_jini::Render(HDC hDC)
{
	Rectangle(hDC, -10.f, -10.f, 810.f, 610.f);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_jini::Release(void)
{
	CObjMgr::Get_Instance()->Destroy_Instance();
}
