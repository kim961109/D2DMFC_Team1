#include "stdafx.h"
#include "SceneMS_Lose.h"


CSceneMS_Lose::CSceneMS_Lose()
{
}


CSceneMS_Lose::~CSceneMS_Lose()
{
}

void CSceneMS_Lose::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/���ֿ���.bmp", L"���ֿ���");

	m_pFrameKey = L"���ֿ���";
}

void CSceneMS_Lose::Update(void)
{
}

void CSceneMS_Lose::Late_Update(void)
{
}

void CSceneMS_Lose::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		265,	// 2,3 ���� :  ������� ��ġ X, Y
		102,
		289,				// 4,5 ���� : ������� ����, ���� ����
		295,
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		289,				// ������ ��Ʈ���� ����, ���� ����
		295,
		RGB(255, 254, 255));			// �����ϰ��� �ϴ� ����

										//Rectangle(hDC, 0, 0, WINCX, WINCY);
										//CTileMgr::Get_Instance()->Render(hDC);
}

void CSceneMS_Lose::Release(void)
{
}
