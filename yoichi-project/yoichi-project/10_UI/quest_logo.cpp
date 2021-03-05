//=============================================================================
//
// クエストロゴのクラス [quest_logo.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "quest_logo.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define QUEST_LOGO_POS_X		(SCREEN_WIDTH / 2)										// X座標
#define QUEST_LOGO_POS_Y		(250.0f)												// Y座標
#define QUEST_LOGO_SIZE_X		(310.0f)												// Xサイズ
#define QUEST_LOGO_SIZE_Y		(40.0f)													// Yサイズ
#define QUEST_LOGO_POS		(D3DXVECTOR3(QUEST_LOGO_POS_X, QUEST_LOGO_POS_Y, 0.0f))		// 座標
#define QUEST_LOGO_SIZE		(D3DXVECTOR3(QUEST_LOGO_SIZE_X, QUEST_LOGO_SIZE_Y, 0.0f))	// サイズ

#define QUEST_LOGO_SCALE_UP_NUM	(0.05f)													// 拡大の値
#define QUEST_LOGO_MAX_NUM		(1.0f)													// 拡大の最大値
#define QUEST_LOGO_END_FLAME	(100)													// 終了の時間

//=============================================================================
// オブジェクト生成
//=============================================================================
CQuestLogo* CQuestLogo::Create(void)
{
	// オブジェクトを生成
	CQuestLogo* pQuestLogo = new CQuestLogo;

	// 初期化処理
	pQuestLogo->Init(QUEST_LOGO_POS, QUEST_LOGO_SIZE);

	return pQuestLogo;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CQuestLogo::CQuestLogo()
{
	m_nEndCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CQuestLogo::~CQuestLogo()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CQuestLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CUi::Init(pos, size);													// 座標、サイズ

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CQuestLogo::Uninit(void)
{
	// 終了処理
	CUi::Uninit();
}

//================================================
// 更新処理
//================================================
void CQuestLogo::Update(void)
{
	// 更新処理
	CUi::Update();

	// 終了のためのカウンター
	m_nEndCounter++;

	if (GetScale() < QUEST_LOGO_MAX_NUM)
	{
		// 拡大の値
		ScaleUp(QUEST_LOGO_SCALE_UP_NUM);
	}
	else
	{
		// 最大数に設定
		SetScale(QUEST_LOGO_MAX_NUM);
	}

	// 一定以上で
	if (m_nEndCounter >= QUEST_LOGO_END_FLAME)
	{
		// 終了処理
		Uninit();
	}
}

//================================================
// 描画処理
//================================================
void CQuestLogo::Draw(void)
{
	// 描画処理
	CUi::Draw();
}