#pragma once
#include "Scene.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "UIFactory.h"
#include "Player_KS.h"
#include "Zombie.h"
#include "Wall.h"

class CScene_KS :
	public CScene
{
public:
	CScene_KS();
	virtual ~CScene_KS();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Scene_ChangeKey(void);
	void Counting_Time(HDC hDC);
	void Win(void);
	void Lose(void);
	void Escape_Map(void);

private:
	D3DXVECTOR3 vMonsterPos[5];//몬스터의 초기화 위치를 담을 벡터배열.

	DWORD dwZombieTime;
	DWORD m_dwWorldTime;
	int m_iMinute;
	int m_iHour;

	bool m_bWin;
	bool m_bLose;

};

