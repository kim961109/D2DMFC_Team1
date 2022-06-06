#include "stdafx.h"
#include "Scene_KS.h"


CScene_KS::CScene_KS()
{
}


CScene_KS::~CScene_KS()
{
	Release();
}

void CScene_KS::Initialize(void)
{
	m_bWin = false;
	m_bLose = false;
	dwZombieTime = GetTickCount();
	m_dwWorldTime = GetTickCount();
	m_iMinute = 0;
	m_iHour = 0;
	CScrollMgr::Get_Instance()->Set_EScrollX(0);
	CScrollMgr::Get_Instance()->Set_EScrollY(0);
	//플레이어 생성.
	CObj* pObj = CAbstractFactory<CPlayer_KS>::Create_Player();
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, pObj);
	//몬스터 생성.
	vMonsterPos[0] = { 300, 200,0 };
	vMonsterPos[1] = { 1300, 300,0 };
	vMonsterPos[2] = { 800, 850,0 };
	vMonsterPos[3] = { 650, 650,0 };
	vMonsterPos[4] = { 1500, 1300,0 };


	//테스트용 몬스터
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonster_KS>::Create_Monster(vMonsterPos[0]));
	//좀비 생성
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[0], pObj));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[1], pObj));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[2], pObj));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[3], pObj));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[4], pObj));

	// 맵을 못 벗어나는 충돌체.
	//CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CWall>::Create_CollisionKS(960.f, 0.f, 1920.f, 10.f));//상
	//CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CWall>::Create_CollisionKS(960.f, 1260.f, 1920.f, 10.f));//하
	//CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CWall>::Create_CollisionKS(10.f, 5.f, 1920.f, 10.f));//우
	//CObjMgr::Get_Instance()->Add_Object(OBJ_COLLISIONKS, CAbstractFactory<CWall>::Create_CollisionKS(10.f, 5.f, 1920.f, 10.f));//좌

	//UI 생성.
	//CUIMgr::Get_Instance()->Add_UI(CUIFactory<CUI_PlayerHp>::Create_UIPlayerHP());

	//배경 이미지추가.
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround_KS.bmp", L"BackGround_KS");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/win.bmp", L"win");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/lose.bmp", L"lose");
}

void CScene_KS::Update(void)
{
	if ((dwZombieTime + 1000 < GetTickCount()) && (m_bWin == false) && (m_bLose == false))
	{
		CObj* pObj = CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front();

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[0], pObj));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[1], pObj));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[2], pObj));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[3], pObj));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CZombie>::Create_Zombie(vMonsterPos[4], pObj));

		dwZombieTime = GetTickCount();
	}

	//Scene_ChangeKey();
	if ((m_bWin == false) && (m_bLose == false))
	{
		CObjMgr::Get_Instance()->Update();
		CUIMgr::Get_Instance()->Update();
	}
	Escape_Map();
}

void CScene_KS::Late_Update(void)
{
	CCollisionMgr::Collision_BulletKS(CObjMgr::Get_Instance()->Get_List(OBJ_BULLET), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER));
	CCollisionMgr::Collision_Zombie(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER), CObjMgr::Get_Instance()->Get_List(OBJ_MONSTER));
	//CCollisionMgr::Collision_RectKS(CObjMgr::Get_Instance()->Get_List(OBJ_COLLISIONKS), CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER));

	CObjMgr::Get_Instance()->Late_Update();
	Win();
	Lose();
	if (m_bWin == true)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_KSWIN);
	}
	if (m_bLose == true)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_KSLOSE);
	}
	// 플레이어가 맵을 벗어나면 피깍임.
}

void CScene_KS::Render(HDC hDC)
{
	//Rectangle(hDC, 0, 0, WINCX, WINCY); //테스트용 흰색 배경.

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hGroundMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BackGround_KS");
	BitBlt(hDC, iScrollX, iScrollY, 1920, 1280, hGroundMemDC, 0, 0, SRCCOPY);

	if ((m_bWin == false) && (m_bLose == false))
	{
		CObjMgr::Get_Instance()->Render(hDC);
		CUIMgr::Get_Instance()->Render(hDC);
		Counting_Time(hDC);
	}
}

void CScene_KS::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_BULLET);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_MONSTER);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_COLLISIONKS);
	CUIMgr::Get_Instance()->Delete_UI();
}

void CScene_KS::Scene_ChangeKey(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MAIN);
	}
}

void CScene_KS::Counting_Time(HDC hDC)
{
	if (m_dwWorldTime + 50 < GetTickCount())
	{
		m_iMinute += 1;
		m_dwWorldTime = GetTickCount();
	}
	if (m_iMinute == 60)
	{
		m_iHour += 1;
		m_iMinute = 0;
	}
	if (m_iHour == 24)
	{
		m_iHour = 0;
		m_iMinute = 0;
	}

	TCHAR Hour[32] = L"";
	TCHAR MINUTE[32] = L"";
	TCHAR HP[23] = L"";
	swprintf_s(Hour, L"%02d", m_iHour);
	swprintf_s(MINUTE, L"%02d", m_iMinute);
	swprintf_s(HP, L"%02d", static_cast<CPlayer_KS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_PlayerKS_Hp());

	SetBkMode(hDC, TRANSPARENT); // 폰트 출력시 배경을 지워주는 함수.뒤의 값이 1이면 투명, 2이면 하얀색.(TextOut 바로 앞줄에 씀.)
								 //TextOut(hDC, (int)0.5 * WINCX, (int)0.5*WINCY, (LPCWSTR)Hour, lstrlen((LPCWSTR)Hour));
	//time font
	TextOut(hDC, (int)(0.5 * WINCX - 20), (int)(0.5 * WINCY - 250), Hour, lstrlen(Hour));
	TextOut(hDC, (int)(0.5 * WINCX ), (int)(0.5 * WINCY - 250), TEXT("  :  "), strlen("  :  "));
	TextOut(hDC, (int)(0.5 * WINCX + 20), (int)(0.5 * WINCY - 250), MINUTE, lstrlen(MINUTE));
	//HP font
	TextOut(hDC, (int)(WINCX - 70), (int)(0.5 * WINCY - 250), TEXT(" HP :  "), strlen(" HP :  "));
	TextOut(hDC, (int)(WINCX - 30), (int)(0.5 * WINCY - 250), HP, lstrlen(HP));
	//TextOut(hDC, (int)(0.5 * WINCX + 400), (int)(0.5 * WINCY - 355), TEXT(" DAY :  "), strlen(" DAY :  "));
}

void CScene_KS::Win(void)
{
	if (m_iHour >= 10)
	{
		m_bWin = true;
	}
}

void CScene_KS::Lose(void)
{
	if (static_cast<CPlayer_KS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_PlayerKS_Hp() <= 0)
	{
		m_bLose = true;
	}
}

void CScene_KS::Escape_Map(void)
{
	if (!CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).empty())
	{
		float fEscapeX = static_cast<CPlayer_KS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_KSPosX();
		float fEscapeY = static_cast<CPlayer_KS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_KSPosY();
		if ((fEscapeX > 1920.f) || (fEscapeX < 0.f) || (fEscapeY < 0.f) || (fEscapeY > 1280.f))
		{
			static_cast<CPlayer_KS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Set_Damage();
			static_cast<CPlayer_KS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Set_Damage();
			static_cast<CPlayer_KS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Set_Damage();
		}
	}
}
