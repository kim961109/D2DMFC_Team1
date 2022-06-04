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
//SCENE_KJE
void CCollisionMgr::Collision_Snake_Apple(list<CObj*> _Snake, list<CObj*> _Apple)
{
	RECT		rc{};

	for (auto& Snake : _Snake)
	{
		for (auto& Apple : _Apple)
		{
			if (IntersectRect(&rc, &(Snake->Get_Rect()), &(Apple->Get_Rect())))
			{
				srand(unsigned int(time(NULL)));
				Apple->Set_ObjPos(rand() % (WINCX - 140)+70, rand() % (WINCY - 140)+70);
				dynamic_cast<CApple*>(Apple)->Set_ApplePlus();
				dynamic_cast<CSnake_Head*>(Snake)->GrowUp();
				

      }
		}
	}
}
void CCollisionMgr::Collision_Snake_Tile(list<CObj*> _Snake, vector<CObj*> _Tile)
{
	RECT		rc{};

	for (auto& Snake : _Snake)
	{
		for (auto& Tile : _Tile)
		{
			if (IntersectRect(&rc, &(Snake->Get_Rect()), &(Tile->Get_Rect())))
			{
				Snake->Set_Dead();
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

					//jeongeun
				case 4: //Snake - Apple
					srand(unsigned int(time(NULL)));
					Sour->Set_ObjPos(rand() % (WINCX - 140) + 70, rand() % (WINCY - 140) + 70);
					dynamic_cast<CApple*>(Sour)->Set_ApplePlus();
					break;

				case 5://Snake - Tile
					break;
				}

			}
		}
	}
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
		fRadius *= 0.7f;
		break;
	case 2:
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CJelly*>(pSour)->Get_Radius();
		break;
		//case 3:
		//   fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CMonster*>(pSour)->Get_Radius();
		//   break;

	case 4: //Snake - Apple
		//float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
		
		break;
	case 5: //Snake - Tile
		break;
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

bool CCollisionMgr::Check_Rect(CObj* pDest, CObj* pSour, float *pX, float* pY)
{
	float		fWidth = abs(pDest->Get_ObjInfo().fX - pSour->Get_ObjInfo().fX);
	float		fHeight = abs(pDest->Get_ObjInfo().fY - pSour->Get_ObjInfo().fY);

	float		fCX = (pDest->Get_ObjInfo().fCX + pSour->Get_ObjInfo().fCX) * 0.5f;
	float		fCY = (pDest->Get_ObjInfo().fCY + pSour->Get_ObjInfo().fCY) * 0.5f;

	if ((fCX > fWidth) && (fCY > fHeight))
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight;

		return true;
	}

	return false;
}

                                 // 고정되어 있는 물체      // 움직이는 물체		
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)// 고정된 물체가 움직이는 물체를 밀어내는 용도.
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			float	fX = 0.f, fY = 0.f;

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				// 상하 충돌
				if (fX > fY)
				{
					// 상 충돌
					if (Dest->Get_ObjInfo().fY > Sour->Get_ObjInfo().fY)
						static_cast<CBall*>(Sour)->Change_MoveY();

					else // 하 충돌
						static_cast<CBall*>(Sour)->Change_MoveY();
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_ObjInfo().fX > Sour->Get_ObjInfo().fX)
						static_cast<CBall*>(Sour)->Change_MoveX();

					// 우 충돌
					else
						static_cast<CBall*>(Sour)->Change_MoveX();
				}

			}
		}
	}
}