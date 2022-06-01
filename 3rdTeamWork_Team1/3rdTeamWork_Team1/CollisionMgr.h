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

};

