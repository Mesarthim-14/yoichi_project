//=============================================================================
//
// アイテムボックスクラス処理 [itembox.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "itembox.h"
#include "renderer.h"
#include "collision.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "game.h"
#include "player.h"
#include "item_bluewing.h"
#include "item_redwing.h"
#include "item_bomb.h"
#include "item_barrier.h"
#include "item_thunder.h"
#include "item_vortex.h"
#include "item_mhand.h"
#include "item.h"
#include "player_ui.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEMBOX_ROTATION_NUM		(0.01f)																			// 回転の値
#define ITEMBOX_ROTATION_NUM_ALL	(D3DXVECTOR3(ITEMBOX_ROTATION_NUM, ITEMBOX_ROTATION_NUM, ITEMBOX_ROTATION_NUM))	// 回転の値
#define ITEMBOX_RADIUS				(100.0f)																		// 当たり判定の半径
#define ITEMBOX_GENERATE_INTER		(300.0f)																		// 再生成フレーム
#define ITEM_HAVE_NUM				(1)																				// アイテムの所持数

//=============================================================================
// インスタンス生成
//=============================================================================
CItemBox * CItemBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// メモリ確保
	CItemBox *pItemBox = new CItemBox;

	// nullcheck
	if (pItemBox != nullptr)
	{
		// 初期化処理
		pItemBox->Init(pos, size);
	}

	return pItemBox;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CItemBox::CItemBox(PRIORITY Priority) : CModel(Priority)
{
	m_bDraw = true;
	m_nDrawCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBox::~CItemBox()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBox::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CModel::Init(pos, size);

	// Xファイルの情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// モデル情報の設定
	BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_ITEM_BOX));
	BindTexture(pXfile->GetXfileTexture(CXfile::XFILE_NUM_ITEM_BOX));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItemBox::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBox::Update(void)
{
	// 描画中
	if (m_bDraw == true)
	{
		// 回転の処理
		Rotation(ITEMBOX_ROTATION_NUM_ALL);

		// 当たり判定
		Collision();

		// 更新処理
		CModel::Update();
	}
	else
	{
		// 描画のためのカウント
		m_nDrawCount++;

		// 一定量を超えたら
		if (m_nDrawCount >= ITEMBOX_GENERATE_INTER)
		{
			m_bDraw = true;
			m_nDrawCount = 0;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CItemBox::Draw(void)
{
	// 描画のフラグ
	if (m_bDraw == true)
	{
		// Rendererクラスからデバイスを取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ライトの効果を消す処理
	//	pDevice->LightEnable(0, false);

		// 描画処理
		CModel::Draw();

		// ライトの効果を付けなおす
	//	pDevice->LightEnable(0, true);
	}
}

//=============================================================================
// 当たり判定の処理
//=============================================================================
void CItemBox::Collision(void)
{
	// プレイヤーの数
	int nPlayerNum = CGame::GetPlayerNum();

	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		// プレイヤーの関数
		CPlayer *pPlayer = CGame::GetPlayer(nCount);
        CPlayer_UI *pPlayerUI = pPlayer->GetPlayerUI();

		// 当たり判定
		if (CCollision::CollisionCircularAndCircular(
			GetPos(), pPlayer->GetPos(),
			ITEMBOX_RADIUS, pPlayer->GetRadius()) == true)
		{
			// 見えなくする
			m_bDraw = false;

			// アイテムを持っていなかったら
			if (pPlayerUI->GetItemNum() == 0)
			{
				// アイテム生成
				ItemCreate(nCount);
			}
			else if (pPlayerUI->GetItem()->GetUse() == true)
			{// アイテムを持っていたら

				// 二つ以上にならないように
				if (pPlayerUI->GetItemNum() <= ITEM_HAVE_NUM)
				{
					// アイテム生成
					ItemCreate(nCount);
				}
			}
		}
	}
}

//=============================================================================
// アイテムの生成
//=============================================================================
void CItemBox::ItemCreate(int nCount)
{
	// 乱数のナンバー
	int nNumber = rand() % (int)ITEM_TYPE_MAX;

		// プレイヤーの関数
	CPlayer *pPlayer = CGame::GetPlayer(nCount);
    CPlayer_UI *pPlayerUI = pPlayer->GetPlayerUI();
	// ナンバー
	switch ((ITEM_TYPE)nNumber)
	{
	case ITEM_TYPE_BLUE_WING:
        pPlayerUI->AcquiredItem(CItemBlueWing::Create(nCount));
		break;

	case ITEM_TYPE_RED_WING:
		pPlayerUI->AcquiredItem(CItemRedWing::Create(nCount));
		break;

	case ITEM_TYPE_BARRIER:
		pPlayerUI->AcquiredItem(CItemBarrier::Create(nCount));
		break;

	case ITEM_TYPE_BOMB:
		pPlayerUI->AcquiredItem(CItemBomb::Create(nCount));
		break;

	case ITEM_TYPE_THUNDER:
		pPlayerUI->AcquiredItem(CItemThunder::Create(nCount));
		break;

	case ITEM_TYPE_VORTEX:
		pPlayerUI->AcquiredItem(CItemVortex::Create(nCount));
		break;

	case ITEM_TYPE_MHAND:
		pPlayerUI->AcquiredItem(CItemMhand::Create(nCount));
		break;

	default:
		break;
	}
}