#pragma once
#include"Obj.h"
class CSnake_Body :public CObj
{
public:
	CSnake_Body();
	~CSnake_Body();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Get_HeadPos(D3DXVECTOR3 _Pos) { m_HeadPos = _Pos; }
	void Get_HeadInfo(INFO _Info) { m_tHead = _Info; }
	bool Get_bDead() { return m_bDead; }

private:
	void		Key_Input(void);

private:

	D3DXVECTOR3			m_vPoint[4];
	D3DXVECTOR3			m_vOriginPoint[4];

	float		m_fSpeed;
	float		m_fAngle;
	D3DXVECTOR3	m_HeadPos;
	INFO		m_tHead;
	INFO		m_tFrontBody;
	list<CObj*> m_SnakeList;

};

