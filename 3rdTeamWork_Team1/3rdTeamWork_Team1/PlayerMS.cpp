#include "stdafx.h"
#include "PlayerMS.h"

CPlayerMS::CPlayerMS()
{
}

CPlayerMS::~CPlayerMS()
{
	Release();
}

void CPlayerMS::Initialize(void)
{
	m_tInfo.vPos = { 400.f,300.f,0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	 
	

	m_vPoint[0] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 30.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 30.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 30.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + 30.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i] = m_vPoint[i];
	}

	m_fSpeed = 5.f;
}

int CPlayerMS::Update(void)
{
	Key_Input(); 

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)  
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= { 400.f, 300.f, 0.f };
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}

	return 0;
}

void CPlayerMS::Late_Update(void)
{
}

void CPlayerMS::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);

	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);

		if (i > 0)
			continue;

		Ellipse(hDC,
			(int)m_vPoint[i].x - 5.f,
			(int)m_vPoint[i].y - 5.f,
			(int)m_vPoint[i].x + 5.f,
			(int)m_vPoint[i].y + 5.f);
	}

	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);

	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);

}

void CPlayerMS::Release(void)
{
}

void CPlayerMS::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle) - m_tInfo.vLook.y * sinf(m_fAngle);
		//m_tInfo.vDir.y = m_tInfo.vLook.x * sinf(m_fAngle) + m_tInfo.vLook.y * cosf(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
		
		
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('S'))
	{
		//m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle) - m_tInfo.vLook.y * sinf(m_fAngle);
		//m_tInfo.vDir.y = m_tInfo.vLook.x * sinf(m_fAngle) + m_tInfo.vLook.y * cosf(m_fAngle);

		D3DXVec3TransformNormal(&m_tInfo.vDir,	&m_tInfo.vLook, &m_tInfo.matWorld);
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
	}

	if (GetAsyncKeyState('A'))
		m_fAngle -= D3DXToRadian(3.f);

	if (GetAsyncKeyState('D'))
		m_fAngle += D3DXToRadian(3.f);

}
