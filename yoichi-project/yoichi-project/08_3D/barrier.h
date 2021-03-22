#ifndef _BARRIER_H_
#define _BARRIER_H_
//=============================================================================
//
// バリアクラスヘッダー [barrier.h]
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
#define BARRIER_MAX_SIZE_X	(500.0f)	// Xのサイズの最大値
#define BARRIER_MAX_SIZE_Y	(500.0f)	// Yのサイズの最大値
#define BARRIER_MAX_SIZE_Z	(500.0f)	// Zのサイズの最大値
#define BARRIER_MAX_SIZE	(D3DXVECTOR3(BARRIER_MAX_SIZE_X, BARRIER_MAX_SIZE_Y, BARRIER_MAX_SIZE_Z))	// サイズの最大値
#define BARRIER_LIFE		(300)	// ライフ

//=============================================================================
// 背景クラス
//=============================================================================
class CBARRIER : public CModel
{
public:
	CBARRIER();		// コンストラクタ
	~CBARRIER();	// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

	static CBARRIER *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum);	// インスタンス生成

private:
	D3DXVECTOR3 m_RotQuantity;	// 回転量
	D3DXVECTOR3 m_Scale;		// 拡大率
	int m_nPlayerNum;			// プレイヤーの番号
};

#endif
