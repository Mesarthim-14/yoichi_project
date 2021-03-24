//=================================================================================
//
// バリアエフェクトクラスヘッダー [barrier_effect.cpp]
// Author : Ito Yogo
//
//=================================================================================

//=================================================================================
// インクルード
//=================================================================================
#include "barrier.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "xfile.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"

//=================================================================================
// インスタンス生成
//=================================================================================
CBARRIER * CBARRIER::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum)
{
	// メモリ確保
	CBARRIER *pBarriereffect = new CBARRIER;

	// !nullcheck
	if (pBarriereffect != NULL)
	{
		pBarriereffect->m_RotQuantity.y = fAngle;	// 回転量
		pBarriereffect->m_Scale = scale;			// 拡大率
		pBarriereffect->m_nPlayerNum = nPlayerNum;	// プレイヤーの番号

		// 初期化処理
		pBarriereffect->Init(pos, size);
	}

	return pBarriereffect;
}

//=================================================================================
// コンストラクタ
//=================================================================================
CBARRIER::CBARRIER()
{
	m_RotQuantity = ZeroVector3;	// 回転量の初期化
	m_Scale = ZeroVector3;			// 拡大率の初期化
	m_nPlayerNum = 0;				// プレイヤーの番号の初期化
}

//=================================================================================
// デストラクタ
//=================================================================================
CBARRIER::~CBARRIER()
{
}

//=================================================================================
// 初期化処理
//=================================================================================
HRESULT CBARRIER::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Xファイルのポインタ
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	//モデル情報を設定
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_BARRIER));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_BARRIER));

	// 初期化処理
	CModel::Init();

	// 体力設定
	CModel::SetLife(BARRIER_LIFE);
	return S_OK;
}

//=================================================================================
// 終了処理
//=================================================================================
void CBARRIER::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=================================================================================
// 更新処理
//=================================================================================
void CBARRIER::Update(void)
{
	// 更新処理
	CModel::Update();

	// 座標の更新
	D3DXVECTOR3 pos = CModel::GetPos();
	pos = CGame::GetPlayer(m_nPlayerNum)->GetPos();
	CModel::SetPos(pos);

	// サイズの更新
	D3DXVECTOR3 size = CModel::GetSize();
	size += m_Scale;
	if (size.x >= BARRIER_MAX_SIZE.x)
	{
		size = BARRIER_MAX_SIZE;
	}
	else
	{
		// 回転の更新
		D3DXVECTOR3 rot = CModel::GetRot();
		rot += m_RotQuantity;
		CModel::SetRot(rot);
	}
	CModel::SetSize(size);
}

//=================================================================================
// 描画処理
//=================================================================================
void CBARRIER::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL*pMat;		//マテリアルデータへのポインタ

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// ライトの効果を消す処理
		pDevice->LightEnable(0, false);

		// 描画処理
		CModel::Draw();

		// ライトの効果を付けなおす
		pDevice->LightEnable(0, true);
	}
}