#include "stdafx.h"
#include "PlayerMS.h"
#include "BmpMgr.h"
CPlayerMS::CPlayerMS()
{
}

CPlayerMS::CPlayerMS(float _fX, float _fY, float _fZ)
{
	m_tInfo.vPos.x = _fX;
	m_tInfo.vPos.y = _fY;
	m_tInfo.vPos.z = _fZ;

}

CPlayerMS::~CPlayerMS()
{
	Release();
}

void CPlayerMS::Initialize(void)
{
	//m_tInfo.vPos = { 100.f, 130.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_fAngle = 140;
	

	m_vPoint[0] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 30.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y - 30.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 30.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y + 30.f, 0.f };

	m_vleftPoint[0] = { m_tInfo.vPos.x - 40.f,  m_tInfo.vPos.y - 30.f, 0.f };
	m_vleftPoint[1] = { m_tInfo.vPos.x - 30.f,  m_tInfo.vPos.y - 30.f, 0.f };
	m_vleftPoint[2] = { m_tInfo.vPos.x - 30.f,  m_tInfo.vPos.y - 5.f, 0.f };
	m_vleftPoint[3] = { m_tInfo.vPos.x - 40.f,  m_tInfo.vPos.y - 5.f, 0.f }; 

	m_vrightPoint[0] = { m_tInfo.vPos.x + 30.f,  m_tInfo.vPos.y - 30.f, 0.f };
	m_vrightPoint[1] = { m_tInfo.vPos.x + 40.f,  m_tInfo.vPos.y - 30.f, 0.f };
	m_vrightPoint[2] = { m_tInfo.vPos.x + 40.f,  m_tInfo.vPos.y - 5.f, 0.f };
	m_vrightPoint[3] = { m_tInfo.vPos.x + 30.f,  m_tInfo.vPos.y - 5.f, 0.f };

	m_vleftDownPoint[0] = { m_tInfo.vPos.x - 40.f,  m_tInfo.vPos.y + 5.f, 0.f };
	m_vleftDownPoint[1] = { m_tInfo.vPos.x - 30.f,  m_tInfo.vPos.y + 5.f, 0.f };
	m_vleftDownPoint[2] = { m_tInfo.vPos.x - 30.f,  m_tInfo.vPos.y + 30.f, 0.f };
	m_vleftDownPoint[3] = { m_tInfo.vPos.x - 40.f,  m_tInfo.vPos.y + 30.f, 0.f };

	m_vrightDownPoint[0] = { m_tInfo.vPos.x + 30.f,  m_tInfo.vPos.y + 5.f, 0.f };
	m_vrightDownPoint[1] = { m_tInfo.vPos.x + 40.f,  m_tInfo.vPos.y + 5.f, 0.f };
	m_vrightDownPoint[2] = { m_tInfo.vPos.x + 40.f,  m_tInfo.vPos.y + 30.f, 0.f };
	m_vrightDownPoint[3] = { m_tInfo.vPos.x + 30.f,  m_tInfo.vPos.y + 30.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i] = m_vPoint[i];
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginleftPoint[i] = m_vleftPoint[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		m_vOriginrightPoint[i] = m_vrightPoint[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		m_vOriginleftDownPoint[i] = m_vleftDownPoint[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		m_vOriginrightDownPoint[i] = m_vrightDownPoint[i];
	}

	m_fSpeed = 5.f;
}

int CPlayerMS::Update(void)
{
	Key_Input(); 

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	for (int i = 0; i < 4; ++i)  
	{
		m_vPoint[i] = m_vOriginPoint[i];
		//m_vPoint[i] -= {100.f, 130.f, 0.f};
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
	}
	for (int i = 0; i < 4; ++i)
	{
		m_vleftPoint[i] = m_vOriginleftPoint[i];
		//m_vleftPoint[i] -= { 100.f, 130.f, 0.f};
		D3DXVec3TransformCoord(&m_vleftPoint[i], &m_vleftPoint[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vrightPoint[i] = m_vOriginrightPoint[i];
		//m_vrightPoint[i] -= { 100.f, 130.f, 0.f};
		D3DXVec3TransformCoord(&m_vrightPoint[i], &m_vrightPoint[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vleftDownPoint[i] = m_vOriginleftDownPoint[i];
		//m_vleftDownPoint[i] -= { 100.f, 130.f, 0.f};
		D3DXVec3TransformCoord(&m_vleftDownPoint[i], &m_vleftDownPoint[i], &m_tInfo.matWorld);
	}

	for (int i = 0; i < 4; ++i)
	{
		m_vrightDownPoint[i] = m_vOriginrightDownPoint[i];
		//m_vrightDownPoint[i] -= {  100.f, 130.f, 0.f};
		D3DXVec3TransformCoord(&m_vrightDownPoint[i], &m_vrightDownPoint[i], &m_tInfo.matWorld);
	}

	if (m_tInfo.vPos.y >= 230|| m_tInfo.vPos.y <= 105)
	{
		m_tInfo.vPos = { 100.f,120.f,0.f };
	}
	

	return 0;
}

void CPlayerMS::Late_Update(void)
{
	if (m_tInfo.vPos.y == 400)
	{
		m_tInfo.vPos = { 100.f,120.f,0.f };
	}
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
	LineTo(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y);
	MoveToEx(hDC, (int)m_vleftPoint[0].x, (int)m_vleftPoint[0].y, nullptr);


	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vleftPoint[i].x, (int)m_vleftPoint[i].y);

		if (i > 0)
			continue;

	}

	
	LineTo(hDC, m_vleftPoint[0].x, m_vleftPoint[0].y);
	MoveToEx(hDC, (int)m_vrightPoint[0].x, (int)m_vrightPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vrightPoint[i].x, (int)m_vrightPoint[i].y);

		if (i > 0)
			continue;
	}
	LineTo(hDC, m_vrightPoint[0].x, m_vrightPoint[0].y);

	MoveToEx(hDC, (int)m_vleftDownPoint[0].x, (int)m_vleftDownPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vleftDownPoint[i].x, (int)m_vleftDownPoint[i].y);

		if (i > 0)
			continue;
	}

	LineTo(hDC, m_vleftDownPoint[0].x, m_vleftDownPoint[0].y);
	
	MoveToEx(hDC, (int)m_vrightDownPoint[0].x, (int)m_vrightDownPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vrightDownPoint[i].x, (int)m_vrightDownPoint[i].y);

		if (i > 0)
			continue;
	}

	LineTo(hDC, m_vrightDownPoint[0].x, m_vrightDownPoint[0].y);

	//MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	Ellipse(hDC,
		m_tInfo.vPos.x - 30.f, m_tInfo.vPos.y - 30.f,
		m_tInfo.vPos.x + 30.f, m_tInfo.vPos.y + 30.f);
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
