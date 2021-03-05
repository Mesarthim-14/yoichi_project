#ifndef _NUMBER_3D_H_
#define _NUMBER_3D_H_
//=============================================================================
//
// ナンバー3Dクラスヘッダー [number_3d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mesh_3d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DAMAGE_NUM_SIZE_X		(250.0f)	// 横のサイズ
#define DAMAGE_NUM_SIZE_Y		(150.0f)	// 縦のサイズ
#define DAMAGE_NUM_SIZE_Z		(0.0f)		// 奥行のサイズ

#define DAMAGE_NUM_SIZE			(D3DXVECTOR3(DAMAGE_NUM_SIZE_X, DAMAGE_NUM_SIZE_Y, DAMAGE_NUM_SIZE_Z))

//=============================================================================
// ナンバー3Dクラス
//=============================================================================
class CNumber3d : public CMesh3d
{
public:
	CNumber3d(PRIORITY Priority = PRIORITY_EFFECT);							// コンストラクタ
	virtual ~CNumber3d();													// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理
	void Gravity(void);														// 重力

	static CNumber3d *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum);	// インスタンス生成

	// Set関数
	void SetInverse(bool bInverse) { m_bInverse = bInverse; }				// 逆行列の設定
	void BindMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }		// マトリクス情報
	void RandSetMove(void);													// 移動量の設定

	// Get関数
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }						// ワールドマトリックス

private:
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	bool m_bInverse;			// 逆行列
	int m_nNumber;				// ナンバーの値
	int m_nLife;				// 体力
	int m_nBoundCounter;		// バウンドカウント
	D3DXVECTOR3 m_move;			// 移動
};

#endif