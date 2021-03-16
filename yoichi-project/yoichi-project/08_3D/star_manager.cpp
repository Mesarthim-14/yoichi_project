//=============================================================================
//
// アイテム管理クラス [star_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "star_manager.h"
#include "manager.h"
#include "renderer.h"
#include "itembox.h"
#include "star.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_STAR_NUM			(30)						// アイテムの出現数
#define STAR_POS_INTERBAL_XToZ	(1800.0f)					// 星の間隔
#define STAR_POS_INTERBAL_Y		(1000.0f)					// 星の間隔
#define STAR_POS_LIMIT_XToZ		(-MAP_LIMIT+(MAP_LIMIT/2))	// 出現の範囲
#define STAR_POS_LIMIT_Y		(3000.0f)					// 出現の範囲
#define STAR_COLOR_CHANGE_FLAME	(1800)						// 色を変えるフレーム

//=============================================================================
// static初期化処理
//=============================================================================
CStar::STAR_COLOR_TYPE CStarManager::m_GameColor = CStar::STAR_COLOR_TYPE_NONE;

//=============================================================================
// コンストラクタ
//=============================================================================
CStarManager::CStarManager()
{
	m_nCounter = 0;
	memset(m_bMapFlag, 0, sizeof(m_bMapFlag));
}

//=============================================================================
// デストラクタ
//=============================================================================
CStarManager::~CStarManager()
{
	m_GameColor = CStar::STAR_COLOR_TYPE_NONE;
}

//=============================================================================
// インスタンス生成
//=============================================================================
CStarManager * CStarManager::Create(void)
{
	// メモリ確保
	CStarManager *pStarFactory = new CStarManager;

	// !nullcheck
	if (pStarFactory != nullptr)
	{
		// 初期化処理
		pStarFactory->Init();
	}

	return pStarFactory;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CStarManager::Init(void)
{
	// スターの生成
	CreateStar();

	// 倍率が上がる色の設定
	SetGameColor();
}

//=============================================================================
// 終了処理
//=============================================================================
void CStarManager::Uninit(void)
{
	// メモリ確保
	for (unsigned nCount = 0; nCount < m_pStar.size(); nCount++)
	{
		// !nullcheck
		if (m_pStar[nCount] != nullptr)
		{
			// 終了処理
			m_pStar[nCount]->Uninit();
			m_pStar[nCount] = nullptr;
		}
	}

	// 配列があれば
	if (m_pStar.size() != NULL)
	{
		// 配列のクリア
		m_pStar.clear();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CStarManager::Update(void)
{
	m_nCounter++;

	// カウンター
	if (m_nCounter <= STAR_COLOR_CHANGE_FLAME)
	{
		// ゲームの色の設定
		SetGameColor();

		m_nCounter = 0;
	}

	// 一定数以下になったら
	if (m_pStar.size() < MAX_STAR_NUM)
	{
		// 星の生成
		CreateStar();
	}

	// 配列が0でなければ
	if (m_pStar.size() != NULL)
	{
		// サイズ分回す
		for (unsigned nCount = 0; nCount < m_pStar.size(); nCount++)
		{
			// 当たり判定
			if (m_pStar[nCount]->Collision() == true)
			{
				// スターを減らす
				SubStarNum(nCount, m_pStar[nCount]->GetPosNumber());
			}
		}
	}
}

//=============================================================================
// アイテムクラスの生成
//=============================================================================
void CStarManager::CreateStar(void)
{
	// 最大数より少なかったら
	while (m_pStar.size() < MAX_STAR_NUM)
	{
		// 配列の番号を決める
		int nNumX = rand() % STAR_CREATE_SIZE;
		int nNumY = rand() % STAR_CREATE_SIZE;
		int nNumZ = rand() % STAR_CREATE_SIZE;

		// 使われていなかったら
		if (m_bMapFlag[nNumX][nNumY][nNumZ] == false)
		{
			// 座標設定
			D3DXVECTOR3 pos = D3DXVECTOR3(
				STAR_POS_LIMIT_XToZ +(nNumX * STAR_POS_INTERBAL_XToZ),
				STAR_POS_LIMIT_Y + (nNumY * STAR_POS_INTERBAL_Y),
				STAR_POS_LIMIT_XToZ + (nNumZ * STAR_POS_INTERBAL_XToZ));

			// 座標番号設定
			CStar::POS_NUMBER posNumber = { nNumX, nNumY, nNumZ };

			// 星の生成
			m_pStar.push_back(CStar::Create(pos, posNumber));

			m_bMapFlag[nNumX][nNumY][nNumZ] = true;
		}
	}
}

//=============================================================================
// スターの総数を減らす
//=============================================================================
void CStarManager::SubStarNum(int nCount, CStar::POS_NUMBER posNum)
{
	// 座標番号のフラグを消す
	m_bMapFlag[posNum.nNumX][posNum.nNumY][posNum.nNumZ] = false;

	// 当たった星を消す
	m_pStar.erase(m_pStar.begin() + nCount);
}

//=============================================================================
// 色の設定
//=============================================================================
CStar::STAR_COLOR_TYPE CStarManager::SetColorType(void)
{
	// 乱数
	int nColorType = rand() % (int)CStar::STAR_COLOR_TYPE_MAX;

	return (CStar::STAR_COLOR_TYPE)nColorType;
}

//=============================================================================
// ゲームの色設定
//=============================================================================
void CStarManager::SetGameColor(void)
{
	// ゲームの色の設定
	m_GameColor = SetColorType();
}