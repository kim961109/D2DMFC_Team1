#include "stdafx.h"
#include "Obj_Collision.h"


CObj_Collision::CObj_Collision()
{
}

CObj_Collision::CObj_Collision(float _fX, float _fY, float _fCX, float _fCY)
{
	m_tObjInfo.fX = _fX;
	m_tObjInfo.fY = _fY;

	m_tObjInfo.fCX = _fCX;
	m_tObjInfo.fCY = _fCY;
}

CObj_Collision::~CObj_Collision()
{
	Release();
}

void CObj_Collision::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Scene_KS.bmp", L"Scene_KS");
}

int CObj_Collision::Update(void)
{

	Update_Rect();
	return 0;
}

void CObj_Collision::Late_Update(void)
{
}

void CObj_Collision::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Scene_KS");

	GdiTransparentBlt(hDC, 					// ���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	// 2,3 ���� :  ������� ��ġ X, Y
		int(m_tRect.top),
		int(m_tObjInfo.fCX),				// 4,5 ���� : ������� ����, ���� ����
		int(m_tObjInfo.fCY),
		hMemDC,							// ��Ʈ���� ������ �ִ� DC
		0,								// ��Ʈ�� ��� ���� ��ǥ, X,Y
		0,
		int(m_tObjInfo.fCX),				// ������ ��Ʈ���� ����, ���� ����
		int(m_tObjInfo.fCY),
		RGB(254, 255, 255));			// �����ϰ��� �ϴ� ����
}

void CObj_Collision::Release(void)
{
}

void CObj_Collision::Update_Rect(void)
{
	m_tRect.left = m_tObjInfo.fX - m_tObjInfo.fCX * 0.5f;
	m_tRect.top = m_tObjInfo.fY - m_tObjInfo.fCY * 0.5f;
	m_tRect.right = m_tObjInfo.fX + m_tObjInfo.fCX * 0.5f;
	m_tRect.bottom = m_tObjInfo.fY + m_tObjInfo.fCY * 0.5f;
}
