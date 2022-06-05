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
	void	Initialize(void);		// 초기화 함수
	void	Update(void);			// 매 프레임마다 갱신되는 데이터를 만드는 함수
	void    Late_Update(void);
	void	Render(void);			// 매 프레임마다 출력하는 함수
	void	Release(void);			// 동적할당한 포인터를 해제하는 함수

public:
	void    Reset_Scene(void);  // 모든 씬에서 부터 강제로 메인 화면으로 돌아옴.

private:
	HDC		m_hDC;
	DWORD m_dwTime;
	TCHAR m_szFPS[64];
	int	 m_iFPS;


};

