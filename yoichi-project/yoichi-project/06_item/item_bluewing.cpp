//=============================================================================
//
// アイテム青い羽根クラス [item_bluewing.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_bluewing.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BLUE_WING_SPEED_UP_NUM	(2)		// 速度の情報
#define BLUE_WING_TIME			(180)	// 速度アップのカウント

//=============================================================================
// コンストラクタ
//=============================================================================
CItemBlueWing::CItemBlueWing(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBlueWing::~CItemBlueWing()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CItemBlueWing * CItemBlueWing::Create(const int nNumber)
{
	// メモリ確保
	CItemBlueWing *pItemBlueWing = new CItemBlueWing;

	// !nullcheck
	if (pItemBlueWing != nullptr)
	{
		// 初期化処理
		pItemBlueWing->Init();
		pItemBlueWing->SetNumber(nNumber);
	}

	return pItemBlueWing;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBlueWing::Init(void)
{
	// メモリ確保
	CUi *pUi = CUi::Create(CItem::SetPosition(GetPlayerNum()), ITEM_UI_SIZE);

	// UIのポインタ設定
	SetUi(pUi);

	// !nullcheck
	if (pUi != nullptr)
	{
		// テクスチャのポインタ取得
		CTexture *pTexture = GET_TEXTURE_PTR;

		// テクスチャの設定
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_BLUE_WING));
	}
	
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBlueWing::Update(void)
{
	// アイテムの更新処理
	CItem::Update();

	// アイテムが使われたら
	if (GetUse() == true)
	{
		// フレームカウンターを進める
		m_nCounter++;

		// カウンターが一定量で
		if (m_nCounter >= BLUE_WING_TIME)
		{
			// アイテムの効果を戻す
			UndoItem();

			m_nCounter = 0;
		}
	}
}

//=============================================================================
// アイテムの効果設定
//=============================================================================
void CItemBlueWing::SetItem(void)
{
	// アイテムを持っているプレイヤーを参照
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// スピードを上昇
		pPlayer->SetSpeed(pPlayer->GetBaseSpeed() * BLUE_WING_SPEED_UP_NUM);

		// 使用状態にする
		SetUse(true);

		// Uiの終了処理
		UiUninit();
	}
}

//=============================================================================
// アイテムの効果を戻す
//=============================================================================
void CItemBlueWing::UndoItem(void)
{
	// アイテムを持っているプレイヤーを参照
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// スピードを上昇
		pPlayer->SetSpeed(pPlayer->GetBaseSpeed());
	}

	// 終了フラグを立てる
	SetEnd(true);
}
