//=============================================================================
//
// アイテム渦クラス [item_vortex.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_vortex.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "collision.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define VORTEX_TIME			(50)	// 効果の有効カウント
#define VORTEX_RADIUS_UP	(0.1f)	// 半径の拡大率

//=============================================================================
// コンストラクタ
//=============================================================================
CItemVortex::CItemVortex(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	m_fRadiusNum = 1.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemVortex::~CItemVortex()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CItemVortex * CItemVortex::Create(const int nNumber)
{
	// メモリ確保
	CItemVortex *pItemVortex = new CItemVortex;

	// !nullcheck
	if (pItemVortex != nullptr)
	{
		// 初期化処理
		pItemVortex->Init();
		pItemVortex->SetNumber(nNumber);
	}

	return pItemVortex;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemVortex::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_VORTEX));
	}

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemVortex::Update(void)
{
	// アイテムが使われたら
	if (GetUse() == true)
	{
		// フレームカウンターを進める
		m_nCounter++;

		// 半径拡大
		RadiusUp();

		// カウンターが一定量で
		if (m_nCounter >= VORTEX_TIME)
		{
			// アイテムの効果を戻す
			UndoItem();

			m_nCounter = 0;
		}
	}
}

//=============================================================================
// 半径の拡大
//=============================================================================
void CItemVortex::RadiusUp(void)
{
	// 倍率を加算
	m_fRadiusNum += VORTEX_RADIUS_UP;

	// アイテムを持っているプレイヤーを参照
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// 半径
	pPlayer->GetRadius();

	// 座標受け取り
	D3DXVECTOR3 pos = pPlayer->GetPos();
	float fRadius = pPlayer->GetRadius() * m_fRadiusNum;

	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// 自分の番号じゃないとき
		if (GetPlayerNum() != nCount)
		{
			// キャラクターのポインタ
			CPlayer *pTarget = CGame::GetPlayer(nCount);

			// !nullcheck
			if (pTarget != nullptr)
			{
				D3DXVECTOR3 TargetPos = pTarget->GetPos();
				float fTargetRadius = pTarget->GetRadius();

				// 円形と円形の当たり判定
				if (CCollision::CollisionCircularAndCircular(
					pos, TargetPos,
					fRadius, fTargetRadius) == true)
				{
					// 外に押し出す
					D3DXVECTOR3 vec = (TargetPos - pos);
					D3DXVec3Normalize(&vec, &vec);
					vec *= (fTargetRadius + fRadius);

					// 座標設定
					D3DXVECTOR3 pos = TargetPos;
					pTarget->SetPos(pos + vec);
				}
			}
		}
	}
}

//=============================================================================
// アイテムの効果設定
//=============================================================================
void CItemVortex::SetItem(void)
{
	// 使用状態にする
	SetUse(true);

	// Uiの終了処理
	UiUninit();
}

//=============================================================================
// アイテムの効果を戻す
//=============================================================================
void CItemVortex::UndoItem(void)
{
	// 終了フラグを立てる
	SetEnd(true);
}