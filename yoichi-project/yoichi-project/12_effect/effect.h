#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//=====================================================
//
// パーティクルヘッダー [particle.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"
#include "effect_factory.h"

//=====================================================
// マクロ定義
//=====================================================

//=====================================================
// 前方宣言
//=====================================================
CEffectFactory;

//=====================================================
// パーティクルクラス
//=====================================================
class CEffect : public CBillboard
{
public:
	CEffect(PRIORITY Priority = PRIORITY_PARTICLE);		// コンストラクタ
	~CEffect();											// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CEffect*Create(D3DXVECTOR3 pos,				// インスタンス生成
		CEffectFactory::EFFECT Particle,
		 int nTexInfo);

private:
};

#endif