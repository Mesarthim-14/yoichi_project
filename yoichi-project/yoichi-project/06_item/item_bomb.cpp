//=============================================================================
//
// アイテムボムクラス [item_bomb.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_bomb.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "item_bombbox.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CItemBomb::CItemBomb(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBomb::~CItemBomb()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CItemBomb * CItemBomb::Create(const int nNumber)
{
	// メモリ確保
	CItemBomb *pItemBomb = new CItemBomb;

	// !nullcheck
	if (pItemBomb != nullptr)
	{
		// 初期化処理
		pItemBomb->Init();
		pItemBomb->SetNumber(nNumber);
	}

	return pItemBomb;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBomb::Init(void)
{
	// メモリ確保
	CUi *pUi = CUi::Create(ITEM_UI_POS, ITEM_UI_SIZE);

	// UIのポインタ設定
	SetUi(pUi);

	// !nullcheck
	if (pUi != nullptr)
	{
		// テクスチャのポインタ取得
		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// テクスチャの設定
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_BOMB));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBomb::Update(void)
{
	// アイテムの更新処理
	CItem::Update();

	// アイテムが使われたら
	if (GetUse() == true)
	{
		// フレームカウンターを進める
		m_nCounter++;
	}
}

//=============================================================================
// アイテムの効果設定
//=============================================================================
void CItemBomb::SetItem(void)
{
	// プレイヤーの番号取得
	int nPlayerNum = GetPlayerNum();

	// 座標
	D3DXVECTOR3 pos = CGame::GetPlayer(nPlayerNum)->GetPos();
	pos.y += PLAYER_BASE_POS_Y;

	// 偽ボックスの生成
	CItemBombBox::Create(pos, MODEL_DEFAULT_SIZE, nPlayerNum);

	// Uiの終了処理
	UiUninit();

	// 終了フラグ
	UndoItem();
}

//=============================================================================
// アイテムの効果を戻す
//=============================================================================
void CItemBomb::UndoItem(void)
{
	// 終了フラグ
	SetEnd(true);
}