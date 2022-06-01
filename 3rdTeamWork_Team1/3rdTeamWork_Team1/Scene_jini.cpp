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
	srand(unsigned int(time(NULL)));
	m_fPosXRandom = float(rand() % 800);
	m_fPosYRandom = float(rand() % 600);
	m_fPosZRandom = 0.f;

	CObjMgr::Get_Instance()->Add_Object(OBJ_Player, CAbstractFactory<CPlayerJini>::Create_Player());
	CObjMgr::Get_Instance()->Add_Object(OBJ_Item, CAbstractFactory<CJelly>::Create_SetPos(m_fPosXRandom, m_fPosYRandom, m_fPosZRandom ));
}


void CScene_jini::Update(void)
{
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
