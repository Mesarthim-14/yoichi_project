//=====================================================
//
// 3Dエフェクトクラス [effect_3d.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "effect_3d.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"

//=====================================================
// マクロ定義
//=====================================================
#define DEFAULT_POS_Y		(200.0f)		// 世界の高さの標準

//=====================================================
// コンストラクタ
//=====================================================
CEffect3D::CEffect3D(PRIORITY Priority) : CScene3D(Priority)
{
	m_nLife = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CEffect3D::~CEffect3D()
{

}

//=====================================================
// インスタンス生成
//=====================================================
CEffect3D * CEffect3D::Create(D3DXVECTOR3 pos, CEffectFactory::EFFECT Particle,
	int nTexInfo)
{
	// メモリ確保
	CEffect3D *pEffect = new CEffect3D;

	// nullchack
	if (pEffect != NULL)
	{
		// 距離の設定
		D3DXVECTOR3 Range;
		Range = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Range.x + rand() % (int)Particle.Range.x - rand() % (int)Particle.Range.x - rand() % (int)Particle.Range.x),
			(float)(rand() % (int)Particle.Range.y + rand() % (int)Particle.Range.y),
			(float)(rand() % (int)Particle.Range.z + rand() % (int)Particle.Range.z - rand() % (int)Particle.Range.z - rand() % (int)Particle.Range.z));

		// ランダムで出現を決める
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Range.x,
			pos.y + Range.y,
			pos.z + Range.z);

		// 初期化処理
		pEffect->Init();

		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// アニメーション情報
		if (Particle.bAnimation == false)
		{
			// テクスチャ設定
			pEffect->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));
		}
		else
		{
			// アニメーションテクスチャ設定
			pEffect->BindTexture(pTexture-> GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));

			// アニメーション情報設定
			pEffect->InitAnimation(
				pTexture->GetSparateTexInfo((CTexture::SEPARATE_TEX_TYPE)nTexInfo),
				pTexture->GetSparateTexLoop((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
		}

		// 移動量が一定以上なら
		if (Particle.move.x >= 1.0f &&
			Particle.move.y >= 1.0f &&
			Particle.move.z >= 1.0f)
		{
			// 移動量設定
			D3DXVECTOR3 move;
			switch (Particle.bGravity)
			{
				// 重力無し
			case false:
				// 移動量
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;

				// 重力あり
			case true:
				// 移動量
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;
			}

			// 移動量
			pEffect->SetMove(move);
		}
		else
		{
			// 移動量
			pEffect->SetMove(Particle.move);
		}

		pEffect->SetColor(Particle.color);			// 色の設定
		pEffect->SetLife(Particle.nLife);			// 体力の設定
		pEffect->SetAlpha(Particle.bAlpha);			// アルファテストの設定
		pEffect->SetAlphaNum(Particle.nAlphaNum);	// アルファテストの値を設定
		pEffect->SetBlend(Particle.bBlend);			// 加算合成の設定
	}

	return pEffect;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEffect3D::Init(void)
{
	// 初期化処理
	CScene3D::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEffect3D::Uninit(void)
{
	// 終了処理
	CScene3D::Uninit();

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CEffect3D::Update(void)
{
	// 寿命の減算
	m_nLife--;

	// 更新処理
	CScene3D::Update();

	// ライフの設定
	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CEffect3D::Draw(void)
{
	// 描画処理
	CScene3D::Draw();
}

//=====================================================
// ライフの設定
//=====================================================
void CEffect3D::SetLife(int nLife)
{
	m_nLife = nLife;
}