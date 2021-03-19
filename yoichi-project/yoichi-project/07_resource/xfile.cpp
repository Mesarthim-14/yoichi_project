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
#define XFILE_NAME_BG						("data/model/bg_dome001.x")		// 背景
#define XFILE_NAME_ITEM_BOX					("data/model/item_box.x")		// アイテムボックス
#define XFILE_NAME_BOMB_BOX					("data/model/item_bombbox.x")		// 偽ボックス
#define XFILE_NAME_BG				("data/model/bg_dome001.x")	// 背景
#define XFILE_NAME_WINDSPHERE		("data/model/windsphere.x")	// 風の球
#define XFILE_NAME_BARRIER			("data/model/barrier.x")	// バリア
#define XFILE_NAME_BARRIER_EFFECT	("data/model/barrier_effect.x")	// バリアエフェクト

// 階層構造モデルのファイル
#define HIERARCHY_FILENAME_PLAYER			("data/Text/motion_PLAYER.txt")	// プレイヤーのファイルネーム

//=============================================================================
// コンストラクタ
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
	memset(m_aModelFile, 0, sizeof(m_aModelFile));
	memset(m_pFileName, 0, sizeof(m_pFileName));
	memset(m_nMaxParts, 0, sizeof(m_nMaxParts));
	memset(m_aHierarchyModel, 0, sizeof(m_aHierarchyModel));
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
	D3DXLoadMeshFromX(XFILE_NAME_ITEM_BOX,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_ITEM_BOX].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_ITEM_BOX].dwNumMat,
		&m_aXfile[XFILE_NUM_ITEM_BOX].pMesh);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(XFILE_NAME_BOMB_BOX,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_BOMB_BOX].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_BOMB_BOX].dwNumMat,
		&m_aXfile[XFILE_NUM_BOMB_BOX].pMesh);

	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_aXfile[nCount].xFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_aXfile[nCount].pBuffMat,
			NULL,
			&m_aXfile[nCount].dwNumMat,
			&m_aXfile[nCount].pMesh);

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
// 階層構造のモデルファイル読み込み
//=============================================================================
HRESULT CXfile::HierarchyReadFile(void)
{
	FILE *pFile = NULL;		//FILEポインタ
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	// モデルのインデックス
	int nMotionType = 0;	// モーションのタイプ
	int nKeyNum = 0;		// キー番号
	int nMotionNum = 0;		// モーション番号

	// ファイルの名前を設定
	SetFileName();

	for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
	{
		// ファイルオープン
		pFile = fopen(m_pFileName[nModelCnt], "r");

		if (pFile != NULL)
		{
			do
			{
				//一列読み込んでモード情報を抽出
				fgets(aHeadData, sizeof(aHeadData), pFile);
				sscanf(aHeadData, "%s", aModeName);

				if (strcmp(aModeName, "MODEL_FILENAME") == 0)
				{
					//Xファイルの名前
					sscanf(aHeadData, "%*s %*s %s %*s %*s", m_aModelFile[nModelIndex][nModelCnt].xFileName);

					//インデックスを１つ進める
					nModelIndex++;
				}

				if (strcmp(aModeName, "CHARACTERSET") == 0)
				{
					//インデックスを最初に戻す
					nModelIndex = 0;

					//END_MOTIONSETを読み込むまで繰り返す
					while (strcmp(aModeName, "END_CHARACTERSET") != 0)
					{
						//一列読み込んでモード情報を抽出
						fgets(aHeadData, sizeof(aHeadData), pFile);
						sscanf(aHeadData, "%s", aModeName);

						if (strcmp(aModeName, "PARTSSET") == 0)
						{
							//END_PARTSSETを読み込むまで繰り返す
							while (strcmp(aModeName, "END_PARTSSET") != 0)
							{
								//一列読み込んでモード情報を抽出
								fgets(aHeadData, sizeof(aHeadData), pFile);
								sscanf(aHeadData, "%s", aModeName);

								if (strcmp(aModeName, "PARENT") == 0)
								{
									//親子情報の設定
									sscanf(aHeadData, "%*s %*s %d", &m_aModelFile[nModelIndex][nModelCnt].nParent);
								}
								if (strcmp(aModeName, "POS") == 0)
								{
									//位置の設定
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetPos.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetPos.y, &m_aModelFile[nModelIndex][nModelCnt].offsetPos.z);
								}
								if (strcmp(aModeName, "ROT") == 0)
								{
									//向きの設定
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetRot.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetRot.y, &m_aModelFile[nModelIndex][nModelCnt].offsetRot.z);
								}
							}

							//インデックスを１つ進める
							nModelIndex++;

							// パーツ数を数える
							m_nMaxParts[nModelCnt]++;

						}
					}
				}

			} while (strcmp(aModeName, "END_SCRIPT") != 0);

			//ファイルクローズ
			fclose(pFile);

			return S_OK;
		}
		else
		{
			//失敗した場合メッセージボックスを表示
			MessageBox(NULL, "モーションファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

			return	E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// 階層構造のモデルロード
//=============================================================================
HRESULT CXfile::HierarchyModelLoad(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
		{
			//モデルの読み込み
			D3DXLoadMeshFromX(m_aModelFile[nCount][nXFileNumCnt].xFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat,
				NULL,
				&m_aHierarchyModel[nCount][nXFileNumCnt].dwNumMat,
				&m_aHierarchyModel[nCount][nXFileNumCnt].pMesh);

			//マテリアル情報の解析
			D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_aHierarchyModel[nCount][nXFileNumCnt].dwNumMat; nCntMat++)
			{
				if (materials[nCntMat].pTextureFilename != NULL)
				{
					// ファイルネームの取得
					char cData[256] = {};

					sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice, cData, &m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntMat]);
				}
			}
		}
	}

	return S_OK;
}

//=============================================================================
// 階層構造のアンモデルロード
//=============================================================================
void CXfile::HierarchyModelUnLoad(void)
{
	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nCount]; nCount++)
		{
			//マテリアル情報の破棄
			if (m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat != NULL)
			{
				m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat->Release();
				m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat = nullptr;
			}

			//メッシュ情報の破棄
			if (m_aHierarchyModel[nCount][nXFileNumCnt].pMesh != NULL)
			{
				m_aHierarchyModel[nCount][nXFileNumCnt].pMesh->Release();
				m_aHierarchyModel[nCount][nXFileNumCnt].pMesh = nullptr;
			}

			// テクスチャの開放
			for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
			{
				if (m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntTexture] != NULL)
				{
					m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntTexture]->Release();
					m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntTexture] = NULL;
				}
			}
		}
	}
}

//=============================================================================
// ファイルの名前を設定
//=============================================================================
void CXfile::SetFileName(void)
{
	m_pFileName[HIERARCHY_XFILE_NUM_PLAYER] = HIERARCHY_FILENAME_PLAYER;
	m_aXfile[XFILE_NUM_BG].xFileName = XFILE_NAME_BG;
	m_aXfile[XFILE_NUM_WINDSPHERE].xFileName = XFILE_NAME_WINDSPHERE;
	m_aXfile[XFILE_NUM_BARRIER].xFileName = XFILE_NAME_BARRIER;
	m_aXfile[XFILE_NUM_BARRIER_EFFECT].xFileName = XFILE_NAME_BARRIER_EFFECT;
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