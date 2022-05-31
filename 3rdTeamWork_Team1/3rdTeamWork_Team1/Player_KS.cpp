#include "stdafx.h"
#include "Player_KS.h"


CPlayer_KS::CPlayer_KS()
{
}


CPlayer_KS::~CPlayer_KS()
{
	Release();
}

void CPlayer_KS::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_fSpeed = 5.f;
	//m_tInfo.vLook = { 1.f, 0.f, 0.f };

	m_vGunPoint[0] = { 0.f, -5.f, 0.f };
	m_vGunPoint[1] = { 40.f, -5.f, 0.f };
	m_vGunPoint[2] = { 40.f, 5.f, 0.f };
	m_vGunPoint[3] = { 0.f, 5.f, 0.f };

	m_vBodyPoint[0] = { -20.f, -20.f , 0.f };
	m_vBodyPoint[1] = { 20.f, -20.f , 0.f };
	m_vBodyPoint[2] = { 20.f, 20.f , 0.f };
	m_vBodyPoint[3] = { -20.f, 20.f , 0.f };
}

void CPlayer_KS::Update(void)
{
	//총구가 바라보는 방향으로의 각도를 구함.
	Change_GunAngle();

	Key_Input();
}

void CPlayer_KS::Late_Update(void)
{
}

void CPlayer_KS::Render(HDC hDC)
{
	//몸체
	Ellipse(hDC,
		(int)(m_vBodyPoint[0].x) ,
		(int)(m_vBodyPoint[0].y) ,
		(int)(m_vBodyPoint[2].x) ,
		(int)(m_vBodyPoint[2].y));//몸통만 표시

	//몸체
	//MoveToEx(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y, nullptr);
	//for (int i = 1; i < 4; ++i)
	//{
	//	LineTo(hDC, (int)m_vBodyPoint[i].x, (int)m_vBodyPoint[i].y);
	//}
	//LineTo(hDC, (int)m_vBodyPoint[0].x, (int)m_vBodyPoint[0].y);

	//총방향.
	MoveToEx(hDC, (int)m_vGunPoint[0].x, (int)m_vGunPoint[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vGunPoint[i].x, (int)m_vGunPoint[i].y);
	}
	LineTo(hDC, (int)m_vGunPoint[0].x, (int)m_vGunPoint[0].y);
}

void CPlayer_KS::Release(void)
{
}

void CPlayer_KS::Key_Input(void)
{
	// 총구 방향이 변하는지 테스트.
	/*if (GetAsyncKeyState('A'))
		m_fGunAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('D'))
		m_fGunAngle += D3DXToRadian(3.f);*/

	// 플레이어의 이동.
	/*if (GetAsyncKeyState('A'))
		m_fGunAngle -= D3DXToRadian(3.f);*/
	

}

void CPlayer_KS::Change_GunAngle(void)
{
	m_tInfo.vDir = ::Get_Mouse() - m_tInfo.vPos;

}
