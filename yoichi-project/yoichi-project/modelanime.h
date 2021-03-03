//=============================================================================
//
// 階層構造用のモデル処理 [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================
#ifndef _MODELANIME_H_
#define _MODELANIME_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_MODEL_TEXTURE		(256)		// テクスチャの最大数
#define MAX_OLD_MTX_WORLD		(5)			// ワールドマトリクスの配列

//=============================================================================
//階層モデルクラス
//=============================================================================
class CModelAnime
{
public:
	//=========================================================================
	//モデル情報音構造体
	//=========================================================================
	typedef struct
	{
		LPD3DXMESH pMesh;			//メッシュ情報へのポインタ
		LPD3DXBUFFER pBuffMat;		//マテリアル情報へのポインタ
		DWORD dwNumMat;				//マテリアル情報の数
	}MODEL;

	CModelAnime();		// コンストラクタ
	~CModelAnime();		// デストラクタ

	static CModelAnime *Create(char *xfilename,							// インスタンス生成
		D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
	void SetParent(CModelAnime *pParent);								// 親の設定
	void SetPosAnime(const D3DXVECTOR3 posAnime);						// アニメーションパーツの座標
	void SetRotAnime(const D3DXVECTOR3 rotAnime);

	// Get情報
	D3DXVECTOR3 GetPos(void)const;			// 座標情報
	D3DXVECTOR3 GetPosAnime(void)const;		// アニメーション座標情報
	D3DXVECTOR3 GetRot(void)const;			// 角度の情報
	D3DXVECTOR3 GetRotAnime(void)const;		// アニメーション角度情報
	D3DXMATRIX GetMtxWorld(void);			// ワールドマトリクス情報
	D3DXMATRIX GetOldMtxWorld(void);		// 古いワールドマトリクスの情報

private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_MODEL_TEXTURE];		// テクスチャのポインタ
	MODEL m_model;											// モデル情報
	D3DXVECTOR3 m_pos;										// 位置
	D3DXVECTOR3 m_rot;										// 向き
	D3DXVECTOR3 m_posAnime;									// アニメーション用の位置
	D3DXVECTOR3 m_rotAnime;									// アニメーション用の向き
	D3DXMATRIX m_mtxWorld;									// ワールドマトリックス
	CModelAnime *m_pParent;									// 親情報のポインタ
	D3DXMATRIX m_OldMtxWorld;								// 古いワールド座標
	D3DXMATRIX m_OldMtxWorld1[MAX_OLD_MTX_WORLD];
};

#endif 