#include "stdafx.h"
#include "CollisionMgr.h"
#include"SceneMgr.h"
#include"Apple.h"
#include"Snake_Body.h"
#include "PlayerJini.h"
#include "MonsterJini.h"
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
				float	fTemp;
				float	fTempMonster;
				int		Num_Temp;
				int		Num_TempMonster;

				//if (Dest->Get_Dead() == true || Sour->Get_Dead() == true)
				//	continue;

				switch (_index)
				{
				case 1: // JINI : Player - Player
					if ((_index == 1) & dynamic_cast<CPlayerJini*>(Sour)->Get_bBirth())
						continue;
					dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CPlayerJini*>(Sour)->Get_Scale());
					Sour->Set_Dead(true);
					break;

				case 2: // JINI : Player - Jelly
					dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CJelly*>(Sour)->Get_PlusScale());
					g_fScore += dynamic_cast<CJelly*>(Sour)->Get_Scale();
					dynamic_cast<CJelly*>(Sour)->Set_ScaleZero();
					Sour->Set_Dead(true);
					break;

				case 3: // JINI : Player - Monster
					fRadiusDest = dynamic_cast<CPlayerJini*>(Dest)->Get_Radius();
					fRadiusSour = dynamic_cast<CMonsterJini*>(Sour)->Get_Radius();
					fTemp = dynamic_cast<CPlayerJini*>(Dest)->Get_Scale();
					fTempMonster = dynamic_cast<CMonsterJini*>(Sour)->Get_Scale();
					Num_Temp = dynamic_cast<CMonsterJini*>(Sour)->Get_NameNum();

					if (fRadiusDest > fRadiusSour)
					{
						dynamic_cast<CPlayerJini*>(Dest)->Set_ScalePlus(dynamic_cast<CMonsterJini*>(Sour)->Get_Scale());
						g_fScore += fTempMonster * 100.f;
						switch (Num_Temp)
						{
						case 1:
							g_fScoreKS -= fTempMonster * 100.f;
							break;
						case 2:
							g_fScoreKJE -= fTempMonster * 100.f;
							break;
						case 3:
							g_fScoreKMS -= fTempMonster * 100.f;
							break;
						}
						Sour->Set_Dead(true);
					}
					else
					{
						dynamic_cast<CMonsterJini*>(Sour)->Set_ScalePlus(dynamic_cast<CPlayerJini*>(Dest)->Get_Scale());
						switch (Num_Temp)
						{
						case 1:
							g_fScoreKS += fTemp * 100.f;
							g_fScore -= fTemp * 100.f;
							break;
						case 2:
							g_fScoreKJE += fTemp * 100.f;
							g_fScore -= fTemp * 100.f;
							break;
						case 3:
							g_fScoreKMS += fTemp * 100.f;
							g_fScore -= fTemp * 100.f;
							break;
						}
						g_fScore += dynamic_cast<CPlayerJini*>(Dest)->Get_Scale();
						Dest->Set_Dead(true);
					}
				   break;

					//jeongeun
				case 4: //SnakeHead - SnakeBody
					break;

				case 5://SnakeBody -SnakeBody
					break;

				case 6: // JINI : Monster - Jelly
					dynamic_cast<CMonsterJini*>(Dest)->Set_ScalePlus(dynamic_cast<CJelly*>(Sour)->Get_PlusScale());
					Num_Temp = dynamic_cast<CMonsterJini*>(Dest)->Get_NameNum();
					switch (Num_Temp)
					{
					case 1:
						g_fScoreKS += dynamic_cast<CJelly*>(Sour)->Get_Scale();
						break;
					case 2:
						g_fScoreKJE += dynamic_cast<CJelly*>(Sour)->Get_Scale();
						break;
					case 3:
						g_fScoreKMS += dynamic_cast<CJelly*>(Sour)->Get_Scale();
						break;
					}
					dynamic_cast<CJelly*>(Sour)->Set_ScaleZero();
					Sour->Set_Dead(true);
					break;

				case 7: // JINI : Monster - Monster
					if (dynamic_cast<CMonsterJini*>(Sour)->Get_bBirth())
						continue;
					if (dynamic_cast<CMonsterJini*>(Dest)->Get_NameNum() != dynamic_cast<CMonsterJini*>(Sour)->Get_NameNum())
						continue;
					dynamic_cast<CMonsterJini*>(Dest)->Set_ScalePlus(dynamic_cast<CMonsterJini*>(Sour)->Get_Scale());
					Sour->Set_Dead(true);
					break;

					//fRadiusDest = dynamic_cast<CMonsterJini*>(Dest)->Get_Radius();
					//fRadiusSour = dynamic_cast<CMonsterJini*>(Sour)->Get_Radius();
					//fTemp = dynamic_cast<CMonsterJini*>(Dest)->Get_Scale();
					//fTempMonster = dynamic_cast<CMonsterJini*>(Sour)->Get_Scale();
					//Num_Temp = dynamic_cast<CMonsterJini*>(Dest)->Get_NameNum();
					//Num_TempMonster = dynamic_cast<CMonsterJini*>(Sour)->Get_NameNum();

					//if (fRadiusDest > fRadiusSour)
					//{
					//	dynamic_cast<CMonsterJini*>(Dest)->Set_ScalePlus(dynamic_cast<CMonsterJini*>(Sour)->Get_Scale());
					//	switch (Num_Temp)
					//	{
					//	case 1:
					//		g_fScoreKS += fTempMonster * 100.f;
					//		break;
					//	case 2:
					//		g_fScoreKJE += fTempMonster * 100.f;
					//		break;
					//	case 3:
					//		g_fScoreKMS += fTempMonster * 100.f;
					//		break;
					//	}
					//	switch (Num_TempMonster)
					//	{
					//	case 1:
					//		g_fScoreKS -= fTempMonster * 100.f;
					//		break;
					//	case 2:
					//		g_fScoreKJE -= fTempMonster * 100.f;
					//		break;
					//	case 3:
					//		g_fScoreKMS -= fTempMonster * 100.f;
					//		break;
					//	}
					//	Sour->Set_Dead(true);
					//}
					//else
					//{
					//	dynamic_cast<CMonsterJini*>(Sour)->Set_ScalePlus(dynamic_cast<CMonsterJini*>(Dest)->Get_Scale());
					//	switch (Num_Temp)
					//	{
					//	case 1:
					//		g_fScoreKS -= fTemp * 100.f;
					//		break;
					//	case 2:
					//		g_fScoreKJE -= fTemp * 100.f;
					//		break;
					//	case 3:
					//		g_fScoreKMS -= fTemp * 100.f;
					//		break;
					//	}
					//	switch (Num_TempMonster)
					//	{
					//	case 1:
					//		g_fScoreKS += fTemp * 100.f;
					//		break;
					//	case 2:
					//		g_fScoreKJE += fTemp * 100.f;
					//		break;
					//	case 3:
					//		g_fScoreKMS += fTemp * 100.f;
					//		break;
					//	}
					//	Dest->Set_Dead(true);
					//}
					//break;
				}

			}
		}
	}
}

// JINI
bool CCollisionMgr::Check_Sphere(CObj* pDest, CObj* pSour, int _index)
{
	float   fWidth = fabs(pDest->Get_Info().vPos.x - pSour->Get_Info().vPos.x);
	float   fHeight = fabs(pDest->Get_Info().vPos.y - pSour->Get_Info().vPos.y);

	float   fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float   fRadius;

	switch (_index)
	{
	case 1: // JINI : Player - Player
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CPlayerJini*>(pSour)->Get_Radius();
		fRadius = fRadius * 0.7f * g_fRenderPercent;
		break;

	case 2: // JINI : Player - Jelly
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CJelly*>(pSour)->Get_Radius();
		fRadius *= g_fRenderPercent;
		break;

	case 3: // JINI : Player - Monster
		fRadius = dynamic_cast<CPlayerJini*>(pDest)->Get_Radius() + dynamic_cast<CMonsterJini*>(pSour)->Get_Radius();
		fRadius *= g_fRenderPercent;
		break;

	case 4: //Snake - Apple
		//float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
		break;

	case 5: //Snake - Tile
		break;

	case 6: // JINI : Monster - Jelly
		fRadius = dynamic_cast<CMonsterJini*>(pDest)->Get_Radius() + dynamic_cast<CJelly*>(pSour)->Get_Radius();
		fRadius *= g_fRenderPercent;
		break;

	case 7: // JINI : Monster - Monster
		fRadius = dynamic_cast<CMonsterJini*>(pDest)->Get_Radius() + dynamic_cast<CMonsterJini*>(pSour)->Get_Radius();
		fRadius = fRadius * 0.7f * g_fRenderPercent;
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
				static_cast<CZombie*>(*Sour)->Set_Damage();
			}
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

                                         // 당구공                // 충돌체.
void CCollisionMgr::Collision_Choose(list<CObj*> _Dest, vector<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest = _Dest.begin(); Dest != _Dest.end(); ++Dest)
	{
		if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((_Sour[0])->Get_Rect())))//나가기
		{
			PostQuitMessage(0);
		}
		else if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((_Sour[1])->Get_Rect())))//지니
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_JINI);
		}
		else if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((_Sour[2])->Get_Rect())))//민성
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_KMS);
		}
		else if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((_Sour[3])->Get_Rect())))//랜덤
		{
			//srand(unsigned int(time(NULL)));
			int		iRandomA = rand() % 2;
			int     iRandomB = rand() % 2 + 1;
			int     iGame = 3 * iRandomA + iRandomB;
			switch (iGame)
			{
			case 1:
				CSceneMgr::Get_Instance()->Scene_Change(SC_JINI);
				break;
			case 2:
				CSceneMgr::Get_Instance()->Scene_Change(SC_KMS);
				break;
			case 4:
				CSceneMgr::Get_Instance()->Scene_Change(SC_KJE);
				break;
			case 5:
				CSceneMgr::Get_Instance()->Scene_Change(SC_KS);
				break;
			}
			//CSceneMgr::Get_Instance()->Scene_Change(SC_KMS);
		}
		else if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((_Sour[4])->Get_Rect())))//정은
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_KJE);
		}
		else if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((_Sour[5])->Get_Rect())))//성
		{
			CSceneMgr::Get_Instance()->Scene_Change(SC_KS);
		}
	}
}

                                       // 플레이어            //좀비.
void CCollisionMgr::Collision_Zombie(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};
	for (auto& Dest = _Dest.begin(); Dest != _Dest.end(); ++Dest)
	{
		for (auto& Sour = _Sour.begin(); Sour != _Sour.end(); ++Sour)
		{
			if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((*Sour)->Get_Rect())))
			{
				static_cast<CPlayer_KS*>(*Dest)->Set_Damage();
			}
		}
	}
}

                                      // 고정                     // 플레이어
void CCollisionMgr::Collision_RectKS(list<CObj*> _Dest, list<CObj*> _Sour)// 고정된 물체가 움직이는 물체를 밀어내는 용도.
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
						static_cast<CPlayer_KS*>(Sour)->Set_KSPosY(-fY);

					else // 하 충돌
						static_cast<CPlayer_KS*>(Sour)->Set_KSPosY(fY);
				}
				// 좌우 충돌
				else
				{
					// 좌 충돌
					if (Dest->Get_ObjInfo().fX > Sour->Get_ObjInfo().fX)
						static_cast<CPlayer_KS*>(Sour)->Set_KSPosX(-fX);

					// 우 충돌
					else
						static_cast<CPlayer_KS*>(Sour)->Set_KSPosX(fX);
				}

			}
		}
	}
}

bool CCollisionMgr::Check_Snake(CObj* pDest, CObj* pSour)
{

	float   fWidth = fabs(pDest->Get_Info().vPos.x - pSour->Get_Info().vPos.x);
	float   fHeight = fabs(pDest->Get_Info().vPos.y - pSour->Get_Info().vPos.y);

	float   fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float   fRadius=1;

	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Snake(list<CObj*> _Dest, list<CObj*> _Sour)
{

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Snake(Dest, Sour))
			{
				{
					Sour->Set_Dead();
					Dest->Set_Dead();
				}
			}
		}
	}
}
