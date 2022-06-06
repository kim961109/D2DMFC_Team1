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
	m_vPosMiniMap = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_vDirLocal = { 1.f, 0.f, 0.f };

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 1.f;
	m_fAngle = 0.f;
	m_fScale = 1.0f;
	//m_fScaleSum = 0.f;
	//m_fScore = 0.f;
	//m_fEllipse		= 50.f;

	m_vBodyLocal[0] = { -50.f, 0.f, 0.f }; //left
	m_vBodyLocal[1] = { 0.f, -50.f, 0.f }; //top
	m_vBodyLocal[2] = { 50.f, 0.f, 0.f }; //right
	m_vBodyLocal[3] = { 0.f, 50.f, 0.f }; //bottom

	m_fRadius = (m_vBodyLocal[2].x - m_vBodyLocal[0].x) * 0.5;
										  // 색상 랜덤 설정
	srand(unsigned int(time(NULL)));
	m_iPlayerColorR = rand() % 256;
	m_iPlayerColorG = rand() % 256;
	m_iPlayerColorB = rand() % 256;

	m_fDistanceMouse = 0.f;

	m_strTag = "부모";
	lstrcpy(m_szName, L"순수하짐");

	m_dwAttackMove = GetTickCount();
	m_bMouseMove = false;
	m_bBirth = false;

	m_vAttackPos = { 0.f, 0.f, 0.f };
	m_vAttackDir = { 0.f, 0.f, 0.f };

}

int CPlayerJini::Update(void)
{

	if (m_bDead)
		return OBJ_DEAD;

	if (m_strTag != "부모")
		m_bBirth = true;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// 크기에 따른 속도 지정
	m_fSpeed = 1.5f / m_fScale;
	if (m_fSpeed > 3.f)
		m_fSpeed = 3.f;
	else if (m_fSpeed < 0.5f)
		m_fSpeed = 0.5f;

	// 분열 공격 시, 이동
	if (m_bBirth & m_strTag != "부모")
	{
		if(m_strTag == "자식")
			m_tInfo.vPos += m_vAttackDir * 5.f * g_fRenderPercent;
		else
			m_tInfo.vPos += m_vAttackDir * 4.f * g_fRenderPercent;

		if (GetTickCount() - m_dwAttackMove > 300)
		{
			m_bBirth = false;
			m_fSpeed = 1.f / m_fScale;
			if (m_fSpeed > 3.f)
				m_fSpeed = 3.f;
			else if (m_fSpeed < 0.5f)
				m_fSpeed = 0.5f;
			m_vAttackDir = { 0.f, 0.f, 0.f };
		}
	}

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
	if (!m_bBirth & m_fDistanceMouse > 10.0f) // 마우스랑 일정거리 이상 가까워지면 이동안하게 (떨림방지)
	{
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
		//m_tInfo.vPos.y += m_tInfo.vDir.y * m_fSpeed;
	}


	// 화면 안벗어나게
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

	if (m_strTag == "부모")
		Offset();

	//cout << "vPos.x = " << m_tInfo.vPos.x << "\t vPos.y = " << m_tInfo.vPos.y << "\t m_fScale = " << m_fScale << "\t m_fScore = " << m_fScore << "\t m_fScaleSum = " << m_fScaleSum << endl;

	m_vPosMiniMap.x = m_tInfo.vPos.x / 2400.f * JINIMAPCX;
	m_vPosMiniMap.y = m_tInfo.vPos.y / 1800.f * JINIMAPCY;

	return OBJ_NOEVENT;
}

void CPlayerJini::Late_Update(void)
{
	// 일정크기 이상 커지면 줌 아웃
	if (g_fScore > 7000.f * (g_fScaleCount + 1.f))
	{
		++g_fScaleCount;
		m_fRenderPercentTemp = g_fRenderPercent * 0.5f;
		g_bZoomOut_Jini = true;
	}

	// 일정크기 이상 작아지면 줌 인
	if ((g_fScaleCount != 0.f) && g_fScore < (7000.f * g_fScaleCount))
	{
		--g_fScaleCount;
		m_fRenderPercentTemp = g_fRenderPercent * 2.f;
		g_bZoomIn_Jini = true;
	}

	if (g_bZoomOut_Jini & g_fRenderPercent > m_fRenderPercentTemp)
		g_fRenderPercent -= 0.01f;
	else
		g_bZoomOut_Jini = false;

	if (g_bZoomIn_Jini & g_fRenderPercent < m_fRenderPercentTemp)
		g_fRenderPercent += 0.01f;
	else
		g_bZoomIn_Jini = false;

	// 점수 출력용
	int iScoreTemp = (int)g_fScore;
	swprintf_s(m_szScore, L"순수하짐 : %d", iScoreTemp);

	cout << "vPos.x = " << m_tInfo.vPos.x << "\t vPos.y = " << m_tInfo.vPos.y << "\t m_fScale = " << m_fScale << "\t g_fScore = " << g_fScore << endl;
}

void CPlayerJini::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	//Ellipse(hDC,
	//	int(m_vBody[0].x + iScrollX),
	//	int(m_vBody[1].y + iScrollY),
	//	int(m_vBody[2].x + iScrollX),
	//	int(m_vBody[3].y + iScrollY));

	Ellipse(hDC,
		int(m_tInfo.vPos.x - ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollX),
		int(m_tInfo.vPos.y - ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollY),
		int(m_tInfo.vPos.x + ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollX),
		int(m_tInfo.vPos.y + ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollY));

	Ellipse(hDC,
		int(m_vPosMiniMap.x - 3.f + WINCX - JINIMAPCX),
		int(m_vPosMiniMap.y - 3.f + WINCY - JINIMAPCY),
		int(m_vPosMiniMap.x + 3.f + WINCX - JINIMAPCX),
		int(m_vPosMiniMap.y + 3.f + WINCY - JINIMAPCY));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfCharSet = 129;
	m_labelFontInfo.lfHeight = m_fScale * g_fRenderPercent * 1.8 * 12;
	m_labelFontInfo.lfWidth = m_fScale * g_fRenderPercent * 1.8 * 6;
	//m_labelFontInfo.lfWeight = FW_BOLD;

	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);
	SetBkMode(hDC, OPAQUE); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	SetTextColor(hDC, RGB(255, 255, 255));

	TextOut(hDC, m_tInfo.vPos.x - m_fRadius * 0.8 * g_fRenderPercent + iScrollX, 
				m_tInfo.vPos.y - m_fRadius * 0.2 * g_fRenderPercent + iScrollY, 
				m_szName, lstrlen(m_szName));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);


	LOGFONT m_labelFontInfo2{};
	m_labelFontInfo2.lfCharSet = 129;
	m_labelFontInfo2.lfHeight = 16;
	m_labelFontInfo2.lfWidth = 8;
	m_labelFontInfo.lfWeight = FW_BOLD;

	HFONT textFont2, oldFont2;
	textFont2 = CreateFontIndirect(&m_labelFontInfo2);
	oldFont2 = (HFONT)SelectObject(hDC, textFont2);
	SetBkMode(hDC, OPAQUE); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(0, 10, 17));
	SetTextColor(hDC, RGB(255, 255, 255));

	TextOut(hDC, 650.f, 20.f, m_szScore, lstrlen(m_szScore));

	SelectObject(hDC, oldFont2);
	DeleteObject(textFont2);

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

	CScrollMgr::Get_Instance()->Set_EScrollX(-m_tInfo.vPos.x + iOffSetX);
	CScrollMgr::Get_Instance()->Set_EScrollY(-m_tInfo.vPos.y + iOffSetY);

}

// 여기
void CPlayerJini::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		Attack(m_tInfo.vDir, 0.35f);
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_CONTROL))
	{
		AttackRound();
	}

	/*if (CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		CSceneMgr::Get_Instance()->Scene_Change(SC_MAIN);
	}*/

	if (CKeyMgr::Get_Instance()->Key_Down('1'))
	{
		g_fScore = 6990.f * (g_fScaleCount + 1.f);
		m_fScale = 4.5f;
	}

}

void CPlayerJini::Attack(D3DXVECTOR3 _vDir, float _fGiveScale)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float   fPosX = (m_tInfo.vPos.x) + (_vDir.x * m_fRadius);
	float	fPosY = (m_tInfo.vPos.y) + (_vDir.y * m_fRadius);

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYERCHILD, CAbstractFactory<CPlayerJini>::Create_SetPos(fPosX, fPosY, 0.f)); // (마우스방향으로), Pos 셋팅을 원의 지름만큼.
																														   //CObjMgr::Get_Instance()->Add_Object(OBJ_PlayerChild, CAbstractFactory<CPlayerJini>::Create_SetPos(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f)); 
	CPlayerJini* m_Child = dynamic_cast<CPlayerJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_PLAYERCHILD));
	m_Child->Set_Scale(m_fScale * _fGiveScale);
	m_Child->Set_Tag("자식");
	m_Child->Set_AttackDir(_vDir);
	//dynamic_cast<CPlayerJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_PlayerChild))->Set_AttackPos();



	m_fScale *= (1.f - _fGiveScale);

	//cout << "vPos.x = " << m_tInfo.vPos.x << "vPos.y = " << m_tInfo.vPos.y << endl;
	//cout << "new vPos.x = " << fPosX << "new vPos.y = " << fPosY << endl;
	//cout << "iScrollX = " << iScrollX << "iScrollY = " << iScrollY << endl;
	//cout << "vDir.x = " << m_tInfo.vDir.x << "vDir.y = " << m_tInfo.vDir.y << endl;

}

void CPlayerJini::AttackRound()
{
	// 8방향 각도
	D3DXVECTOR3		m_vDirTemp[8] =
	{ { 0.f, -1.f, 0.f },
	{ 0.5f, -0.5f, 0.f },
	{ 1.f, 0.f, 0.f },
	{ 0.5f, 0.5f, 0.f },
	{ 0.f, 1.f, 0.f },
	{ -0.5f, 0.5f, 0.f },
	{ -1.f, 0.f, 0.f },
	{ -0.5f, -0.5f, 0.f }
	};

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	srand(unsigned int(time(NULL)));
	int		iRandom = rand() % 4 + 5;

	for (int i = 0; i < iRandom; ++i)
	{
		float   fPosX = (m_tInfo.vPos.x) + (m_vDirTemp[i].x * m_fRadius );
		float	fPosY = (m_tInfo.vPos.y) + (m_vDirTemp[i].y * m_fRadius );

		CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYERCHILD, CAbstractFactory<CPlayerJini>::Create_SetPos(fPosX, fPosY, 0.f)); // (마우스방향으로), Pos 셋팅을 원의 지름만큼.
		CPlayerJini* m_Child = dynamic_cast<CPlayerJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_PLAYERCHILD));
		m_Child->Set_Scale(m_fScale * 0.1f);
		m_Child->Set_Tag("다자녀");
		m_Child->Set_AttackDir(m_vDirTemp[i]);
	}

	m_fScale *= (10 - iRandom) * 0.1f;
}


