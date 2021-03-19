//=====================================================
//
// パーティクルクラス [particle.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "effect.h"
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
			(float)(rand() % (int)Particle.Range.x - ((int)Particle.Range.x / 2)),
			(float)(rand() % (int)Particle.Range.y - ((int)Particle.Range.y / 2)),
			(float)(rand() % (int)Particle.Range.z - ((int)Particle.Range.z / 2)));

		// ランダムで出現を決める
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y,
			pos.z + Distance.z);

		// 初期化処理
		pEffect->Init(TargetPos, Particle.size);

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
		if (Particle.move.x >= 1.0f || Particle.move.x <= -1.0f &&
			Particle.move.y >= 1.0f || Particle.move.y <= -1.0f &&
			Particle.move.z >= 1.0f || Particle.move.z <= -1.0f)
		{
			// 移動量設定
			D3DXVECTOR3 move;
			switch (Particle.movetype)
			{
				// 完全ランダム
			case CEffectFactory::MOVE_TYPE_ALLRANDOM:
				switch (Particle.bGravity)
				{
					// 重力無し
				case false:
					// 移動量
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							(float)(rand() % (int)Particle.move.y - ((int)Particle.move.y / 2)),
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;

					// 重力あり
				case true:
					// 移動量
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;
				}
				break;

				// 縦と横のランダム
			case CEffectFactory::MOVE_TYPE_XZRANDOM:
				switch (Particle.bGravity)
				{
					// 重力無し
				case false:
					// 移動量
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							Particle.move.y,
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;

					// 重力あり
				case true:
					// 移動量
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							Particle.move.y,
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;
				}
				break;

			default:
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

		pEffect->SetRot(D3DXToRadian(Particle.rot));		// 回転の設定
		pEffect->SetColor(Particle.color);					// 色の設定
		pEffect->SetLife(Particle.nLife);					// 体力の設定
		pEffect->SetAlpha(Particle.bAlpha);					// アルファテストの設定
		pEffect->SetAlphaNum(Particle.nAlphaNum);			// アルファの値の設定
		pEffect->SetBlend(Particle.bBlend);					// 加算合成の設定
		pEffect->SetGravity(Particle.GravityNum);			// 重力の設定
		pEffect->SetTransparency(Particle.fTransparency);	// 透明度を減らす量の設定
		pEffect->SetScale(Particle.Scale);					// 拡大率の設定
		pEffect->SetUseZBuf(Particle.bUseZbuf);				// Zバッファの設定
	}

	return pEffect;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

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