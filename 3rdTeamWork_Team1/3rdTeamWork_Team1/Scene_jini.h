#pragma once
#include "Scene.h"
#include "Obj.h"

class CScene_jini :
	public CScene
{
public:
	CScene_jini();
	virtual ~CScene_jini();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public :
	void		Bublle_Sort(int _list[4], int n);
private:
	DWORD	m_dwJellyCreate;
	DWORD	m_dwJellyCreate2;
	DWORD	m_dwCollisionJelly;


	CObj*	m_pPlayer;
	CObj*	m_pMonster1;
	CObj*	m_pMonster2;
	CObj*	m_pMonster3;

	vector<CObj*> m_vecRank;



};

