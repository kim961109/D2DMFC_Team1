#include "stdafx.h"
#include "Snake_Body.h"


CSnake_Body::CSnake_Body()
{
}


CSnake_Body::~CSnake_Body()
{
}

void CSnake_Body::Initialize(void)
{	//유니코드 테스트
	//m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i] = m_vPoint[i];
	}

	m_fAngle = 0.f;
	m_fSpeed = 2.f;
}

int CSnake_Body::Update(void)
{
	Key_Input();

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= { 400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);

	}
	return 0;
}

void CSnake_Body::Late_Update(void)
{
}

void CSnake_Body::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
	}

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);
}

void CSnake_Body::Release(void)
{
}

void CSnake_Body::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
	}

	if (GetAsyncKeyState('S'))
	{
	}

	if (GetAsyncKeyState(VK_UP))
	{
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
	}

}

