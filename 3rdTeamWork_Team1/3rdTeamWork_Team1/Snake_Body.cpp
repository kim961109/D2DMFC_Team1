#include "stdafx.h"
#include "Snake_Body.h"
#include "Snake_Head.h"
#include"ObjMgr.h"


CSnake_Body::CSnake_Body()
{
}


CSnake_Body::~CSnake_Body()
{
}

void CSnake_Body::Initialize(void)
{	
	m_tInfo.vPos = {0.f, 0.f, 0.f };
	m_tInfo.vDir = { 0.f, -1.f, 0.f };

	m_vPoint[0] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[1] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y - 10.f, 0.f };
	m_vPoint[2] = { m_tInfo.vPos.x + 10.f,  m_tInfo.vPos.y + 10.f, 0.f };
	m_vPoint[3] = { m_tInfo.vPos.x - 10.f,  m_tInfo.vPos.y + 10.f, 0.f };

	for (int i = 0; i < 4; ++i)
	{
		m_vOriginPoint[i] = m_vPoint[i];
	}

	m_fAngle = 0.f;
	m_fSpeed = 1.f;
}

int CSnake_Body::Update(void)
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	//front 는 head를 따라가고  나머지는 바로앞에꺼 따라가게 
	
	if (!CObjMgr::Get_Instance()->Get_List(OBJ_SNAKE).empty())

	{
		m_SnakeList = CObjMgr::Get_Instance()->Get_List(OBJ_SNAKEBODY);

		if (CObjMgr::Get_Instance()->Get_List(OBJ_SNAKEBODY).front() == this)
		{

			m_HeadPos = dynamic_cast<CSnake_Head*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_SNAKE))->Get_Pos();
			m_tHead = dynamic_cast<CSnake_Head*>(CObjMgr::Get_Instance()->Get_ListBack(OBJ_SNAKE))->Get_Info();
			m_tInfo.vDir = m_HeadPos - m_tInfo.vPos;

			// 벡터의 정규화를 수행하는 함수(1. 결과 값을 어디에 저장할 것인가 2. 단위 벡터로 만들 벡터)
			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
			//D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

			// 벡터의 크기를 구해주는 함수
			// float fLength = D3DXVec3Length(&m_tInfo.vDir);

			// 두 방향 벡터의 내적을 수행하는 함수

			/*
	float   fWidth = fabs(pDest->Get_Info().vPos.x - pSour->Get_Info().vPos.x);
	float   fHeight = fabs(pDest->Get_Info().vPos.y - pSour->Get_Info().vPos.y);

	float   fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float   fRadius=20;
*/
			float   fWidth = fabs(m_tHead.vPos.x - m_tInfo.vPos.x);
			float   fHeight = fabs(m_tHead.vPos.y - m_tInfo.vPos.y);

			float   fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
			
			if (fDiagonal > 20)
			{
				m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
			}
			else
			{

			}
			

			float fDot = D3DXVec3Dot(&m_tHead.vDir, &m_tInfo.vDir);

			float	fAngle = acosf(fDot);
			//m_tInfo.vPos.x += m_fSpeed * cosf(fAngle);
		//	m_tInfo.vPos.y -= m_fSpeed * sinf(fAngle);

			D3DXMATRIX		matScale, matRotZ, matTrans;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixRotationZ(&matRotZ, m_fAngle);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

			m_tInfo.matWorld = matScale * matRotZ* matTrans;
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
			for (int i = 0; i < 4; ++i)
			{
				m_vPoint[i] = m_vOriginPoint[i];
				//m_vPoint[i] -= { 400.f, 300.f, 0.f };

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}
		}
		else
		{
			int iNum = 0;

			vector<CObj*> vec = dynamic_cast<CSnake_Head*>(CObjMgr::Get_Instance()->Get_List(OBJ_SNAKE).front())->Get_vector();

			for (int i = 0; i < vec.size(); ++i)
			{
				if (this == vec[i])
				{
					iNum = i;
				}
			}

			CSnake_Body* frontBody = dynamic_cast<CSnake_Body*>(vec[iNum - 1]);
			m_tFrontBody = frontBody->Get_Info();
			m_tInfo.vDir = m_tFrontBody.vPos - m_tInfo.vPos;

			// 벡터의 정규화를 수행하는 함수(1. 결과 값을 어디에 저장할 것인가 2. 단위 벡터로 만들 벡터)
			D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
			//D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

			// 벡터의 크기를 구해주는 함수
			// float fLength = D3DXVec3Length(&m_tInfo.vDir);

			// 두 방향 벡터의 내적을 수행하는 함수


			float   fWidth = fabs(m_tFrontBody.vPos.x - m_tInfo.vPos.x);
			float   fHeight = fabs(m_tFrontBody.vPos.y - m_tInfo.vPos.y);
			
			float   fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

			if (fDiagonal > 20)
			{
				m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
			}
			else
			{

			}

			float fDot = D3DXVec3Dot(&m_tFrontBody.vDir, &m_tInfo.vDir);

			float	fAngle = acosf(fDot);
			//m_tInfo.vPos.x += m_fSpeed * cosf(fAngle);
			//	m_tInfo.vPos.y -= m_fSpeed * sinf(fAngle);

			D3DXMATRIX		matScale, matRotZ, matTrans;

			D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
			D3DXMatrixRotationZ(&matRotZ, m_fAngle);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

			m_tInfo.matWorld = matScale * matRotZ* matTrans;
			D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vDir, &m_tInfo.matWorld);
			for (int i = 0; i < 4; ++i)
			{
				m_vPoint[i] = m_vOriginPoint[i];
				//m_vPoint[i] -= { 400.f, 300.f, 0.f };

				D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tInfo.matWorld);
			}


		}
		return OBJ_NOEVENT;
	}
}

void CSnake_Body::Late_Update(void)
{

}

void CSnake_Body::Render(HDC hDC)
{
	/*MoveToEx(hDC, (int)m_vPoint[0].x, (int)m_vPoint[0].y, nullptr);
	for (int i = 0; i < 4; ++i)
	{
		LineTo(hDC, (int)m_vPoint[i].x, (int)m_vPoint[i].y);
	}
	LineTo(hDC, m_vPoint[0].x, m_vPoint[0].y);*/

	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	HPEN myPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(rand() % 256, rand() % 256, rand() % 256));
	HPEN oldPen = (HPEN)SelectObject(hDC, myPen);

	Ellipse(hDC,
		int(m_vPoint[0].x),
		int(m_vPoint[1].y),
		int(m_vPoint[2].x),
		int(m_vPoint[3].y));

	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);
}

void CSnake_Body::Release(void)
{
}

void CSnake_Body::Key_Input(void)
{
	if (GetAsyncKeyState('W'))
	{
	}

	if (GetAsyncKeyState('S'))
	{
	}

	if (GetAsyncKeyState(VK_UP))
	{
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
	}

}

