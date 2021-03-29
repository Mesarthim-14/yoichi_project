//=================================================================================
//
// バリアエフェクトクラスヘッダー [barrier_effect.cpp]
// Author : Ito Yogo
//
//=================================================================================

//=================================================================================
// インクルード
//=================================================================================
#include "barrier_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "xfile.h"
#include "resource_manager.h"

//=================================================================================
// インスタンス生成
//=================================================================================
CBarriereffect * CBarriereffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fAngle)
{
	// メモリ確保
	CBarriereffect *pBarriereffect = new CBarriereffect;

	// !nullcheck
	if (pBarriereffect != NULL)
	{
		// 移動量が一定以上なら
		if (move.x >= 1.0f || move.x <= -1.0f &&
			move.y >= 1.0f || move.y <= -1.0f &&
			move.z >= 1.0f || move.z <= -1.0f)
		{
			// 移動量
			move = D3DXVECTOR3((float)(rand() % (int)move.x - ((int)move.x / 2)),
				(float)(rand() % (int)move.y - ((int)move.y / 2)),
				(float)(rand() % (int)move.z - ((int)move.z / 2)));
		}

		// 回転量が一定以上なら
		if (fAngle >= 1.0f || fAngle <= -1.0f)
		{
			// 回転量
			pBarriereffect->m_RotQuantity =
				D3DXVECTOR3(D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))));
		}

		// 初期化処理
		pBarriereffect->Init(pos, size, move);
	}

	return pBarriereffect;
}

//=================================================================================
// コンストラクタ
//=================================================================================
CBarriereffect::CBarriereffect()
{
	m_RotQuantity = ZeroVector3;	// 回転量の初期化
	m_Scale = ZeroVector3;			// 拡大率の初期化
}

//=================================================================================
// デストラクタ
//=================================================================================
CBarriereffect::~CBarriereffect()
{
}

//=================================================================================
// 初期化処理
//=================================================================================
HRESULT CBarriereffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	// Xファイルのポインタ
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	//モデル情報を設定
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_BARRIER_EFFECT));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_BARRIER_EFFECT));

	// 初期化処理
	CModel::Init();

	// 座標情報を与える
	CModel::SetPos(pos);
	CModel::SetMove(move);

	// 体力設定
	CModel::SetLife(BARRIEREFFECT_LIFE);
	return S_OK;
}

//=================================================================================
// 終了処理
//=================================================================================
void CBarriereffect::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=================================================================================
// 更新処理
//=================================================================================
void CBarriereffect::Update(void)
{
	// 更新処理
	CModel::Update();

	// 回転の更新
	D3DXVECTOR3 rot = CModel::GetRot();
	rot += m_RotQuantity;
	CModel::SetRot(rot);
}

//=================================================================================
// 描画処理
//=================================================================================
void CBarriereffect::Draw(void)
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