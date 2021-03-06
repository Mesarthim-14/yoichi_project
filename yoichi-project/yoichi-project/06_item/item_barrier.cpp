//=============================================================================
//
// アイテムバリアクラス [item_barrier.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_barrier.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "barrier.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BARRIER_TIME			(200)	// バリアの間隔

//=============================================================================
// コンストラクタ
//=============================================================================
CItemBarrier::CItemBarrier(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBarrier::~CItemBarrier()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CItemBarrier * CItemBarrier::Create(const int nNumber)
{
	// メモリ確保
	CItemBarrier *pItemBarrier = new CItemBarrier;

	// !nullcheck
	if (pItemBarrier != nullptr)
	{
		// 初期化処理
		pItemBarrier->SetNumber(nNumber);
		pItemBarrier->Init();
	}

	return pItemBarrier;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBarrier::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_BARRIER));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBarrier::Update(void)
{
	// アイテムの更新処理
	CItem::Update();

	// アイテムが使われたら
	if (GetUse() == true)
	{
		// フレームカウンターを進める
		m_nCounter++;

		// カウンターが一定量で
		if (m_nCounter >= BARRIER_TIME)
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
void CItemBarrier::SetItem(void)
{
	// アイテムを持っているプレイヤーを参照
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// 無敵状態にする
		pPlayer->SetArmor(true);
		CBARRIER::Create(pPlayer->GetPos(), BARRIER_MAX_SIZE, 0.0f, BARRIER_MAX_SIZE, GetPlayerNum());
	}

	// 使用状態にする
	SetUse(true);

	// Uiの終了処理
	UiUninit();
}

//=============================================================================
// アイテムの効果を戻す
//=============================================================================
void CItemBarrier::UndoItem(void)
{
	// アイテムを持っているプレイヤーを参照
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// スピードを上昇
		pPlayer->SetArmor(false);
	}

	// 終了フラグを立てる
	SetEnd(true);
}