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

typedef struct tagFrame
{
	int		iFrameStart;		// 원하는 지점부터 스프라이트 이미지 구동 시작
	int		iFrameEnd;			// 스프라이트가 끝나는 지점을 지정
	int		iMotion;			// 모션 인덱스

	DWORD	dwSpeed;			// 스프라이트가 돌아가는 속도
	DWORD	dwTime;				// 스프라이트 위치가 변경되는 시간 

}FRAME;
