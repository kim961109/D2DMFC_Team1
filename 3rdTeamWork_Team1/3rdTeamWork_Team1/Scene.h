#pragma once
class CScene
{
public:
	CScene();
	~CScene();

public:
	virtual void	Initialize(void) PURE;
	virtual void	Update(void) PURE;
	virtual void	Late_Update(void) PURE;
	virtual void	Render(HDC hDC) PURE;
	virtual void	Release(void) PURE;
};

