#include "stdafx.h"
#include "CollisionMgr.h"


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

                                                  //ÃÑ¾Ë            // ¸ó½ºÅÍ
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
