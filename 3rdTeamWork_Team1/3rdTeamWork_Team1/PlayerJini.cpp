#include "stdafx.h"
#include "PlayerJini.h"

#include "ScrollMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CPlayerJini::CPlayerJini()
{
}


CPlayerJini::~CPlayerJini()
{
	Release();
}

void CPlayerJini::Initialize(void)
{
	//m_tInfo.vPos	= { 400.f, 300.f, 0.f };
	m_vPosMiniMap	= { 0.f, 0.f, 0.f };
	m_tInfo.vDir	= { 1.f, 0.f, 0.f };
	m_vDirLocal		= { 1.f, 0.f, 0.f };

	m_tInfo.vLook	= { 1.f, 0.f, 0.f };
	m_fSpeed		= 1.f;
	m_fAngle		= 0.f;
	m_fScale		= 1.0f;
	//m_fEllipse		= 50.f;

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

	m_strName = "순수하짐";
	m_strTag = "부모"; 
	lstrcpy(m_szName, L"순수하짐");
}

int CPlayerJini::Update(void)
{
	if(m_bDead)
		return OBJ_DEAD;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 크기에 따른 속도 지정
	m_fSpeed = m_fScale * 2.0f / (m_fScale * m_fScale * 0.8f);

	// 마우스 방향연산
	m_vMouseTemp = ::Get_Mouse();
	m_vMouseTemp.x -= iScrollX;
	m_vMouseTemp.y -= iScrollY;
	m_vDirLocal = m_vMouseTemp - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_vDirLocal);

	// 마우스 거리 재기
	float _DistanceX = m_vMouseTemp.x - m_tInfo.vPos.x;
	float _DistanceY = m_vMouseTemp.y - m_tInfo.vPos.y;
	m_fDistanceMouse = sqrtf(_DistanceX * _DistanceX + _DistanceY * _DistanceY);

	// 마우스 방향 이동 
	if (m_fDistanceMouse > 10.0f) // 마우스랑 일정거리 이상 가까워지면 이동안하게 (떨림방지)
	{
			m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		//m_tInfo.vPos.y += m_tInfo.vDir.y * m_fSpeed;
	}

	if (0 > m_tInfo.vPos.x)
		m_tInfo.vPos.x = 0.f;
	else if (2400 < m_tInfo.vPos.x)
		m_tInfo.vPos.x = 2400.f;
	else if (0 > m_tInfo.vPos.y)
		m_tInfo.vPos.y = 0.f;
	else if (1800 < m_tInfo.vPos.y)
		m_tInfo.vPos.y = 1800.f;

	Key_Input();

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
	
	// 반지름 계산해두기
	m_fRadius = (m_vBody[2].x - m_vBody[0].x) * 0.5;
	
	if(m_strTag == "부모")
		Offset();

	cout << "vPos.x = " << m_tInfo.vPos.x << "vPos.y = " << m_tInfo.vPos.y << endl;

	m_vPosMiniMap.x = m_tInfo.vPos.x / 2400.f * JINIMAPCX;
	m_vPosMiniMap.y = m_tInfo.vPos.y / 1800.f * JINIMAPCY;

	return OBJ_NOEVENT;
}

void CPlayerJini::Late_Update(void)
{
}

void CPlayerJini::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Ellipse(hDC,
		int(m_vBody[0].x + iScrollX),
		int(m_vBody[1].y + iScrollY),
		int(m_vBody[2].x + iScrollX),
		int(m_vBody[3].y + iScrollY));

	Ellipse(hDC,
		int(m_vPosMiniMap.x - 3.f + WINCX - JINIMAPCX),
		int(m_vPosMiniMap.y - 3.f + WINCY - JINIMAPCY),
		int(m_vPosMiniMap.x + 3.f + WINCX - JINIMAPCX),
		int(m_vPosMiniMap.y + 3.f + WINCY - JINIMAPCY));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	// 포신 그리기
	//MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	//LineTo(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y - 50.f);

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfCharSet = 129;
	m_labelFontInfo.lfHeight = m_fScale * 1.5 * 12;
	m_labelFontInfo.lfWidth = m_fScale * 1.5 * 6;
	//m_labelFontInfo.lfWeight = FW_BOLD;

	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);
	SetBkMode(hDC, OPAQUE); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	SetTextColor(hDC, RGB(255, 255, 255));

	TextOut(hDC, m_tInfo.vPos.x - m_fRadius * 0.7 + iScrollX, m_tInfo.vPos.y - m_fRadius * 0.2 + iScrollY, m_szName, lstrlen(m_szName));
	
	SelectObject(hDC, oldFont);
	DeleteObject(textFont);

	
}

void CPlayerJini::Release(void)
{
} 

//
void CPlayerJini::Offset()
{
	int		iOffSetX = WINCX >> 1;
	int		iOffSetY = WINCY >> 1;
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	int		iItvX = 2;
	int		iItvY = 2;

	CScrollMgr::Get_Instance()->Set_EScrollX(-m_tInfo.vPos.x + iOffSetX);
	CScrollMgr::Get_Instance()->Set_EScrollY(-m_tInfo.vPos.y + iOffSetY);

	//if (iOffSetX - iItvX > m_tInfo.vPos.x + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

	//if (iOffSetX + iItvX < m_tInfo.vPos.x + iScrollX)
	//	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

	//if (iOffSetY - iItvY > m_tInfo.vPos.y + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

	//if (iOffSetY + iItvY < m_tInfo.vPos.y + iScrollY)
	//	CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);

}

// 여기
void CPlayerJini::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		Attack();

		// 함수를 따로 떼던가
		// 먼저 크기를 반으로 나누고
		//m_fScale *= 0.5;

		// 분신 생성 및 크기 셋팅
		//CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbsractFactory<CPlayer>::Create(0.f, 0.f, 0.f)); // (마우스방향으로), Pos 셋팅을 원의 지름만큼.
		//CObjMgr::Get_Instance()->Get_ListBack(OBJ_PLAYER)->Set_Scale(m_fScale);
		//CObjMgr::Get_Instance()->Get_ListBack(OBJ_PLAYER)->Set_Tag("자식");

		// 
	}
}

void CPlayerJini::Attack()
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float   fPosX = (m_tInfo.vPos.x ) + ( m_tInfo.vDir.x * m_fRadius);
	float	fPosY = (m_tInfo.vPos.y ) + ( m_tInfo.vDir.y * m_fRadius);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYERCHILD, CAbstractFactory<CPlayerJini>::Create_SetPos(fPosX, fPosY, 0.f)); // (마우스방향으로), Pos 셋팅을 원의 지름만큼.
	dynamic_cast<CPlayerJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_PLAYERCHILD))->Set_Scale(m_fScale * 0.41);
	dynamic_cast<CPlayerJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_PLAYERCHILD))->Set_Tag("자식");
	
	m_fScale *= 0.59;
	
	cout << "vPos.x = " << m_tInfo.vPos.x << "vPos.y = " << m_tInfo.vPos.y << endl;
	cout << "new vPos.x = " << fPosX << "new vPos.y = " << fPosY << endl;
	cout << "iScrollX = " << iScrollX << "iScrollY = " << iScrollY << endl;
	cout << "vDir.x = " << m_tInfo.vDir.x << "vDir.y = " << m_tInfo.vDir.y << endl;

}

