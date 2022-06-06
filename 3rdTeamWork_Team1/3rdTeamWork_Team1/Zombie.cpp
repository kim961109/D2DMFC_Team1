#include "stdafx.h"
#include "Zombie.h"


CZombie::CZombie()
{
}

CZombie::CZombie(D3DXVECTOR3 vPos, CObj* pObj)
	:m_fSpeed(1.5f), m_iHp(6), m_pTarget(pObj), fRadian(0.f), fAngleA(0.f), m_bChase(true)
{
	m_tObjInfo.fX = vPos.x;
	m_tObjInfo.fY = vPos.y;
	m_eCurState = END;
	m_ePreState = END;
}

CZombie::~CZombie()
{
	Release();
}

void CZombie::Initialize(void)
{
	m_tObjInfo.fCX = 16.f;
	m_tObjInfo.fCY = 32.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Zombie.bmp", L"Zombie");

	m_pFrameKey = L"Zombie";
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();
}

int CZombie::Update(void)
{
	if (0 >= m_iHp)
	{
		return OBJ_DEAD;
	}

	ChaseAngle();
	Motion_Change();

	Update_RectZombie();

	//cout << "MONSTER: " << m_tObjInfo.fX << m_tObjInfo.fY << endl;
	return OBJ_NOEVENT;
}

void CZombie::Late_Update(void)
{
	Move_Frame();
}

void CZombie::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);

	GdiTransparentBlt(hDC, 					// 복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	// 2,3 인자 :  복사받을 위치 X, Y
		int(m_tRect.top),
		2 * int(m_tObjInfo.fCX),				// 4,5 인자 : 복사받을 가로, 세로 길이
		2 * int(m_tObjInfo.fCY),
		hMemDC,							// 비트맵을 가지고 있는 DC
		m_tFrame.iFrameStart * (int)m_tObjInfo.fCX,		// 비트맵 출력 시작 좌표, X,Y
		m_tFrame.iMotion * (int)m_tObjInfo.fCY,
		(int)m_tObjInfo.fCX,				// 복사할 비트맵의 가로, 세로 길이
		(int)m_tObjInfo.fCY,
		RGB(255, 255, 255));			// 제거하고자 하는 색상

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CZombie::Release(void)
{
}

void CZombie::ChaseAngle(void)
{

	float		fWidth = m_pTarget->Get_ObjInfo().fX - m_tObjInfo.fX;
	float		fHeight = m_pTarget->Get_ObjInfo().fY - m_tObjInfo.fY;

	float		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	/*if (fDiagonal < 400.f)
	{
		m_bChase = true;
	}
	else
	{
		m_bChase = false;
	}*/

	fRadian = acosf(fWidth / fDiagonal); // acos값으로 나올 수 있는 각도의 범위는 0~180도 사이 값에 해당한다.

	if (m_pTarget->Get_ObjInfo().fY > m_tObjInfo.fY)
		fRadian = (2 * PI) - fRadian;

	fAngleA = fRadian * 180 / PI;

	if (m_bChase == true)
	{
		m_tObjInfo.fX += m_fSpeed * cosf((fAngleA)* PI / 180.f);
		m_tObjInfo.fY -= m_fSpeed * sinf((fAngleA)* PI / 180.f);
	}
}

void CZombie::Update_RectZombie(void)
{
	int		iScrollX =  (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY =  (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_tRect.left = LONG(m_tObjInfo.fX - 0.5f * m_tObjInfo.fCX + iScrollX);
	m_tRect.top = LONG(m_tObjInfo.fY - 0.5f * m_tObjInfo.fCY + iScrollY);
	m_tRect.right = LONG(m_tObjInfo.fX + 1.5f * m_tObjInfo.fCX + iScrollX);
	m_tRect.bottom = LONG(m_tObjInfo.fY + 1.5f * m_tObjInfo.fCY + iScrollY);
}

void CZombie::Motion_Change(void)
{
	if (m_bChase == true)
	{
		if ((fAngleA > 45.f) && (fAngleA <= 135.f))
		{
			STATEID = WALK_UP;
		}
		else if ((fAngleA > 225.f) && (fAngleA <= 315.f))
		{
			STATEID = WALK_DOWN;
		}
		else if ((fAngleA > 315.f) || (fAngleA <= 45.f))
		{
			STATEID = WALK_RIGHT;
		}
		else if ((fAngleA > 135.f) && (fAngleA <= 225.f))
		{
			STATEID = WALK_LEFT;
		}
	}
	else if (m_bChase == false)
	{
		STATEID = IDLE;
	}
	
	m_eCurState = STATEID;
	if (m_ePreState != m_eCurState)
	{
		switch (STATEID)
		{
		case CZombie::WALK_DOWN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 0;
			break;
		case CZombie::WALK_RIGHT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 1;
			break;
		case CZombie::WALK_UP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 2;
			break;
		case CZombie::WALK_LEFT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iMotion = 3;
			break;
		case CZombie::IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iMotion = 0;
			break;
		}

		m_ePreState = m_eCurState;
	}
}
