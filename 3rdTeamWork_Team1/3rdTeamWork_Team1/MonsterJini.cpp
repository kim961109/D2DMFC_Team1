#include "stdafx.h"
#include "MonsterJini.h"

#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMonsterJini::CMonsterJini()
{
	m_pPlayer = nullptr;
}


CMonsterJini::~CMonsterJini()
{
	Release();
}

void CMonsterJini::Initialize(void)
{
	//m_vPosMiniMap = { 0.f, 0.f, 0.f };
	m_tInfo.vDir = { -1.f, 0.f, 0.f };
	m_vDirLocal = { 1.f, 0.f, 0.f };
	m_vPlayerLocal = { 0.f, 0.f, 0.f };

	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_fSpeed = 1.f;
	m_fAngle = 0.f;
	m_fScale = 2.0f;

	m_vBodyLocal[0] = { -50.f, 0.f, 0.f }; //left
	m_vBodyLocal[1] = { 0.f, -50.f, 0.f }; //top
	m_vBodyLocal[2] = { 50.f, 0.f, 0.f }; //right
	m_vBodyLocal[3] = { 0.f, 50.f, 0.f }; //bottom
	m_fRadius = (m_vBodyLocal[2].x - m_vBodyLocal[0].x) * 0.5;

	// ���� ���� ����
	srand(unsigned int(time(NULL)));
	m_iPlayerColorR = rand() * 10 % 256;
	m_iPlayerColorG = rand() * 18 % 256;
	m_iPlayerColorB = rand() * 27 % 256;

	m_strTag = "�θ�";

	m_dwAttackMove = GetTickCount();
	m_bBirth = false;

	m_vAttackPos = { 0.f, 0.f, 0.f };
	m_vAttackDir = { 0.f, 0.f, 0.f };

	m_fPlayerDistance = 0.f;
	m_vPlayerTemp = { 0.f, 0.f, 0.f };
	m_dwAttackTime = GetTickCount();
}

int CMonsterJini::Update(void)
{
	if (m_bDead)
	{
		switch (m_iNameNum)
		{
		case 1:
			g_fScoreKS = 0;
			break;
		case 2:
			g_fScoreKJE = 0;
			break;
		case 3:
			g_fScoreKMS = 0;
			break;
		}
		return OBJ_DEAD;
	}

	if (m_strTag != "�θ�")
		m_bBirth = true;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	// ũ�⿡ ���� �ӵ� ����
	m_fSpeed = 1.5f / m_fScale;
	if (m_fSpeed > 3.f)
		m_fSpeed = 3.f;
	else if (m_fSpeed < 0.5f)
		m_fSpeed = 0.5f;

	// ȭ�� �ȹ����
	if (0 >= m_tInfo.vPos.x || 2400 <= m_tInfo.vPos.x || 0 >= m_tInfo.vPos.y || 1800 <= m_tInfo.vPos.y)
		m_tInfo.vDir *= -1.f;

	KeyInput();

	// �п� ���� ��, �̵�
	if (m_bBirth & m_strTag != "�θ�")
	{
		if (m_strTag == "�ڽ�")
			m_tInfo.vPos += m_vAttackDir * 2.f * g_fRenderPercent;
		else
			m_tInfo.vPos += m_vAttackDir * 2.f * g_fRenderPercent;

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

	// ����Ʈ �̵�
	if(!m_bBirth)
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	// ������� �����
	D3DXMATRIX		matScale, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// ������� ����
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&m_vBody[i], &m_vBodyLocal[i], &m_tInfo.matWorld);
	}

	// ������ ����صα�
	m_fRadius = (m_vBody[2].x - m_vBody[0].x) * 0.5;

	//cout << "vPos.x = " << m_tInfo.vPos.x << "\t vPos.y = " << m_tInfo.vPos.y << "\t m_fScale = " << m_fScale << "\t m_fScore = " << m_fScore << "\t m_fScaleSum = " << m_fScaleSum << endl;
	//cout << "vPos.x = " << m_tInfo.vPos.x << "\t vPos.y = " << m_tInfo.vPos.y << "\t m_fPlayerDistance = " << m_fPlayerDistance  << endl;

	// �÷��̾� �Ÿ�, ����
	if (m_pPlayer)
	{
		m_vPlayerTemp.x = m_pPlayer->Get_Info().vPos.x;
		m_vPlayerTemp.y = m_pPlayer->Get_Info().vPos.y;

		// �÷��̾� �Ÿ� ���
		float _DistanceX = m_vPlayerTemp.x - m_tInfo.vPos.x;
		float _DistanceY = m_vPlayerTemp.y - m_tInfo.vPos.y;
		m_fPlayerDistance = sqrtf(_DistanceX * _DistanceX + _DistanceY * _DistanceY);

		// �÷��̾� ���⿬��
		m_vPlayerLocal = m_vPlayerTemp - m_tInfo.vPos;
		D3DXVec3Normalize(&m_vPlayerDir, &m_vPlayerLocal);
	}

	if (m_strTag == "�θ�")
		Phase();

	return OBJ_NOEVENT;
}

void CMonsterJini::Late_Update(void)
{
	int iScoreTemp;

	// ���� ��¿�
	switch (m_iNameNum)
	{
	case 1:
		iScoreTemp = (int)g_fScoreKS;
		swprintf_s(m_szScore, L"���� : %d", iScoreTemp);
		break;
	case 2:
		iScoreTemp = (int)g_fScoreKJE;
		swprintf_s(m_szScore, L"������ : %d", iScoreTemp);
		break;
	case 3:
		iScoreTemp = (int)g_fScoreKMS;
		swprintf_s(m_szScore, L"�μ��� : %d", iScoreTemp);
		break;
	}
}

void CMonsterJini::Render(HDC hDC)
{

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int		iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Ellipse(hDC,
		int(m_tInfo.vPos.x - ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollX),
		int(m_tInfo.vPos.y - ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollY),
		int(m_tInfo.vPos.x + ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollX),
		int(m_tInfo.vPos.y + ((m_fRadius + 100 / m_fRadius)) * g_fRenderPercent + iScrollY));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);

	LOGFONT m_labelFontInfo{};
	m_labelFontInfo.lfCharSet = 129;
	m_labelFontInfo.lfHeight = m_fScale * g_fRenderPercent * 1.5 * 12;
	m_labelFontInfo.lfWidth = m_fScale * g_fRenderPercent * 1.5 * 6;

	HFONT textFont, oldFont;
	textFont = CreateFontIndirect(&m_labelFontInfo);
	oldFont = (HFONT)SelectObject(hDC, textFont);
	SetBkMode(hDC, OPAQUE); // TRANSPARENT, OPAQUE
	SetBkColor(hDC, RGB(m_iPlayerColorR, m_iPlayerColorG, m_iPlayerColorB));
	SetTextColor(hDC, RGB(255, 255, 255));

	TextOut(hDC, m_tInfo.vPos.x - m_fRadius * 0.7 * g_fRenderPercent + iScrollX, m_tInfo.vPos.y - m_fRadius * 0.2 * g_fRenderPercent + iScrollY, m_szName, lstrlen(m_szName));

	SelectObject(hDC, oldFont);
	DeleteObject(textFont);

	if (m_strTag == "�θ�")
	{
		// ���� UI
		LOGFONT m_labelFontInfo2{};
		m_labelFontInfo2.lfCharSet = 129;
		m_labelFontInfo2.lfHeight = 16;
		m_labelFontInfo2.lfWidth = 8;
		m_labelFontInfo.lfWeight = FW_BOLD;

		HFONT textFont2, oldFont2;
		textFont2 = CreateFontIndirect(&m_labelFontInfo2);
		oldFont2 = (HFONT)SelectObject(hDC, textFont2);
		SetBkMode(hDC, TRANSPARENT); // TRANSPARENT, OPAQUE
		SetBkColor(hDC, RGB(0, 10, 17));
		SetTextColor(hDC, RGB(255, 255, 255));

		TextOut(hDC, 650.f, 10.f + 20.f * (m_iRank), m_szScore, lstrlen(m_szScore));

		SelectObject(hDC, oldFont2);
		DeleteObject(textFont2);
	}

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

	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTERCHILD, CAbstractFactory<CMonsterJini>::Create_MonsterJini(fPosX, fPosY, 0.f, m_iNameNum, m_fScale * _fGiveScale)); // (���콺��������), Pos ������ ���� ������ŭ.
																														  
	CMonsterJini* m_pChild = dynamic_cast<CMonsterJini*>((CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTERCHILD)));
	m_pChild->Set_Tag("�ڽ�");
	m_pChild->Set_AttackDir(_vDir);
	m_pChild->Set_Dir(m_tInfo.vDir);


	m_fScale *= (1.f - _fGiveScale);

}

void CMonsterJini::AttackRound()
{
	// 8���� ����
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

		CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CMonsterJini>::Create_MonsterJini(fPosX, fPosY, 0.f, m_iNameNum, m_fScale * 0.1f)); // (���콺��������), Pos ������ ���� ������ŭ.
		CMonsterJini* pMonster = dynamic_cast<CMonsterJini*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_MONSTER));
		pMonster->Set_Tag("���ڳ�");
		pMonster->Set_AttackDir(m_vDirTemp[i]);
	}

	m_fScale *= (10 - iRandom) * 0.1f;
}
void CMonsterJini::KeyInput()
{
	if (CKeyMgr::Get_Instance()->Key_Down('Z'))
	{
		Attack(m_tInfo.vDir, 0.35f);
	}
}

void CMonsterJini::Phase()
{
	if (m_fPlayerDistance < 800.f)
	{
		if (GetTickCount() - m_dwAttackTime > (m_iNameNum) * 6000.f)
		{
			Attack(m_vPlayerDir, 0.35f);
			m_dwAttackTime = GetTickCount();
		}
	}
}

void CMonsterJini::Late_Initialize()
{
	switch (m_iNameNum)
	{
	case KS:
		lstrcpy(m_szName, L"����");
		g_fScoreKS = m_fScale * 800.f;
		break;
	case KJE:
		lstrcpy(m_szName, L"������");
		g_fScoreKJE = m_fScale * 800.f;
		break;
	case KMS:
		lstrcpy(m_szName, L"�μ���");
		g_fScoreKMS = m_fScale * 800.f;
		break;
	}

	srand(unsigned int(time(NULL)));
	m_iPlayerColorR = rand() * m_iNameNum * 10 % 256;
	m_iPlayerColorG = rand() * m_iNameNum * 18 % 256;
	m_iPlayerColorB = rand() * m_iNameNum * 27 % 256;
}
