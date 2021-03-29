//=============================================================================
//
// アイテム赤い羽根クラス [item_redwing.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_redwing.h"
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
#define RED_WING_SPEED_DOWN_NUM	(2)				// 速度の情報
#define RED_WING_TIME			(180)			// 速度アップのカウント

//=============================================================================
// コンストラクタ
//=============================================================================
CItemRedWing::CItemRedWing(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	memset(m_bValid, false, sizeof(m_bValid));
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemRedWing::~CItemRedWing()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CItemRedWing * CItemRedWing::Create(const int nNumber)
{
	// メモリ確保
	CItemRedWing *pItemRedWing = new CItemRedWing;

	// !nullcheck
	if (pItemRedWing != nullptr)
	{
		// 初期化処理
		pItemRedWing->Init();
		pItemRedWing->SetNumber(nNumber);
	}

	return pItemRedWing;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemRedWing::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_RED_WING));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemRedWing::Update(void)
{
	// アイテムの更新処理
	CItem::Update();

	// アイテムが使われたら
	if (GetUse() == true)
	{
		// フレームカウンターを進める
		m_nCounter++;

		// カウンターが一定量で
		if (m_nCounter >= RED_WING_TIME)
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
void CItemRedWing::SetItem(void)
{
	// プレイヤー分回す
	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// 使ったプレイヤー以外
		if (nCount != GetPlayerNum())
		{
			// アイテムを持っているプレイヤーを参照
			CPlayer *pPlayer = CGame::GetPlayer(nCount);

			// !nullcheck
			if (pPlayer != nullptr)
			{
				// プレイヤーが無敵じゃなかったら
				if (pPlayer->GetArmor() == false)
				{
					if (GetUse() == false)
					{
						// 相手の速度を低下
						pPlayer->SetSpeed(pPlayer->GetBaseSpeed() / RED_WING_SPEED_DOWN_NUM);

						// 効果を有効にする
						m_bValid[nCount] = true;
					}
				}
			}
		}
	}

	// 使用フラグ
	SetUse(true);

	// Uiの終了処理
	UiUninit();
}

//=============================================================================
// アイテムの効果を戻す
//=============================================================================
void CItemRedWing::UndoItem(void)
{
	// プレイヤー分回す
	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// 使ったプレイヤー以外
		if (nCount != GetPlayerNum())
		{
			// アイテムを持っているプレイヤーを参照
			CPlayer *pPlayer = CGame::GetPlayer(nCount);

			if (m_bValid[nCount] == true)
			{
				// !nullcheck
				if (pPlayer != nullptr)
				{
					// スピードを上昇
					pPlayer->SetSpeed(pPlayer->GetBaseSpeed());

					// アイテムの有効フラグ
					m_bValid[nCount] = false;
				}
			}
		}
	}

	// 終了フラグを立てる
	SetEnd(true);
}