//=============================================================================
//
// アイテム雷クラス [item_thunder.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_thunder.h"
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
#define THUNDER_SPEED_NUM	(0)			// 速度の情報
#define THUNDER_TIME		(180)		// 速度アップのカウント

//=============================================================================
// コンストラクタ
//=============================================================================
CItemThunder::CItemThunder(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	memset(m_bValid, false, sizeof(m_bValid));
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemThunder::~CItemThunder()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CItemThunder * CItemThunder::Create(const int nNumber)
{
	// メモリ確保
	CItemThunder *pItemThunder = new CItemThunder;

	// !nullcheck
	if (pItemThunder  != nullptr)
	{
		// 初期化処理
		pItemThunder->SetNumber(nNumber);
		pItemThunder->Init();
	}

	return pItemThunder;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemThunder::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_THUNDER));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemThunder::Update(void)
{
	// アイテムの更新処理
	CItem::Update();

	// アイテムが使われたら
	if (GetUse() == true)
	{
		// フレームカウンターを進める
		m_nCounter++;

		// カウンターが一定量で
		if (m_nCounter >= THUNDER_TIME)
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
void CItemThunder::SetItem(void)
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
				if (pPlayer->GetArmor() == false)
				{
					// 相手の速度を無くす
					pPlayer->SetSpeed(THUNDER_SPEED_NUM);

					CModelAnime* pModelAnime = pPlayer->GetModelAnime(21);
					D3DXVECTOR3 Rot = pPlayer->GetRot();
					D3DXVECTOR3 EffectCenter = D3DXVECTOR3(pModelAnime->GetMtxWorld()._41,
						pModelAnime->GetMtxWorld()._42,
						pModelAnime->GetMtxWorld()._43);
					CEffectFactory::CreateEffect(EffectCenter, CEffectFactory::EFFECT_TYPE::EFFECT_NUM_THUNDER);

					CEffectFactory::CreateEffect(EffectCenter + D3DXVECTOR3(0.0f, 500.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_LIGHTNINGSTRIKE);

					// アイテムの有効フラグ
					m_bValid[nCount] = true;

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
void CItemThunder::UndoItem(void)
{
	// プレイヤー分回す
	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// 使ったプレイヤー以外
		if (nCount != GetPlayerNum())
		{
			if (m_bValid[nCount])
			{
				// アイテムを持っているプレイヤーを参照
				CPlayer *pPlayer = CGame::GetPlayer(nCount);

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
