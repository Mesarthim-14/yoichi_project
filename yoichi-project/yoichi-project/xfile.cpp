//=============================================================================
//
// Xファイルの管理クラス [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
// モデルネーム
#define XFILE_NAME_BG						("data/model/bg_dome001.x")					// 背景

//=============================================================================
// コンストラクタ
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
}

//=============================================================================
// デストラクタ
//=============================================================================
CXfile::~CXfile()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CXfile * CXfile::Create(void)
{
	// メモリ確保
	CXfile *pXfile = new CXfile;

	return pXfile;
}

//=============================================================================
// Xファイルロード
//=============================================================================
HRESULT CXfile::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(XFILE_NAME_BG,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_BG].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_BG].dwNumMat,
		&m_aXfile[XFILE_NUM_BG].pMesh);

	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//マテリアル情報の解析
		D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
		{
			// ファイルネームの取得
			char cData[128] = {};

			sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[nCount].apTexture[nCntMat]);
		}
	}

	return S_OK;
}

//=============================================================================
// Xファイルアンロード
//=============================================================================
void CXfile::ModelUnLoad(void)
{
	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//メッシュの破棄
		if (m_aXfile[nCount].pMesh != NULL)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_aXfile[nCount].pBuffMat != NULL)
		{
			m_aXfile[nCount].pBuffMat->Release();
			m_aXfile[nCount].pBuffMat = NULL;
		}

		for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
		{
			if (m_aXfile[nCount].apTexture[nCntTexture] != NULL)
			{
				m_aXfile[nCount].apTexture[nCntTexture]->Release();
				m_aXfile[nCount].apTexture[nCntTexture] = NULL;
			}
		}
	}
}

//=============================================================================
// モデルの情報
//=============================================================================
CXfile::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}

//=============================================================================
// モデルに使用するテクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(XFILE_NUM TexNum)
{
	if (TexNum < XFILE_NUM_MAX)
	{
		if (m_aXfile[TexNum].apTexture != NULL)
		{
			return m_aXfile[TexNum].apTexture;
		}
	}

	return nullptr;
}
