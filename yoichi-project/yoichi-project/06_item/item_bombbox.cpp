//=============================================================================
//
// アイテムボックスクラス処理 [itembombbox.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_bombbox.h"
#include "renderer.h"
#include "collision.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "game.h"
#include "player.h"
#include "item_bluewing.h"
#include "item_vortex.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BOMBBOX_RADIUS				(100.0f)		// 当たり判定の半径
#define BOMBBOX_ROTATION_NUM		(0.01f)			// 回転の値
#define BOMBBOX_ROTATION_NUM_ALL	(D3DXVECTOR3(BOMBBOX_ROTATION_NUM, BOMBBOX_ROTATION_NUM, BOMBBOX_ROTATION_NUM))	// 回転の値
#define BOMB_SPEED_NUM				(0)				// 速度の情報
#define BOMB_TIME					(120)			// 速度DOWNのカウント

//=============================================================================
// インスタンス生成
//=============================================================================
CItemBombBox * CItemBombBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPlayerNum)
{
	// メモリ確保
	CItemBombBox *pItemBombBox = new CItemBombBox;

	// nullcheck
	if (pItemBombBox != nullptr)
	{
		pItemBombBox->SetPos(pos);
		pItemBombBox->SetSize(size);
		// 初期化処理
		pItemBombBox->Init();

		// プレイヤーの番号
		pItemBombBox->m_nPlayerNum = nPlayerNum;
	}

	return pItemBombBox;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CItemBombBox::CItemBombBox(PRIORITY Priority) : CModel(Priority)
{
	m_nPlayerNum = 0;
	m_nCounter = 0;
	m_nHitPlayer = 0;
	m_bUse = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBombBox::~CItemBombBox()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItemBombBox::Init(void)
{
	// 初期化処理
	CModel::Init();

	// Xファイルの情報取得
	CXfile *pXfile = GET_XFILE_PTR;

	// モデル情報の設定
	BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_BOMB_BOX));
	BindTexture(pXfile->GetXfileTexture(CXfile::XFILE_NUM_BOMB_BOX));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItemBombBox::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBombBox::Update(void)
{
	// 回転の処理
	Rotation(BOMBBOX_ROTATION_NUM_ALL);

	// 更新処理
	CModel::Update();

	 // 当たり判定
	Collision();

	// 使用中だったら
	if (m_bUse == true)
	{
		m_nCounter++;

		// 時間だった
		if (m_nCounter >= BOMB_TIME)
		{
			// 終了フラグ
			UndoBox();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CItemBombBox::Draw(void)
{
	if (m_bUse == false)
	{
		// 描画処理
		CModel::Draw();

	}
}

//=============================================================================
// ボックスの効果の終了
//=============================================================================
void CItemBombBox::UndoBox(void)
{
	// アイテムを持っているプレイヤーを参照
	CPlayer *pPlayer = CGame::GetPlayer(m_nHitPlayer);

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// スピードを上昇
		pPlayer->SetSpeed(pPlayer->GetBaseSpeed());
	}

	// 終了処理
	Uninit();
}

//=============================================================================
// 当たり判定の処理
//=============================================================================
void CItemBombBox::Collision(void)
{
	// プレイヤーの数
	int nPlayerNum = CGame::GetPlayerNum();

	// プレイヤー分回る
	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		if (m_nPlayerNum != nCount)
		{
			// プレイヤーの関数
			CPlayer *pPlayer = CGame::GetPlayer(nCount);

			// 当たり判定
			if (CCollision::CollisionCircularAndCircular(
				GetPos(), pPlayer->GetPos(),
				BOMBBOX_RADIUS, pPlayer->GetRadius()) == true)
			{
				// !nullcheck
				if (pPlayer != nullptr)
				{
					// Armorが付いていなかったら
					if (pPlayer->GetArmor() == false)
					{
						// 当たったプレイヤーの番号
						m_nHitPlayer = nCount;

						// 相手の速度を無くす
						pPlayer->SetSpeed(BOMB_SPEED_NUM);

						// Armorが無ければ
						pPlayer->SetArmor(true);

						// 飛ぶときの処理
						pPlayer->SetFly(false);
						pPlayer->SetUseGravity(true);

						// 使用中
						m_bUse = true;
					}
				}
			}
		}
	}
}