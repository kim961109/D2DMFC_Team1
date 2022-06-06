#pragma once
#include "Obj.h"

class CPlayerJini :
	public CObj
{
public:
	CPlayerJini();
	virtual ~CPlayerJini();

public:
	void	Set_ScalePlus(const float& _Scale)	{ m_fScale += _Scale; }
	void	Set_Scale(const float& _Scale)		{ m_fScale = _Scale; }
	void	Set_Tag(const string& _Tag)			{ m_strTag = _Tag; }
	void	Set_AttackDir(D3DXVECTOR3 _vDir)	{ m_vAttackDir = _vDir; }
	void	Set_AttackPos(D3DXVECTOR3 _vPos)	{ m_vAttackPos = _vPos; }
	void	Set_Dir(D3DXVECTOR3 _vDir)			{ m_tInfo.vDir = _vDir; }


	const float&	Get_Scale() { return m_fScale; }
	const float&	Get_Radius() { return m_fRadius; }
	const string&	Get_Tag() { return m_strTag; }
	const bool&		Get_bBirth() { return m_bBirth; }

	


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	// 여기
public:
	void		Offset();
	void		Key_Input();
	void		Attack(D3DXVECTOR3 _vDir, float _fGiveScale);
	void		AttackRound();


private:
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fScale;
	float	m_fRadius;

	D3DXVECTOR3		m_vBodyLocal[4];
	D3DXVECTOR3		m_vBody[4];

	D3DXVECTOR3		m_vDirLocal;
	D3DXVECTOR3		m_vLookLocal;

	D3DXVECTOR3		m_vPosScreen;
	D3DXVECTOR3		m_vDirBefore;
	D3DXVECTOR3		m_vMouseTemp;

	D3DXVECTOR3		m_vPosMiniMap;

	int		m_iPlayerColorR;
	int		m_iPlayerColorG;
	int		m_iPlayerColorB;
	int		m_iPlayerColorROrigin;
	int		m_iPlayerColorGOrigin;
	int		m_iPlayerColorBOrigin;

	float	m_fDistanceMouse;

	//여기
	string m_strTag;   // 부모 or 자식
	TCHAR	m_szName[64];
	TCHAR	m_szScore[64];

	bool	m_bBirth;
	bool	m_bMouseMove;
	D3DXVECTOR3		m_vAttackPos;
	D3DXVECTOR3		m_vAttackDir;
	DWORD			m_dwAttackMove;
	DWORD			m_dwRoundAttackTime;
	bool			m_bRoundAttack;

	float	m_fRenderPercentTemp;

	DWORD			m_dwDeathTime;


};

