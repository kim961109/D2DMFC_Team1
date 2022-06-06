#include "stdafx.h"
#include "Scene_ShapeMoment.h"


CScene_ShapeMoment::CScene_ShapeMoment()
{
}


CScene_ShapeMoment::~CScene_ShapeMoment()
{
	Release();
}

void CScene_ShapeMoment::Initialize(void)
{
	m_iLoseCount = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/T���̵�.bmp", L"T���̵�");

	m_pFrameKey = L"T���̵�";
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerMS>::Create_PlayerMS(420.f,540.f,0.f));
}

void CScene_ShapeMoment::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_ShapeMoment::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	Reset();
	Win_MS();
	LoseCount();
}

void CScene_ShapeMoment::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		0,	// 2,3 ���� :  ������� ��ġ X, Y
		0,
		WINCX,				// 4,5 ���� : ������� ����, ���� ����
		WINCY,
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		800,				// ������ ��Ʈ���� ����, ���� ����
		600,
		RGB(255, 254, 255));			// �����ϰ��� �ϴ� ����

								//Rectangle(hDC, 0, 0, WINCX, WINCY);
								//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_ShapeMoment::Release(void)
{
	CObjMgr::Get_Instance()->Delete_ID(OBJ_PLAYER);
}

void CScene_ShapeMoment::Reset(void)
{
	float m_fXX = (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_Info().vPos.x;
	float m_fYY = (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_Info().vPos.y;
	if (m_fXX > 442.f)
	{
		static_cast<CPlayerMS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Set_PlayerMSPos({ 420.f,540.f,0.f });
		m_iLoseCount += 1;
	}
	else if ((m_fXX < 420.f) && ((m_fYY < 260.f) || (m_fYY > 370.f)))
	{
		static_cast<CPlayerMS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Set_PlayerMSPos({ 420.f,540.f,0.f });
		m_iLoseCount += 1;
	}
}

void CScene_ShapeMoment::Win_MS(void)
{
	float m_fXX = (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_Info().vPos.x;
	float m_fYY = (CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Get_Info().vPos.y;
	if ((m_fXX < 150.f) && ((m_fYY > 260.f) && (m_fYY < 370.f)))
	{
		//static_cast<CPlayerMS*>(CObjMgr::Get_Instance()->Get_List(OBJ_PLAYER).front())->Set_PlayerMSPos({ 420.f,540.f,0.f });
		CSceneMgr::Get_Instance()->Scene_Change(SC_KSWIN);
	}
}

void CScene_ShapeMoment::LoseCount()
{
	if (m_iLoseCount >= 5)
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MSLOSE);
	}
}
