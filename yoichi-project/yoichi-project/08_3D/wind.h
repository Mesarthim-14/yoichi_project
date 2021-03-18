#ifndef _WIND_H_
#define _WIND_H_
//=============================================================================
//
// 風クラスヘッダー [wind.h]
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
#define WIND_MAX_SIZE_X		(300.0f)	// Xのサイズの最大値
#define WIND_MAX_SIZE_Y		(300.0f)	// Yのサイズの最大値
#define WIND_MAX_SIZE_Z		(300.0f)	// Zのサイズの最大値
#define WIND_MAX_SIZE		(D3DXVECTOR3(WIND_MAX_SIZE_X, WIND_MAX_SIZE_Y, WIND_MAX_SIZE_Z))	// サイズの最大値

//=============================================================================
// 背景クラス
//=============================================================================
class CWind : public CModel
{
public:
	CWind();		// コンストラクタ
	~CWind();		// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

	static CWind *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum);	// インスタンス生成

private:
	D3DXVECTOR3 m_RotQuantity;	// 回転量
	D3DXVECTOR3 m_Scale;		// 拡大率
};

#endif
