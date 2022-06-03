#include "stdafx.h"
#include "CollisionMgr.h"
#include "PlayerJini.h"
#include "Jelly.h"

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

// 여기 : Jini 원충돌용
void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour, int _index)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour, _index))
			{
				float   fRadiusDest;
				float   fRadiusSour;

				switch (_index)
				{
				case 1: //Player - Player
					dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CPlayerJini*>(Sour)->Get_Scale());
					Sour->Set_Dead(true);

					break;
				case 2: //Player - Jelly
					//fRadiusDest = dynamic_cast<CPlayerJini*>(Dest)->Get_Radius();
					//fRadiusSour = dynamic_cast<CJelly*>(Sour)->Get_Radius();

						//if (fRadiusDest > fRadiusSour)
					dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CJelly*>(Sour)->Get_PlusScale());
					Sour->Set_Dead(true);

					break;
					//case 3: //Player - Monster
					//   fRadiusDest = dynamic_cast<CPlayerJini*>(Dest)->Get_Radius();
					//  fRadiusSour = dynamic_cast<CMonster*>(Sour)->Get_Radius();
					//   break;
				}


			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour, int _index)
{
	// abs : 절대값을 구해주는 함수
	float   fWidth = fabs(pDest->Get_Info().vPos.x - pSour->Get_Info().vPos.x);
	float   fHeight = fabs(pDest->Get_Info().vPos.y - pSour->Get_Info().vPos.y);

	// sqrt : 루트를 씌워주는 함수
	float   fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float   fRadius;

	switch (_index)
	{
	case 1:
		//if (dynamic_cast<CPlayerJini*>(pDest)->Get_Tag() == dynamic_cast<CPlayerJini*>(pSour)->Get_Tag())
		//	return 0;
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CPlayerJini*>(pSour)->Get_Radius();
		fRadius *= 0.7f;
		break;
	case 2:
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CJelly*>(pSour)->Get_Radius();
		break;
		//case 3:
		//   fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CMonster*>(pSour)->Get_Radius();
		//   break;
	}


	return fRadius > fDiagonal;
}
