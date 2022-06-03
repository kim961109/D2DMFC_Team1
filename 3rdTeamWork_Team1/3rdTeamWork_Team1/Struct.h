#pragma once
typedef	struct tagInfo
{

	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;

	D3DXMATRIX		matWorld;


}INFO;

typedef struct tagObjInfo
{
	float fX;
	float fY;

	float fCX;
	float fCY;

}OBJINFO, UIINFO;

//typedef struct tagUIInfo
//{
//	float fX;
//	float fY;
//
//	float fCX;
//	float fCY;
//
//}UIINFO;
