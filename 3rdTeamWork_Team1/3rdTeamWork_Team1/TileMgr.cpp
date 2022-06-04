#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "SceneMgr.h"
#include "TileMS.h"
CTileMgr*	CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	//m_CheckScene = SC_JINI;
	if (SC_KJE == CSceneMgr::Get_Instance()->Get_SceneID()) 
	{
		for (int i = 0; i < TILEY; ++i)
		{
			for (int j = 0; j < TILEX; ++j)
			{
				if ((i >= 0 && i < 3) || (i >= TILEY - 3 && i <= TILEY) || (j >= 0 && j < 3) || (j >= TILEX - 3 && j <= TILEX))
				{
					float		fX = (TILECX >> 1) + float(TILECX * j);
					float		fY = (TILECY >> 1) + float(TILECY * i);
					CObj*	pTile = CAbstractFactory<CTile>::Create(fX, fY);
					m_vecTile.push_back(pTile);

					if ((i >= 0 && i < 3) || (i >= TILEY - 3 && i <= TILEY) || (j >= 0 && j < 3) || (j >= TILEX - 3 && j <= TILEX))
					{
						dynamic_cast<CTile*>(pTile)->Set_Option(1);
					}
					//dynamic_cast<CTile*>(pTile)->Set_Option(1);
				}
			}
		}
	}
	if (SC_KMS == CSceneMgr::Get_Instance()->Get_SceneID()) 
	{
		for (int i = 0; i < TILEB; ++i)
		{
			for (int j = 0; j < TILEA; ++j)
			{
				float		fX = (TILEDX >> 1) + float(TILEDX * j);
				float		fY = (TILEDY >> 1) + float(TILEDY * i);
				CObj*	pTile = CAbstractFactory<CTileMS>::Create(fX, fY);
				m_vecTile.push_back(pTile);
				
			}
		}
	}
}

void CTileMgr::Update()
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

void CTileMgr::Late_Update()
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
}

void CTileMgr::Render(HDC hDC)
{
	for (auto& iter : m_vecTile)
	{
		iter->Render(hDC);
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), CDeleteObj());
	m_vecTile.clear();
}

void CTileMgr::Picking_Tile(POINT _pt, const int& _iDrawID, const int& _iOption)
{
	int		x = _pt.x / TILECX;
	int		y = _pt.y / TILECY;

	int	iIndex = y * TILEX + x;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(_iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(_iOption);
}

void CTileMgr::Save_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int		iDrawID = 0, iOption = 0;
	DWORD	dwByte = 0;

	for (auto& iter : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(iter)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(iter)->Get_Option();

		WriteFile(hFile, &iter->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CTileMgr::Load_Tile(void)
{
	HANDLE		hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	OBJINFO		tInfo{};
	int			iDrawID = 0, iOption = 0;
	DWORD		dwByte = 0;

	Release();
	
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj*		pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pObj)->Set_Option(iOption);

		m_vecTile.push_back(pObj);
	}
	CloseHandle(hFile);
}
