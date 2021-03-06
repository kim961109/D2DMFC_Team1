#pragma once
#include "Include.h"

class CObj
{
public:
	CObj();
	~CObj();

public:
	virtual void Initialize(void) PURE;
	virtual int Update(void) PURE;
	virtual void Late_Update(void) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release(void) PURE;

protected:
	void Update_Rect(void);
	void Move_Frame(void);

public:
	OBJINFO Get_ObjInfo(void) { return m_tObjInfo; }
	RECT Get_Rect(void) { return m_tRect; }
	INFO Get_Info(void) { return m_tInfo; }

	void Set_Dead() { m_bDead = true; }
    void Set_Dead(bool _b) { m_bDead = _b; }
	void Set_Pos(float _fX, float _fY, float _fZ) { m_tInfo.vPos.x = _fX; m_tInfo.vPos.y = _fY; m_tInfo.vPos.z = _fZ; }
	void Set_Dir(float _fX, float _fY, float _fZ) { m_tInfo.vDir.x = _fX; m_tInfo.vDir.y = _fY; m_tInfo.vDir.z = _fZ; }
	void Set_ObjPos(float _fX, float _fY) { m_tObjInfo.fX = _fX;  m_tObjInfo.fY = _fY; }
	void Set_PosX(float _fX) { m_tObjInfo.fX += _fX; }
	void Set_PosY(float _fY) { m_tObjInfo.fY += _fY; }

protected:
	OBJINFO m_tObjInfo;		//충돌하는 벽 같은 움직이지 않을 오브젝트는 이걸로 월드 좌표만 주고
	RECT m_tRect;			//움직이지 않는 물체의 렉트.

	INFO m_tInfo;//움직이는 플레이어와 같은 오브젝트는 D3D 벡터 사용하자.

	bool		m_bDead;

	FRAME		m_tFrame;
	TCHAR*		m_pFrameKey;

};

