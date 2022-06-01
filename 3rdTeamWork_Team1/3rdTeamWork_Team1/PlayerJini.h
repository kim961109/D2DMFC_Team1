#pragma once
#include "Obj.h"

class CPlayerJini :
	public CObj
{
public:
	CPlayerJini();
	virtual ~CPlayerJini();

// 여기
public :
	void	Set_ScalePlus(const float& _Scale) { m_fScale += _Scale; }
	void	Set_Scale(const float& _Scale) { m_fScale = _Scale; }
	void	Set_Tag(const string& _Tag) { m_strTag = _Tag; }
	const float&	Get_Scale() { return m_fScale; }

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

// 여기
public:
	void		Key_Input();
	void		Attack();

private:
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fScale;
	//float	m_fEllipse;

	D3DXVECTOR3		m_vBodyLocal[4];
	D3DXVECTOR3		m_vBody[4];

	D3DXVECTOR3		m_vDirLocal;
	D3DXVECTOR3		m_vLookLocal;

	int		m_iPlayerColorR;
	int		m_iPlayerColorG;
	int		m_iPlayerColorB;

	//여기
	string m_strName;
	string m_strTag;   // 부모 or 자식

};

