#include "stdafx.h"
#include "Bullet_KS.h"


CBullet_KS::CBullet_KS()
{
}

CBullet_KS::CBullet_KS(float _fAngle, D3DXVECTOR3 vA, D3DXVECTOR3 vB)
	:m_fAngle(_fAngle), m_fSpeed(8.f)
{
	m_tInfo.vPos.x = 0.5f * (vA.x + vB.x);
	m_tInfo.vPos.y = 0.5f * (vA.y + vB.y);
	m_tInfo.vPos.z = 0.5f * (vA.z + vB.z);
	m_tInfo.vDir = { 1,0,0 };

	m_bDead = false;
}

CBullet_KS::~CBullet_KS()
{
	Release();
}

void CBullet_KS::Initialize(void)
{
	m_tInfo.vDir.x = 1.f * cosf(m_fAngle);
	m_tInfo.vDir.y = 1.f * sinf(m_fAngle);
	m_tInfo.vDir.z = 0.f;
}

int CBullet_KS::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tRect.left = m_tInfo.vPos.x - 5.f;
	m_tRect.top = m_tInfo.vPos.y - 5.f;
	m_tRect.right = m_tInfo.vPos.x + 5.f;
	m_tRect.bottom = m_tInfo.vPos.y + 5.f;

	Move_Bullet_KS();
	
	return OBJ_NOEVENT;
}

void CBullet_KS::Late_Update(void)
{
}

void CBullet_KS::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet_KS::Release(void)
{
}

void CBullet_KS::Move_Bullet_KS(void)
{
	m_tInfo.vPos.x += m_fSpeed * m_tInfo.vDir.x;
	m_tInfo.vPos.y += m_fSpeed * m_tInfo.vDir.y;
}
