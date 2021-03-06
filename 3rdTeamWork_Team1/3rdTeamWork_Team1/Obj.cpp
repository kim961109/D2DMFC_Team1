#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_bDead(false)
{
	ZeroMemory(&m_tObjInfo, sizeof(OBJINFO));
	ZeroMemory(&m_tRect, sizeof(RECT));

	D3DXMatrixIdentity(&m_tInfo.matWorld);
}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = LONG(m_tObjInfo.fX - 0.5f * m_tObjInfo.fCX);
	m_tRect.top = LONG(m_tObjInfo.fY - 0.5f * m_tObjInfo.fCY);
	m_tRect.right = LONG(m_tObjInfo.fX + 0.5f * m_tObjInfo.fCX);
	m_tRect.bottom = LONG(m_tObjInfo.fY + 0.5f * m_tObjInfo.fCY);
}

void CObj::Move_Frame(void)
{
	if (GetTickCount() - m_tFrame.dwTime >= m_tFrame.dwSpeed )
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;


	}
	/*if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		m_tFrame.iFrameStart++;

		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}*/
}
