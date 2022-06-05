#pragma once
#include "Include.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void	Initialize(void);		// �ʱ�ȭ �Լ�
	void	Update(void);			// �� �����Ӹ��� ���ŵǴ� �����͸� ����� �Լ�
	void    Late_Update(void);
	void	Render(void);			// �� �����Ӹ��� ����ϴ� �Լ�
	void	Release(void);			// �����Ҵ��� �����͸� �����ϴ� �Լ�

public:
	void    Reset_Scene(void);  // ��� ������ ���� ������ ���� ȭ������ ���ƿ�.

private:
	HDC		m_hDC;
	DWORD m_dwTime;
	TCHAR m_szFPS[64];
	int	 m_iFPS;


};

