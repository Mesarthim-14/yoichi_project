//=============================================================================
//
// ステージマップクラス [stage_map.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "stage_map.h"
#include "manager.h"
#include "renderer.h"
#include "itembox.h"
#include "star.h"
#include "meshfield.h"
#include "bg.h"
#include "mesh_pillar.h"

//=======================================================================================
// マクロ定義
//=======================================================================================
#define SCAFFOLD_NUM_X	(3)				// 足場の数
#define SCAFFOLD_NUM_Z	(3)				// 足場の数
#define SCAFFOLD_INTER	(3000.0f)		// 足場の間隔

//=============================================================================
// コンストラクタ
//=============================================================================
CStageMap::CStageMap()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CStageMap::~CStageMap()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CStageMap * CStageMap::Create(void)
{
	// メモリ確保
	CStageMap *pStageMap = new CStageMap;

	// !nullcheck
	if (pStageMap != nullptr)
	{
		// 初期化処理
		pStageMap->CreateMap();
	}

	return pStageMap;
}

//=============================================================================
// 終了処理
//=============================================================================
void CStageMap::Uninit(void)
{
}

//=============================================================================
// マップ生成クラス
//=============================================================================
void CStageMap::CreateMap(void)
{
	// メッシュフィールド
	CMeshField::Create();

	// 背景ドームの生成
	 CBg::Create(BG_POS, BG_SIZE);

	// 足場の生成
	for (int nCntX = 0; nCntX < SCAFFOLD_NUM_X; nCntX++)
	{
		for (int nCntZ = 0; nCntZ < SCAFFOLD_NUM_Z; nCntZ++)
		{
			// 円柱の生成
			m_pMeshPillar.push_back(CMeshPillar::Create(D3DXVECTOR3(
				-SCAFFOLD_INTER + (nCntX*SCAFFOLD_INTER),
				0.0f,
				-SCAFFOLD_INTER + (nCntZ*SCAFFOLD_INTER)),
				CMesh3d::MESH_TYPE_SCAFFOLD));
		}
	}
}