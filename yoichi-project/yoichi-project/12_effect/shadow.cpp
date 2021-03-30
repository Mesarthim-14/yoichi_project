//=====================================================
//
// シャドウクラス [shadow.cpp]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "stage_map.h"
#include "mesh_pillar.h"
#include "meshfield.h"

//=====================================================
// マクロ定義
//=====================================================
#define DEFAULT_SIZE		(D3DXVECTOR3(150.0f, 150.0f, 0.0f))				// 基本の大きさ
#define DEFAULT_ROT			(D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f))	// 基本の角度
#define DEFAULT_COLOR		(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))				// 基本の色
#define DEFAULT_POS_Y		(-2000.0f)										// 基本の座標
#define PILLAR_POS_Y		(0.0f)											// 柱の座標
#define DIVIDE_NUM			(2000.0f)										// 距離を割る数

//=====================================================
// コンストラクタ
//=====================================================
CShadow::CShadow(PRIORITY Priority) : CBillboard(Priority)
{
	m_nPlayerNum = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CShadow::~CShadow()
{

}

//=====================================================
// インスタンス生成
//=====================================================
CShadow * CShadow::Create(int nTexInfo, int nPlayerNum)
{
	// メモリ確保
	CShadow *pEffect = new CShadow;

	if (pEffect != NULL)
	{
		CTexture *pTexture = GET_TEXTURE_PTR;

		// アニメーションテクスチャ設定
		pEffect->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));

		pEffect->SetSize(DEFAULT_SIZE);
		pEffect->SetRot(DEFAULT_ROT);
		pEffect->SetColor(DEFAULT_COLOR);
		pEffect->SetAlpha(true);			// アルファテストの設定
		pEffect->m_nPlayerNum = nPlayerNum; // 追従させるプレイヤーの番号

		// 初期化処理
		pEffect->Init();

	}

	return pEffect;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CShadow::Init()
{
	// 初期化処理
	CBillboard::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CShadow::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CShadow::Update(void)
{
	// 更新処理
	CBillboard::Update();

	// 座標の更新
	D3DXVECTOR3 pos = CGame::GetPlayer(m_nPlayerNum)->GetPos();

	// ポインタ情報取得
	CStageMap *pStageMap = CManager::GetGame()->GetStageMap();

	// !nullcheck
	if (pStageMap != nullptr)
	{
		// ローカル変数宣言
		int mMeshPillarNum = pStageMap->GetMeshPillarNum();		// 柱の数

		for (int nCount = 0; nCount < mMeshPillarNum; nCount++)
		{
			// 柱の情報
			CMeshPillar *pMeshPiller = pStageMap->GetMeshPillar(nCount);

			// !nullcheck
			if (pMeshPiller != nullptr)
			{
				D3DXVECTOR3 PillerPos = pMeshPiller->GetPos() * 2;	// 柱の座標
				float fRadius = pMeshPiller->GetSize().x;

				// プレイヤーの情報取得
				D3DXVECTOR3 PlayerPos = CGame::GetPlayer(m_nPlayerNum)->GetPos();		// 座標取得
				float fPlayerRadius = CGame::GetPlayer(m_nPlayerNum)->GetRadius();		// 半径

				// 二点の距離、二点の角度設定
				float fLength = sqrtf(
					powf((PlayerPos.x - PillerPos.x), 2) +
					powf((PlayerPos.z - PillerPos.z), 2));

				// 離す距離
				float fDistance = fRadius;

				// 当たり判定
				if (fLength <= fDistance)
				{
					pos.y = PILLAR_POS_Y + 0.1f;
					break;
				}
				else
				{
					pos.y = DEFAULT_POS_Y + 0.1f;
				}
			}
		}
	}
	SetPos(pos);

	// 色の更新
	D3DXCOLOR col = GetColor();
	float fAlphaSub = (CGame::GetPlayer(m_nPlayerNum)->GetPos().y - pos.y) / DIVIDE_NUM;
	col.a = 1.0f - fAlphaSub;
	SetColor(col);
}

//=====================================================
// 描画処理
//=====================================================
void CShadow::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}