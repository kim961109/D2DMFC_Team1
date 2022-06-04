#include "stdafx.h"
#include "CollisionMgr.h"
#include"SceneMgr.h"
#include"Apple.h"
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
					if ((_index == 1) & dynamic_cast<CPlayerJini*>(Sour)->Get_bBirth())
						continue;
					dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CPlayerJini*>(Sour)->Get_Scale());
					Sour->Set_Dead(true);

					break;
				case 2: //Player - Jelly
					//fRadiusDest = dynamic_cast<CPlayerJini*>(Dest)->Get_Radius();
					//fRadiusSour = dynamic_cast<CJelly*>(Sour)->Get_Radius();

						//if (fRadiusDest > fRadiusSour)
					dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CJelly*>(Sour)->Get_PlusScale());
					dynamic_cast<CPlayerJini*>(Dest)->Set_Score(dynamic_cast<CJelly*>(Sour)->Get_Scale());
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

void CCollisionMgr::Collision_Sphere2(list<CObj*> _Dest, list<CObj*> _Sour)
{

	//for (auto& Dest : _Dest)
	//{
	//	for (auto& Sour : _Sour)
	//	{
	//		if (Check_Sphere(Dest, Sour, _index))
	//		{
	//			float   fRadiusDest;
	//			float   fRadiusSour;

	//			switch (_index)
	//			{
	//			case 1: //Player - Player
	//				if ((_index == 1) & dynamic_cast<CPlayerJini*>(Sour)->Get_bBirth())
	//					continue;
	//				dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CPlayerJini*>(Sour)->Get_Scale());
	//				Sour->Set_Dead(true);

	//				break;
	//			case 2: //Player - Jelly
	//					//fRadiusDest = dynamic_cast<CPlayerJini*>(Dest)->Get_Radius();
	//					//fRadiusSour = dynamic_cast<CJelly*>(Sour)->Get_Radius();

	//					//if (fRadiusDest > fRadiusSour)
	//				dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CJelly*>(Sour)->Get_PlusScale());
	//				Sour->Set_Dead(true);

	//				break;
	//				//case 3: //Player - Monster
	//				//   fRadiusDest = dynamic_cast<CPlayerJini*>(Dest)->Get_Radius();
	//				//  fRadiusSour = dynamic_cast<CMonster*>(Sour)->Get_Radius();
	//				//   break;
	//			}
	//		}
	//	}
	//}
}
	
bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour, int _index)
{
	// abs : Àý´ë°ªÀ» ±¸ÇØÁÖ´Â ÇÔ¼ö
	float   fWidth = fabs(pDest->Get_Info().vPos.x - pSour->Get_Info().vPos.x);
	float   fHeight = fabs(pDest->Get_Info().vPos.y - pSour->Get_Info().vPos.y);

	// sqrt : ·çÆ®¸¦ ¾º¿öÁÖ´Â ÇÔ¼ö
	float   fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float   fRadius;

	switch (_index)
	{
	case 1:
		//if (dynamic_cast<CPlayerJini*>(pDest)->Get_Tag() == dynamic_cast<CPlayerJini*>(pSour)->Get_Tag())
		//	return 0;
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CPlayerJini*>(pSour)->Get_Radius();
		fRadius = fRadius * 0.7f * g_fRenderPercent;
		break;
	case 2:
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CJelly*>(pSour)->Get_Radius();
		fRadius *= g_fRenderPercent;
		break;
		//case 3:
		//   fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CMonster*>(pSour)->Get_Radius();
		//   break;
	}


	return fRadius > fDiagonal;
}
                                                  //총알            // 몬스터
void CCollisionMgr::Collision_BulletKS(list<CObj*>& _Dest, list<CObj*>& _Sour)
{
	RECT		rc{};

	for (auto& Dest = _Dest.begin(); Dest != _Dest.end(); ++Dest)
	{
		for (auto& Sour = _Sour.begin(); Sour != _Sour.end(); ++Sour)
		{
			if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((*Sour)->Get_Rect())))
			{
				(*Dest)->Set_Dead();
				static_cast<CMonster_KS*>(*Sour)->Set_Damage();
				/*Dest = _Dest.erase(Dest);
				if (Dest == _Dest.end())
				{
					return;
				}
				else
				{
					++Dest;
				}
				static_cast<CMonster_KS*>(*Sour)->Set_Damage();

				if (0 == static_cast<CMonster_KS*>(*Sour)->Get_Hp())
				{
					Sour = _Sour.erase(Sour);
					if (Sour == _Sour.end())
					{
						return;
					}
				}*/
			}
		/*	else
			{
				++Dest;
			}*/
		}
	}
}
