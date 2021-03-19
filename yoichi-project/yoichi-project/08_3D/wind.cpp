//=================================================================================
//
// 風クラスヘッダー [wind.cpp]
// Author : Ito Yogo
//
//=================================================================================

//=================================================================================
// インクルード
//=================================================================================
#include "wind.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "xfile.h"
#include "resource_manager.h"

//=================================================================================
// インスタンス生成
//=================================================================================
CWind * CWind::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum)
{
	// メモリ確保
	CWind *pWind = new CWind;

	// !nullcheck
	if (pWind != NULL)
	{
		// 回転量が一定以上なら
		if (fAngle >= 1.0f || fAngle <= -1.0f)
		{
			// 回転量
			pWind->m_RotQuantity =
				D3DXVECTOR3(D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))));
		}

		pWind->m_Scale = scale;	// 拡大率

		// 初期化処理
		pWind->Init(pos, size);
	}

	return pWind;
}

//=================================================================================
// コンストラクタ
//=================================================================================
CWind::CWind()
{
	m_RotQuantity = ZeroVector3;	// 回転量の初期化
	m_Scale = ZeroVector3;			// 拡大率の初期化
}

//=================================================================================
// デストラクタ
//=================================================================================
CWind::~CWind()
{
}

//=================================================================================
// 初期化処理
//=================================================================================
HRESULT CWind::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Xファイルのポインタ
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	//モデル情報を設定
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_WINDSPHERE));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_WINDSPHERE));

	// 初期化処理
	CModel::Init(pos, size);

	// 体力設定
	CModel::SetLife(WIND_LIFE);
	return S_OK;
}

//=================================================================================
// 終了処理
//=================================================================================
void CWind::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=================================================================================
// 更新処理
//=================================================================================
void CWind::Update(void)
{
	// 更新処理
	CModel::Update();

	// サイズの更新
	D3DXVECTOR3 size = CModel::GetSize();
	size += m_Scale;
	CModel::SetSize(size);

	// 回転の更新
	D3DXVECTOR3 rot = CModel::GetRot();
	rot += m_RotQuantity;
	CModel::SetRot(rot);
}

//=================================================================================
// 描画処理
//=================================================================================
void CWind::Draw(void)
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

		CModel::SubAlpha(0.00001f);

		// 描画処理
		CModel::Draw();

		// ライトの効果を付けなおす
		pDevice->LightEnable(0, true);
	}
}