#include "stdafx.h"
#include "Snake_Head.h"


CSnake_Head::CSnake_Head()
{
}

CSnake_Head::~CSnake_Head()
{
}

void CSnake_Head::Initialize(void)
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i] = m_vPoint[i];//키누를때만움직이게하려고 originpoint 만듬
	}

	m_fAngle = 0.f;
	m_fSpeed = 1.f;
}

int CSnake_Head::Update(void)
{
	if (GetTickCount() - m_dKeyInput > 800)
	{
		Key_Input();
	}
	//m_tInfo.vPos += m_tInfo.vLook * m_fSpeed;
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	m_tInfo.vPos += m_tInfo.vDir*m_fSpeed;
	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= { 400.f, 300.f, 0.f };

		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	return 0;
}

void CSnake_Head::Late_Update(void)
{
}

void CSnake_Head::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 1)
			continue;

		Ellipse(hDC,
			(int)m_vPoint[i].x - 5,
			(int)m_vPoint[i].y - 5,
			(int)m_vPoint[i].x + 5,
			(int)m_vPoint[i].y + 5);
	}

	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
}

void CSnake_Head::Release(void)
{
}

void CSnake_Head::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
	}

	if (GetAsyncKeyState('S'))
	{
	}

	/*if (GetAsyncKeyState(VK_UP))
	{	
		m_fAngle -= D3DXToRadian(90.f);
		m_dKeyInput = GetTickCount();
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_fAngle += D3DXToRadian(90.f);
		m_dKeyInput = GetTickCount();
	}/**/
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_fAngle -= D3DXToRadian(90.f);
		m_dKeyInput = GetTickCount();
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_fAngle += D3DXToRadian(90.f);
		m_dKeyInput = GetTickCount();
	}

}
