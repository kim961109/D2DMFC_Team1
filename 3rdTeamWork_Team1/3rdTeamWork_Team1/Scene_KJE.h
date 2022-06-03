#pragma once
#include "Scene.h"
#include "Snake_Head.h"
class CScene_KJE :
	public CScene
{
public:
	CScene_KJE();
	virtual ~CScene_KJE();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	list<CObj*> m_SnakeList;
	list<CObj*> m_AppleList;

	int		m_iMilliSecond;
	int		m_iSecond;
	int		m_iApple;
	
};

