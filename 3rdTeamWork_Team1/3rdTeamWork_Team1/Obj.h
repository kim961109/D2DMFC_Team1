#pragma once
#include "Include.h"

class CObj
{
public:
	CObj();
	~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;

protected:
	void Update_Rect(void);

public:
	OBJINFO Get_ObjInfo(void) { return m_tObjInfo; }
	RECT Get_Rect(void) { return m_tRect; }
	INFO Get_Info(void) { return m_tInfo; }

protected:
	OBJINFO m_tObjInfo;		//충돌하는 벽 같은 움직이지 않을 오브젝트는 이걸로 월드 좌표만 주고
	RECT m_tRect;			//움직이지 않는 물체의 렉트.

	INFO m_tInfo;			//움직이는 플레이어와 같은 오브젝트는 D3D 벡터 사용하자.
};

