#include "stdafx.h"
#include "Ball.h"


CBall::CBall()
{
}

CBall::CBall(D3DXVECTOR3 _vPos)
	:m_fAngle(0.f), m_bMove(false)
{
	m_tInfo.vPos = _vPos;
}


CBall::~CBall()
{
	Release();
}

void CBall::Initialize(void)
{
	m_tObjInfo.fCX = 30.f;
	m_tObjInfo.fCY = 30.f;

	m_vFirstPos = { 0.f,0.f,0.f };//로컬 좌표.
	m_vCurPos = m_vFirstPos;
	m_vMoveDir = { 0.f,0.f,0.f };

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Ball.bmp", L"Ball");
}

int CBall::Update(void)
{
	m_vCurPos = m_vFirstPos;

	m_fAngle += float(D3DX_PI / 6);

	if (m_bMove == true)
	{
		D3DXVECTOR3 m_vFriction = m_vMoveDir;// 마찰에 의해 감속시킬 벡터.
		D3DXVec3Normalize(&m_vFriction, &m_vFriction);//감속 벡터의 정규화
		m_tInfo.vPos -= 3.f * m_vMoveDir;// 공의 움직임.
		m_vMoveDir -= 0.0015f * m_vFriction; // 감속
		if (D3DXVec3Length(&m_vMoveDir) < 0.01f)// 공의 움직임 속도가 어느정도로 작아지면 멈춰라.
		{
			m_bMove = false;
		}
	}

	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotZ, m_fAngle);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
	
	D3DXVec3TransformCoord(&m_vCurPos, &m_vCurPos, &m_tInfo.matWorld);
	
	cout << m_tInfo.vPos.x << "\t" << m_tInfo.vPos.y << endl;

	Update_CollisionPos();
	return OBJ_NOEVENT;
}

void CBall::Late_Update(void)
{
}

void CBall::Render(HDC hDC)
{
	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Ball");

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tInfo.vPos.x - 15.f),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tInfo.vPos.y - 15.f),
		int(30.f),				// 4,5 인자 : 복사받을 가로, 세로 길이
		int(30.f),
		hMemDC,							// 비트맵을 가지고 있는 DC
		0,								// 비트맵 출력 시작 좌표, X,Y
		0,
		int(30.f),				// 복사할 비트맵의 가로, 세로 길이
		int(30.f),
		RGB(255, 255, 255));			// 제거하고자 하는 색상
}

void CBall::Release(void)
{
}

void CBall::Update_CollisionPos(void)
{
	m_tObjInfo.fX = m_tInfo.vPos.x;
	m_tObjInfo.fY = m_tInfo.vPos.y;
}

void CBall::Reset_Ball(void)
{
	m_bMove = false;
	m_vMoveDir = { 0.f,0.f,0.f };
	m_tInfo.vPos = { 230.f, 300.f, 0.f };
}
