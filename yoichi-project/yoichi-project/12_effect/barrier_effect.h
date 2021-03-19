#ifndef _BARRIEREFFECT_H_
#define _BARRIEREFFECT_H_
//=============================================================================
//
// バリアエフェクトクラスヘッダー [barrier_effect.h]
// Author : Ito Yogo
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "model.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define BARRIEREFFECT_MAX_SIZE_X	(300.0f)	// Xのサイズの最大値
#define BARRIEREFFECT_MAX_SIZE_Y	(300.0f)	// Yのサイズの最大値
#define BARRIEREFFECT_MAX_SIZE_Z	(300.0f)	// Zのサイズの最大値
#define BARRIEREFFECT_MAX_SIZE		(D3DXVECTOR3(BARRIEREFFECT_MAX_SIZE_X, BARRIEREFFECT_MAX_SIZE_Y, BARRIEREFFECT_MAX_SIZE_Z))	// サイズの最大値
#define BARRIEREFFECT_LIFE			(180)	// ライフ

//=============================================================================
// 背景クラス
//=============================================================================
class CBARRIEREFFECT: public CModel
{
public:
	CBARRIEREFFECT();		// コンストラクタ
	~CBARRIEREFFECT();		// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

	static CBARRIEREFFECT *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fAngle);	// インスタンス生成

private:
	D3DXVECTOR3 m_RotQuantity;	// 回転量
	D3DXVECTOR3 m_Scale;		// 拡大率
};

#endif
