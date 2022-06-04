#pragma once
#include "Obj.h"
#include "Include.h"
#include "Monster_KS.h"


class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Snake_Apple(list<CObj*> _Snake, list<CObj*> _Apple);
	static void		Collision_Snake_Tile(list<CObj*> _Snake, vector<CObj*> _Tile);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour, int _index);
	static bool		Check_Sphere(CObj* pDest, CObj* pSour, int _index);
	static void		Collision_BulletKS(list<CObj*>& _Dest, list<CObj*>& _Sour);
	static bool     Check_Rect(CObj * pDest, CObj * pSour, float * pX, float * pY);
	static void     Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour);

};

