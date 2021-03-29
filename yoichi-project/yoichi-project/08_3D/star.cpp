//=============================================================================================
//
// 星クラス [star.cpp]
// Author : Konishi Yuuto
//
//=============================================================================================

//=============================================================================================
// インクルード
//=============================================================================================
#include "star.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "star_manager.h"
#include "renderer.h"

//=============================================================================================
// マクロ定義
//=============================================================================================

#define STAR_SIZE_X				(150.0f)												// 横幅
#define STAR_SIZE_Y				(150.0f)												// 縦幅
#define STAR_SIZE_Z				(0.0f)													// 奥行
#define STAR_SIZE				(D3DXVECTOR3(STAR_SIZE_X, STAR_SIZE_Y, STAR_SIZE_Z))	// サイズ

#define STAR_RADIUS				(STAR_SIZE_X)											// 星の半径
#define STAR_ALPHA_NUM			(40)													// アルファテストの値

#define DEFAULT_ADD_STAR_NUM	(1)														// 通常の星獲得数
#define SUITABLE_ADD_STAR_NUM	(5)														// ゲーム状態に適した色の場合

//=============================================================================================
// コンストラクタ
//=============================================================================================
CStar::CStar(PRIORITY Priority)
{
	m_PosNumber = { 0,0,0 };
	m_ColorType = STAR_COLOR_TYPE_NONE;
}

//=============================================================================================
// デストラクタ
//=============================================================================================
CStar::~CStar()
{
}

//=============================================================================================
// 星の生成
//=============================================================================================
CStar * CStar::Create(D3DXVECTOR3 pos, POS_NUMBER posNum)
{
	// メモリ確保
	CStar *pStar = new CStar;

	// !nullcheck
	if (pStar != nullptr)
	{
		pStar->SetPos(pos);
		pStar->SetSize(STAR_SIZE);
		// 初期化処理
		pStar->Init();
		pStar->m_PosNumber = posNum;
	}

	return pStar;
}

//=============================================================================================
// 初期化処理
//=============================================================================================
HRESULT CStar::Init(void)
{
	// ビルボードの初期化処理
	CBillboard::Init();

	// テクスチャのポインタ
	CTexture *pTexture = GET_TEXTURE_PTR;

	// nullcheck
	if (pTexture != nullptr)
	{
		// テクスチャの設定
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EFFECT));
	}

	// 色の設定
	SetColorType();

	// アルファテストの値
	SetAlphaNum(STAR_ALPHA_NUM);

	return S_OK;
}

//=============================================================================================
// 更新処理
//=============================================================================================
void CStar::Update(void)
{
}

//=============================================================================================
// 描画処理
//=============================================================================================
void CStar::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}

//=============================================================================
// 当たり判定の処理
//=============================================================================
bool CStar::Collision(void)
{
	// プレイヤーの数
	int nPlayerNum = CGame::GetPlayerNum();

	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		// プレイヤーの関数
		CPlayer *pPlayer = CGame::GetPlayer(nCount);

		// 当たり判定
		if (CCollision::CollisionCircularAndCircular(
			GetPos(), pPlayer->GetPos(),
			STAR_RADIUS, pPlayer->GetRadius()) == true)
		{
			// 色が適した
			if (CStarManager::GetGameStarColor() == m_ColorType)
			{
				// 星の加算
				pPlayer->AddStarNum(SUITABLE_ADD_STAR_NUM);
			}
			else
			{
				// 星の加算
				pPlayer->AddStarNum(DEFAULT_ADD_STAR_NUM);
			}

			// 終了処理
			Uninit();

			return true;
		}
	}

	return false;
}

//=============================================================================
// 色の種類設定
//=============================================================================
void CStar::SetColorType(void)
{
	int nColorType = rand() % (int)STAR_COLOR_TYPE_MAX;

	m_ColorType = (STAR_COLOR_TYPE)nColorType;

	// 色の設定
	switch (m_ColorType)
	{
	case STAR_COLOR_TYPE_RED:
		// 赤色
		SetColor(STAR_COLOR_RED);
		break;

	case STAR_COLOR_TYPE_BLUE:
		// 青色
		SetColor(STAR_COLOR_BLUE);
		break;

	case STAR_COLOR_TYPE_GREEN:
		// 緑色
		SetColor(STAR_COLOR_GREEN);
		break;

	case STAR_COLOR_TYPE_YELLOW:
		// 黄色
		SetColor(STAR_COLOR_YELLOW);
		break;
	}

}
