#include "stdafx.h"
#include "Monster_KS.h"


CMonster_KS::CMonster_KS()
{
}

CMonster_KS::CMonster_KS(D3DXVECTOR3 _vPos)
{
	m_tInfo.vPos = _vPos;
	m_vFirstPos = _vPos;
}


CMonster_KS::~CMonster_KS()
{
	Release();
}

void CMonster_KS::Initialize(void)
{
	m_iHp = 5;
	//m_tInfo.vLook = { 1.f, 0.f, 0.f };
}

int CMonster_KS::Update(void)
{
	if (0 >= m_iHp)
	{
		return OBJ_DEAD;
	}

	m_tRect.left = m_tInfo.vPos.x - 20.f;
	m_tRect.top = m_tInfo.vPos.y - 20.f;
	m_tRect.right = m_tInfo.vPos.x + 20.f;
	m_tRect.bottom = m_tInfo.vPos.y + 20.f;

	return OBJ_NOEVENT;
}

void CMonster_KS::Late_Update(void)
{
}

void CMonster_KS::Render(HDC hDC)
{
	m_tInfo.vPos = m_vFirstPos;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	m_tInfo.vPos.x += iScrollX;
	m_tInfo.vPos.y += iScrollY;

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster_KS::Release(void)
{
}
