#include "stdafx.h"
#include "Scene_MinSungJJang.h"
#include "TileMgr.h"



CScene_MinSungJJang::CScene_MinSungJJang()
{
}


CScene_MinSungJJang::~CScene_MinSungJJang()
{
	Release();
}

void CScene_MinSungJJang::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/����.bmp", L"����");

	m_pFrameKey = L"����";
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerMS>::Create_Player());
	CTileMgr::Get_Instance()->Initialize();
}

void CScene_MinSungJJang::Update(void)
{
	CTileMgr::Get_Instance()->Update();
	
	CObjMgr::Get_Instance()->Update();
}

void CScene_MinSungJJang::Late_Update(void)
{
	CTileMgr::Get_Instance()->Late_Update();
	CObjMgr::Get_Instance()->Late_Update();

}

void CScene_MinSungJJang::Render(HDC hDC)
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
		799,				// ������ ��Ʈ���� ����, ���� ����
		582,
		RGB(0, 0, 0));			// �����ϰ��� �ϴ� ����

	//Rectangle(hDC, 0, 0, WINCX, WINCY);
	CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);

}

void CScene_MinSungJJang::Release(void)
{
}
