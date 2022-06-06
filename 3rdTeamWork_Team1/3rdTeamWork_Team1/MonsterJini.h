#pragma once
#include "Obj.h"
class CMonsterJini :
	public CObj
{
public:
	CMonsterJini();
	virtual ~CMonsterJini();

public:
	void	Set_ScalePlus(const float& _Scale) { m_fScale += _Scale; }
	void	Set_Scale(const float& _Scale) { m_fScale = _Scale; }
	void	Set_Tag(const string& _Tag) { m_strTag = _Tag; }
	void	Set_AttackDir(D3DXVECTOR3 _vDir) { m_vAttackDir = _vDir; }
	void	Set_AttackPos(D3DXVECTOR3 _vPos) { m_vAttackPos = _vPos; }
	void	Set_Score(float _Score) { m_fScore += _Score; }

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

public:
	void		Attack(D3DXVECTOR3 _vDir, float _fGiveScale);
	void		AttackRound();

private:
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fScale;
	float	m_fScaleSum;

	//float	m_fEllipse;

	float	m_fRadius;

	D3DXVECTOR3		m_vBodyLocal[4];
	D3DXVECTOR3		m_vBody[4];

	D3DXVECTOR3		m_vDirLocal;
	D3DXVECTOR3		m_vLookLocal;

	D3DXVECTOR3		m_vPosScreen;
	D3DXVECTOR3		m_vDirBefore;
	D3DXVECTOR3		m_vMouseTemp;

	//D3DXVECTOR3		m_vPosMiniMap;

	int		m_iPlayerColorR;
	int		m_iPlayerColorG;
	int		m_iPlayerColorB;

	string m_strTag;   // 부모 or 자식
	TCHAR	m_szName[64];

	bool	m_bBirth;
	bool	m_bMouseMove;
	D3DXVECTOR3		m_vAttackPos;
	D3DXVECTOR3		m_vAttackDir;
	DWORD			m_dwAttackMove;

	int		m_fScore;

	float	m_fRenderPercentTemp;

};

