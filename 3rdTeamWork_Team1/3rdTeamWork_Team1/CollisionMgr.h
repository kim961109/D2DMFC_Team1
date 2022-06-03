#pragma once
#include "Obj.h"
#include "Include.h"


class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void		Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void		Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour, int _index);
	static bool		Check_Sphere(CObj* pDest, CObj* pSour, int _index);

};

