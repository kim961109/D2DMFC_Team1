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
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/�����̵�.bmp", L"�����̵�");

	m_pFrameKey = L"�����̵�";
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayerMS>::Create_SetPos(100.f,200.f,0.f));
}

void CScene_ShapeMoment::Update(void)
{
	CObjMgr::Get_Instance()->Update();
}

void CScene_ShapeMoment::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
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
		801,				// ������ ��Ʈ���� ����, ���� ����
		601,
		RGB(0, 0, 0));			// �����ϰ��� �ϴ� ����

								//Rectangle(hDC, 0, 0, WINCX, WINCY);
								//CTileMgr::Get_Instance()->Render(hDC);
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene_ShapeMoment::Release(void)
{
}
