#include "stdafx.h"
#include "CollisionMgr.h"
#include"SceneMgr.h"
#include"Apple.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				//Sour->Set_Damage(Dest->Get_Damage());
			}
		}
	}
}

void CCollisionMgr::Collision_Snake_Apple(list<CObj*> _Snake, list<CObj*> _Apple)
{
	RECT		rc{};

	for (auto& Snake : _Snake)
	{
		for (auto& Apple : _Apple)
		{
			if (IntersectRect(&rc, &(Snake->Get_Rect()), &(Apple->Get_Rect())))
			{
				//Apple->Set_Dead();
				srand(unsigned int(time(NULL)));
				Apple->Set_ObjPos(rand() % (WINCX - 140)+70, rand() % (WINCY - 140)+70);
				dynamic_cast<CApple*>(Apple)->Set_ApplePlus();
			}
		}
	}
}

/*bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour)
{

	// abs : 절대값을 구해주는 함수
	float	fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float	fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	// sqrt : 루트를 씌워주는 함수
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}*/