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
	OBJINFO m_tObjInfo;		//�浹�ϴ� �� ���� �������� ���� ������Ʈ�� �̰ɷ� ���� ��ǥ�� �ְ�
	RECT m_tRect;			//�������� �ʴ� ��ü�� ��Ʈ.

	INFO m_tInfo;			//�����̴� �÷��̾�� ���� ������Ʈ�� D3D ���� �������.
};

