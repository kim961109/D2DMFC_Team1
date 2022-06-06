#include "stdafx.h"
#include "MonsterJini.h"

#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMonsterJini::CMonsterJini()
{
}


CMonsterJini::~CMonsterJini()
{
	Release();
}

void CMonsterJini::Initialize(void)
{
	//m_vPosMiniMap = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { 1.f, 0.f, 0.f };
	m_vDirLocal = { 1.f, 0.f, 0.f };

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 1.f;
	m_fAngle = 0.f;
	m_fScale = 3.0f;
	m_fScaleSum = 0.f;
	m_fScore = 0.f;
	//m_fEllipse		= 50.f;

	m_vBodyLocal[0] = { -50.f, 0.f, 0.f }; //left
	m_vBodyLocal[1] = { 0.f, -50.f, 0.f }; //top
	m_vBodyLocal[2] = { 50.f, 0.f, 0.f }; //right
	m_vBodyLocal[3] = { 0.f, 50.f, 0.f }; //bottom
	m_fRadius = (m_vBodyLocal[2].x - m_vBodyLocal[0].x) * 0.5;

	// 색상 랜덤 설정
	srand(unsigned int(time(NULL)));
	m_iPlayerColorR = rand() * 10 % 256;
	m_iPlayerColorG = rand() * 18 % 256;
	m_iPlayerColorB = rand() * 27 % 256;

	m_strTag = "부모";
	lstrcpy(m_szName, L"성이");

	m_dwAttackMove = GetTickCount();
	m_bMouseMove = false;
	m_bBirth = false;

	m_vAttackPos = { 0.f, 0.f, 0.f };
	m_vAttackDir = { 0.f, 0.f, 0.f };

}

int CMonsterJini::Update(void)
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

	// 화면 안벗어나게
	if (0 >= m_tInfo.vPos.x || 2400 <= m_tInfo.vPos.x || 0 >= m_tInfo.vPos.y || 1800 <= m_tInfo.vPos.y)
		m_tInfo.vDir *= -1.f;

	// 분열 공격 시, 이동
	if (m_bBirth & m_strTag != "부모")
	{
		if (m_strTag == "자식")
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

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

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


	//cout << "vPos.x = " << m_tInfo.vPos.x << "\t vPos.y = " << m_tInfo.vPos.y << "\t m_fScale = " << m_fScale << "\t m_fScore = " << m_fScore << "\t m_fScaleSum = " << m_fScaleSum << endl;

	//m_vPosMiniMap.x = m_tInfo.vPos.x / 2400.f * JINIMAPCX;
	//m_vPosMiniMap.y = m_tInfo.vPos.y / 1800.f * JINIMAPCY;

	return OBJ_NOEVENT;
}

void CMonsterJini::Late_Update(void)
{
}

void CMonsterJini::Render(HDC hDC)
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

	//Ellipse(hDC,
	//	int(m_vPosMiniMap.x - 3.f + WINCX - JINIMAPCX),
	//	int(m_vPosMiniMap.y - 3.f + WINCY - JINIMAPCY),
	//	int(m_vPosMiniMap.x + 3.f + WINCX - JINIMAPCX),
	//	int(m_vPosMiniMap.y + 3.f + WINCY - JINIMAPCY));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfCharSet = 129;
	m_labelFontInfo.lfHeight = m_fScale * g_fRenderPercent * 1.5 * 12;
	m_labelFontInfo.lfWidth = m_fScale * g_fRenderPercent * 1.5 * 6;
	//m_labelFontInfo.lfWeight = FW_BOLD;

	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);
	SetBkMode(hDC, OPAQUE); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	SetTextColor(hDC, RGB(255, 255, 255));

	TextOut(hDC, m_tInfo.vPos.x - m_fRadius * 0.7 * g_fRenderPercent + iScrollX, m_tInfo.vPos.y - m_fRadius * 0.2 * g_fRenderPercent + iScrollY, m_szName, lstrlen(m_szName));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);

}

void CMonsterJini::Release(void)
{
}

void CMonsterJini::Attack(D3DXVECTOR3 _vDir, float _fGiveScale)
{
	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	float   fPosX = (m_tInfo.vPos.x) + (_vDir.x * m_fRadius);
	float	fPosY = (m_tInfo.vPos.y) + (_vDir.y * m_fRadius);

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterJini>::Create_SetPos(fPosX, fPosY, 0.f)); // (마우스방향으로), Pos 셋팅을 원의 지름만큼.
																														   //CObjMgr::Get_Instance()->Add_Object(OBJ_PlayerChild, CAbstractFactory<CPlayerJini>::Create_SetPos(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f)); 

	dynamic_cast<CMonsterJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER))->Set_Scale(m_fScale * _fGiveScale);
	dynamic_cast<CMonsterJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER))->Set_Tag("자식");
	dynamic_cast<CMonsterJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER))->Set_AttackDir(_vDir);

	m_fScale *= (1.f - _fGiveScale);

	//cout << "vPos.x = " << m_tInfo.vPos.x << "vPos.y = " << m_tInfo.vPos.y << endl;
	//cout << "new vPos.x = " << fPosX << "new vPos.y = " << fPosY << endl;
	//cout << "iScrollX = " << iScrollX << "iScrollY = " << iScrollY << endl;
	//cout << "vDir.x = " << m_tInfo.vDir.x << "vDir.y = " << m_tInfo.vDir.y << endl;

}

void CMonsterJini::AttackRound()
{
	// 8방향 각도
	D3DXVECTOR3		m_vDirTemp[8] =
	{ 
		{ 0.f, -1.f, 0.f },
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
		float   fPosX = (m_tInfo.vPos.x) + (m_vDirTemp[i].x * m_fRadius);
		float	fPosY = (m_tInfo.vPos.y) + (m_vDirTemp[i].y * m_fRadius);

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterJini>::Create_SetPos(fPosX, fPosY, 0.f)); // (마우스방향으로), Pos 셋팅을 원의 지름만큼.
		dynamic_cast<CMonsterJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER))->Set_Scale(m_fScale * 0.1f);
		dynamic_cast<CMonsterJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER))->Set_Tag("다자녀");
		dynamic_cast<CMonsterJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER))->Set_AttackDir(m_vDirTemp[i]);


	}

	m_fScale *= (10 - iRandom) * 0.1f;
}
