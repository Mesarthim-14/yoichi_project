//=============================================================================
//
// アイテム青い羽根クラス [item_mhand.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_mhand.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "magichand.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MHAND_TIME			(120)	// アイテム効果のカウント
#define MHAND_RADIUS_UP		(5)		// 半径の拡大率

//=============================================================================
// コンストラクタ
//=============================================================================
CItemMhand::CItemMhand(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	m_fPlayerRadius = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemMhand::~CItemMhand()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CItemMhand * CItemMhand::Create(const int nNumber)
{
	// メモリ確保
	CItemMhand *pItemMhand = new CItemMhand;

	// !nullcheck
	if (pItemMhand != nullptr)
	{
		// 初期化処理
        pItemMhand->SetNumber(nNumber);
		pItemMhand->Init();

	}

	return pItemMhand;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemMhand::Init(void)
{
	// メモリ確保
	CUi *pUi = CUi::Create(SetPosition(this->GetPlayerNum()), ITEM_UI_SIZE);

	// UIのポインタ設定
	SetUi(pUi);

	// !nullcheck
	if (pUi != nullptr)
	{
		// テクスチャのポインタ取得
		CTexture *pTexture = GET_TEXTURE_PTR;

		// テクスチャの設定
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_MHAND));
	}

	// プレイヤーの番号
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// プレイヤーの半径
		m_fPlayerRadius = pPlayer->GetRadius();
	}


	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemMhand::Update(void)
{
	// アイテムの更新処理
	CItem::Update();

	// アイテムが使われたら
	if (GetUse() == true)
	{
		// フレームカウンターを進める
		m_nCounter++;

		// カウンターが一定量で
		if (m_nCounter >= MHAND_TIME)
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
void CItemMhand::SetItem(void)
{
	if (GetUse() == false)
	{
		// アイテムを持っているプレイヤーを参照
		CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());
		int nNum = GetPlayerNum();
		// !nullcheck
		if (pPlayer != nullptr)
		{
			// 半径を上昇
			pPlayer->SetRadius(pPlayer->GetRadius() * MHAND_RADIUS_UP);
			// マジックハンドのエフェクト
			CMagichand::Create(-MAGICHAND_DISTANCE , CTexture::SEPARATE_TEX_MAGICHANDLEFT, nNum);
			CMagichand::Create(MAGICHAND_DISTANCE, CTexture::SEPARATE_TEX_MAGICHANDRIGHT, nNum);
		}

		// 使用状態にする
		SetUse(true);

		// Uiの終了処理
		UiUninit();
	}
}

//=============================================================================
// アイテムの効果を戻す
//=============================================================================
void CItemMhand::UndoItem(void)
{
	// アイテムを持っているプレイヤーを参照
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 半径を戻す
		pPlayer->SetRadius(pPlayer->GetBaseRadius());
	}

	// 終了フラグを立てる
	SetEnd(true);
}