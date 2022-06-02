#include "stdafx.h"
#include "PlayerJini.h"
#include "ScrollMgr.h"

CPlayerJini::CPlayerJini()
{
}


CPlayerJini::~CPlayerJini()
{
	Release();
}

void CPlayerJini::Initialize(void)
{
	m_tInfo.vPos	= { 400.f, 300.f, 0.f };
	m_tInfo.vDir	= { 1.f, 0.f, 0.f };
	m_vDirLocal		= { 1.f, 0.f, 0.f };

	m_tInfo.vLook	= { 1.f, 0.f, 0.f };
	m_fSpeed		= 2.f;
	m_fAngle		= 0.f;
	m_fScale		= 1.f;
	m_fEllipse		= 50.f;

	m_vBodyLocal[0] = { -50.f, 0.f, 0.f }; //left
	m_vBodyLocal[1] = { 0.f, -50.f, 0.f }; //top
	m_vBodyLocal[2] = { 50.f, 0.f, 0.f }; //right
	m_vBodyLocal[3] = { 0.f, 50.f, 0.f }; //bottom

	// 색상 랜덤 설정
	srand(unsigned int(time(NULL)));
	m_iPlayerColorR = rand() % 256;
	m_iPlayerColorG = rand() % 256;
	m_iPlayerColorB = rand() % 256;

	m_fDistanceMouse = 0.f;

	m_bScroll = true;
}

void CPlayerJini::Update(void)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();


	// 마우스 방향연산
	//m_tInfo.vPos.x += iScrollX;
	//m_tInfo.vPos.y += iScrollY;
	m_vMouseTemp = ::Get_Mouse();
	m_vMouseTemp.x -= iScrollX;
	m_vMouseTemp.y -= iScrollY;

	// 마우스 거리 재기
	float _DistanceX = m_vMouseTemp.x - m_tInfo.vPos.x;
	float _DistanceY = m_vMouseTemp.y - m_tInfo.vPos.y;
	m_fDistanceMouse = sqrtf(_DistanceX * _DistanceX + _DistanceY * _DistanceY);

	m_fSpeed = m_fScale * 3 / (m_fScale * m_fScale);

	m_vDirLocal = m_vMouseTemp - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_vDirLocal);
	/*D3DXVec3Normalize(&m_tInfo.vLook, &m_vLookLocal);
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
	m_fAngle = acosf(fDot);*/

	//if (m_tInfo.vPos.y < Get_Mouse().y)
	//	m_fAngle = 2.f * D3DX_PI - m_fAngle;

	// 마우스 방향 이동 
	// 마우스랑 일정거리 이상 가까워지면 이동안하게 (떨림방지)
	// 스크롤때문에 떨림
	if (m_fDistanceMouse > 10.0f)		
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		//m_tInfo.vPos.y += m_tInfo.vDir.y * m_fSpeed;
	}

	// 월드행렬 만들기
	D3DXMATRIX		matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// 월드행렬 적용
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vBody[i], &m_vBodyLocal[i], &m_tInfo.matWorld);
	}

	//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_vDirLocal, &m_tInfo.matWorld);

	// 안떨리게 시도 : 화면좌표 구해서 스크롤 안먹게
	//m_vPosScreen = { float(int(m_tInfo.vPos.x) % WINCX) , float(int(m_tInfo.vPos.y) % WINCY), 0.f };
	//float m_fr = m_tInfo.vPos.x - m_vBody[0].x;

	//if (m_vPosScreen.x - m_fr <= 330)
	//	m_bScroll = false;
	//else if (m_vPosScreen.x + m_fr >= 460)
	//	m_bScroll = false;
	//else if (m_vPosScreen.y - m_fr <= 240)
	//	m_bScroll = false;
	//else if (m_vPosScreen.y + m_fr >= 360)
	//	m_bScroll = false;

	//if (m_vDirBefore != m_tInfo.vDir)
	//	m_bScroll = true;

	Offset();
}

void CPlayerJini::Late_Update(void)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	m_iScrollXBefore = iScrollX;
	m_iScrollYBefore = iScrollY;

	m_vDirBefore = m_tInfo.vDir;
}

void CPlayerJini::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	//if (m_bScroll)
	//{
		Ellipse(hDC,
			int(m_vBody[0].x + iScrollX),
			int(m_vBody[1].y + iScrollY),
			int(m_vBody[2].x + iScrollX),
			int(m_vBody[3].y + iScrollY));
	//}
	//else
	//{
	//	Ellipse(hDC,
	//		int(m_vBody[0].x + m_iScrollXBefore),
	//		int(m_vBody[1].y + m_iScrollYBefore),
	//		int(m_vBody[2].x + m_iScrollXBefore),
	//		int(m_vBody[3].y + m_iScrollYBefore));
	//}
	

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	// 포신 그리기
	//MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	//LineTo(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y - 50.f);
}

void CPlayerJini::Release(void)
{
}

void CPlayerJini::Offset()
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 2;
	int		iItvY = 2;

	CScrollMgr::Get_Instance()->Set_EScrollX(- m_tInfo.vPos.x + iOffSetX);
	CScrollMgr::Get_Instance()->Set_EScrollY(- m_tInfo.vPos.y + iOffSetY);

	//if (iOffSetX - iItvX > m_tInfo.vPos.x + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	//if (iOffSetX + iItvX < m_tInfo.vPos.x + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	//if (iOffSetY - iItvY > m_tInfo.vPos.y + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	//if (iOffSetY + iItvY < m_tInfo.vPos.y + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

}

