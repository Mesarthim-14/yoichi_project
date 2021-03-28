//=====================================================
//
// パーティクルクラス [particle.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "particle.h"
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
CEffect::CEffect(PRIORITY Priority) : CBillboard(Priority)
{
	
}

//=====================================================
// デストラクタ
//=====================================================
CEffect::~CEffect()
{

}

//=====================================================
// インスタンス生成
//=====================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, CEffectFactory::EFFECT Particle,
	 int nTexInfo)
{
	// メモリ確保
	CEffect *pEffect = new CEffect;

	if (pEffect != NULL)
	{
		// 距離の設定
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x),
			(float)(rand() % (int)Particle.Distance.y + rand() % (int)Particle.Distance.y),
			(float)(rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z));

		// ランダムで出現を決める
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y,
			pos.z + Distance.z);

		pEffect->SetPos(TargetPos);
		pEffect->SetSize(Particle.size);
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
			pEffect->BindTexture(pTexture->GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
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
		pEffect->SetAlphaNum(Particle.nAlphaNum);	// アルファの値の設定
		pEffect->SetBlend(Particle.bBlend);			// 加算合成の設定
	}

	return pEffect;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEffect::Init(void)
{
	// 初期化処理
	CBillboard::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CEffect::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CEffect::Update(void)
{
	// 更新処理
	CBillboard::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CEffect::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}