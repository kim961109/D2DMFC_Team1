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
	static void		Collision_BulletKS(list<CObj*>& _Dest, list<CObj*>& _Sour);

};

