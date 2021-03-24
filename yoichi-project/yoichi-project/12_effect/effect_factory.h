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
	// 動きの種類
	typedef enum
	{
		MOVE_TYPE_NONE = -1,			// 初期値
		MOVE_TYPE_ALLRANDOM,			// 完全ランダム
		MOVE_TYPE_XZRANDOM				// 縦と横のランダム
	}MOVE_TYPE;

	// パーティクルの構造体
	typedef struct
	{
		D3DXVECTOR3 size;		// サイズ
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 rot;		// 角度
		D3DXVECTOR3 Range;		// 範囲
		D3DXVECTOR3 Scale;		// 拡大率
		MOVE_TYPE movetype;		// 動きの種類
		int nLife;				// ライフ
		int nNum;				// 数
		D3DXCOLOR color;		// 色
		bool bGravity;			// 重力をかけるか
		D3DXVECTOR3 GravityNum;	// 重力の値
		float fTransparency;	// 透明度を減らす値
		bool bAlpha;			// アルファテスト
		int nAlphaNum;			// アルファテストの値
		bool bAnimation;		// アニメーションをするかどうか
		bool bBlend;			// 加算合成
		bool bUseZbuf;			// Zバッファ
		int nPriority;			// 描画優先順位
	}EFFECT;

	// テクスチャの番号の列挙型
	typedef enum
	{
		EFFECT_NUM_NONE = -1,			// 初期値
		EFFECT_NUM_PARTICLE,			// ダメージを受けたとき
		EFFECT_NUM_LIGHTNINGSTRIKE,		// 雷のアイテムが使われたとき
		EFFECT_NUM_THUNDER,				// 雷が当たったとき
		EFFECT_NUM_STAR,				// 星
		EFFECT_NUM_SHOCKWAVE,			// 衝撃波
		EFFECT_NUM_WIND,				// 風
		EFFECT_NUM_STATUSUP,			// 状態が良くなったとき
		EFFECT_NUM_STATUSDOWN,			// 状態が悪くなったとき
		EFFECT_NUM_EXPLOSION,			// 爆発
		EFFECT_NUM_EXPLOSIONCIRCLE,		// 爆発の円
		EFFECT_NUM_EXPLOSIONSPARK,		// 爆発の火花
		EFFECT_NUM_SINKER,				// 重り
		EFFECT_NUM_STATESUPPARTICLE,	// 状態が良くなったときの粒子
		EFFECT_NUM_STATUSDOWNPARTICLE,	// 状態が悪くなったときの粒子
		EFFECT_NUM_KIRAKIRA,			// 飛んでいるときのキラキラ
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
