#ifndef _EFFECT_FACTORY_H_
#define _EFFECT_FACTORY_H_
//=============================================================================
//
// パーティクル生成クラスヘッダー [effect_factory.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// エフェクト生成
//=============================================================================
class CEffectFactory
{
public:
	// パーティクルの構造体
	typedef struct
	{
		D3DXVECTOR3 size;		// サイズ
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 Distance;	// 距離
		int nLife;				// ライフ
		int nNum;				// 数
		D3DXCOLOR color;		// 色
		bool bGravity;			// 重力
		bool bAlpha;			// アルファテスト
		int nAlphaNum;			// アルファテストの値
		bool bAnimation;		// アニメーションをするかどうか
		bool bBlend;			// 加算合成
		int nPriority;			// 描画優先順位
	}EFFECT;

	// テクスチャの番号の列挙型
	typedef enum
	{
		EFFECT_NUM_NONE = -1,			// 初期値
		EFFECT_NUM_EXPLOSION,			// ダメージを受けたとき
		EFFECT_NUM_MAX
	}EFFECT_TYPE;

	CEffectFactory();												// コンストラクタ
	~CEffectFactory();												// デストラクタ

	static HRESULT ReadFile(void);									// ファイルの読み込み
	static void CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type);	// パーティクルのクラス
private:
	static EFFECT m_Effect[EFFECT_NUM_MAX];							// パーティクル
};
#endif
