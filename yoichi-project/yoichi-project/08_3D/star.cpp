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
#include "star_factory.h"

//=============================================================================================
// マクロ定義
//=============================================================================================
#define STAR_COLOR_RED		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))						// 赤
#define STAR_COLOR_BLUE		(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))						// 青
#define STAR_COLOR_YELLOW	(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))						// 黄
#define STAR_COLOR_GREEN	(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))						// 緑

#define STAR_SIZE_X			(100.0f)												// 横幅
#define STAR_SIZE_Y			(100.0f)												// 縦幅
#define STAR_SIZE_Z			(0.0f)													// 奥行
#define STAR_SIZE			(D3DXVECTOR3(STAR_SIZE_X, STAR_SIZE_Y, STAR_SIZE_Z))	// サイズ

#define STAR_RADIUS			(STAR_SIZE_X)											// 星の半径

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
		// 初期化処理
		pStar->Init(pos);
		pStar->m_PosNumber = posNum;
	}

	return pStar;
}

//=============================================================================================
// 初期化処理
//=============================================================================================
HRESULT CStar::Init(D3DXVECTOR3 pos)
{
	// ビルボードの初期化処理
	CBillboard::Init(pos, STAR_SIZE);

	// テクスチャのポインタ
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// nullcheck
	if (pTexture != nullptr)
	{
		// テクスチャの設定
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EFFECT));
	}

	// 色の種類設定
	SetColorType();

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
