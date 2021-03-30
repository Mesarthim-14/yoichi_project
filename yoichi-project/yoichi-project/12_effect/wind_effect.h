#ifndef _WIND_EFFECT_H_
#define _WIND_EFFECT_H_
//=====================================================
//
// マジックハンドクラスヘッダー [magichand.h]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"

//=====================================================
// マクロ定義
//=====================================================
#define MAGICHAND_DISTANCE	(D3DXVECTOR3(150.0f ,0.0f, 0.0f))	// プレイヤーとの距離

//=====================================================
// パーティクルクラス
//=====================================================
class CWindEffect : public CBillboard
{
public:
	CWindEffect(PRIORITY Priority = PRIORITY_PARTICLE);		// コンストラクタ
	~CWindEffect();											// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CWindEffect*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Distance, int nTexInfo);	// インスタンス生成

private:
};

#endif