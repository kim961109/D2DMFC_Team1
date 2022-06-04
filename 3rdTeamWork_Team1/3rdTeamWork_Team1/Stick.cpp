#include "stdafx.h"
#include "Stick.h"


CStick::CStick()
{
}


CStick::~CStick()
{
	Release();
}

void CStick::Initialize(void)
{
	m_iMoveTimeUp = 0;
	m_iMoveTimeDown = 0;
	m_bMove = false;
	m_bGameStart = false;
	m_bHit = false;
	m_tInfo.vPos = {230.f, 300.f, 0.f};

	m_tInfo.vDir = { 1.f,0.f,0.f };
	m_tInfo.vLook = { 1.f,0.f,0.f };
	m_vMoveDir = { 1.f,0.f,0.f };

	m_vPointPos[0] = { 0.f, -3.f, 0.f };
	m_vPointPos[1] = { 300.f, -3.f, 0.f };
	m_vPointPos[2] = { 300.f, 3.f, 0.f };
	m_vPointPos[3] = { 0.f, 3.f, 0.f };//막대기 네점의 좌표.
	for (int i = 0; 4 > i; ++i)
	{
		m_vOriginPointPos[i] = m_vPointPos[i];
	}
}

int CStick::Update(void)
{
	Key_Start();
	Key_Input();

	for (int i = 0; 4 > i; ++i)
	{
		m_vPointPos[i] = m_vOriginPointPos[i];
	}

	if (m_bGameStart == true)
	{
		if (m_bMove == true)
		{
			Move_Stick();
		}
		else if (m_bMove == false)
		{
			Check_Angle();
		}
	}

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);//총구의 회전.
	D3DXMatrixTranslation(&matTrans, (m_tInfo.vPos.x + m_tInfo.vDir.x), (m_tInfo.vPos.y + m_tInfo.vDir.y), 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;//총구의 월드변환.

	for (int i = 0; 4 > i; ++i)
	{
		D3DXVec3TransformCoord(&m_vPointPos[i], &m_vPointPos[i], &m_tInfo.matWorld);
	}

	return 0;
}

void CStick::Late_Update(void)
{
}

void CStick::Render(HDC hDC)
{
	MoveToEx(hDC, (int)m_vPointPos[0].x, (int)m_vPointPos[0].y, nullptr);
	for (int i = 1; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPointPos[i].x, (int)m_vPointPos[i].y);
	}
	LineTo(hDC, (int)m_vPointPos[0].x, (int)m_vPointPos[0].y);
}

void CStick::Release(void)
{
}

void CStick::Key_Input(void)
{
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (m_bGameStart == true)
		{
			m_bMove = true;
		}
	}
	
}

void CStick::Key_Start(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		m_bGameStart = true;
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_Z))
	{
		m_bHit = false;
		//Reset_Ball
		static_cast<CBall*>(CObjMgr::Get_Instance()->Get_List(OBJ_BALL).front())->Reset_Ball();
	}
}

void CStick::Check_Angle(void)
{
	D3DXVECTOR3 New_vDir = { Get_Mouse().x - 230.f, Get_Mouse().y - 300.f, 0.f };

	D3DXVec3Normalize(&New_vDir, &New_vDir);
	m_vMoveDir = New_vDir;

	m_tInfo.vDir = 20.f * New_vDir;

	float fDot = D3DXVec3Dot(&New_vDir, &m_tInfo.vLook);

	m_fAngle = acosf(fDot);

	if (300.f > Get_Mouse().y)
		m_fAngle = 2.f * D3DX_PI - m_fAngle;

}

void CStick::Move_Stick(void)
{
	if (m_iMoveTimeUp < 20)
	{
		m_tInfo.vPos += 4.f * m_vMoveDir;
		m_iMoveTimeUp += 1;
	}
	else if(m_iMoveTimeDown < 10)
	{
		m_tInfo.vPos -= 8.f * m_vMoveDir;
		m_iMoveTimeDown += 1;
	}

	if ((m_iMoveTimeUp > 19) && (m_iMoveTimeDown > 9))
	{
		m_iMoveTimeUp = 0;
		m_iMoveTimeDown = 0;
		m_bMove = false;
		if (m_bHit == false)
		{
			static_cast<CBall*>(CObjMgr::Get_Instance()->Get_List(OBJ_BALL).front())->Set_Move(m_vMoveDir);
			static_cast<CBall*>(CObjMgr::Get_Instance()->Get_List(OBJ_BALL).front())->Set_MoveBool(true);
			m_bHit = true;
		}
	}
}
