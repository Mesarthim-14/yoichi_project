#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// モデル処理 [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_MODEL_TEXTURE	(256)		// テクスチャの最大数

//=============================================================================
// モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
	typedef enum
	{
		MODEL_TYPE_NONE = 0,	// 初期値
		MODEL_TYPE_PLAYER1,		// プレイヤー
		MODEL_TYPE_PLAYER2,		// プレイヤー
		MODEL_TYPE_BEAM,		// ビーム
		MODEL_TYPE_OBJECT,		// 建物
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CModel(PRIORITY Priority = PRIORITY_EFFECT);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// インスタンス生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void BindModel(CXfile::MODEL model);						// モデルの設定
	void BindTexture(LPDIRECT3DTEXTURE9 *pTexture);				// テクスチャの設定
	void SubAlpha(float fAlpha);								// 透明度の減算
	
	// Set関数
	void SetPos(const D3DXVECTOR3 pos);		// 座標の設定
	void SetMove(const D3DXVECTOR3 move);	// 移動量の設定
	void SetRot(const D3DXVECTOR3 rot);		// 座標の情報
	void SetType(MODEL_TYPE Mtype);			// モデルの種類設定
	void SetSize(D3DXVECTOR3 size);			// サイズの設定
	void SetTexPattern(int TexPattern);		// テクスチャのパターン
	void SetLife(int nLife);				// ライフの設定
	void SetColor(D3DXCOLOR color);			// 色の設定
	void SetAlphaNum(float fAlphaNum);		// 透明度の設定

	// Get関数
	D3DXVECTOR3 GetPos(void)const;						// 座標の情報
	D3DXVECTOR3 GetMove(void);							// 移動量の情報
	D3DXVECTOR3 GetSize(void);							// サイズの設定
	D3DXVECTOR3 GetRot(void);							// 角度の設定
	MODEL_TYPE GetType(void);							// 種類の情報
	D3DXCOLOR GetColor(void);							// 色の情報
	D3DXMATRIX GetMtxWorld(void);						// 輪0ルドマトリクス
	LPD3DXMESH GetMesh(void)const;						// メッシュ情報
	LPD3DXBUFFER GetBuffMat(void);						// バッファ情報
	DWORD GetNumMat(void);								// マトリクスの数
	int GetTexPattern(void);							// テクスチャ
	int GetLife(void);									// ライフの設定
	float GetAlphaNum(void) { return m_fAlphaNum; }		// 透明度の値
private:
	LPDIRECT3DTEXTURE9 *m_apTexture;	// テクスチャのポインタ
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_move;					// 移動量
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// サイズ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	MODEL_TYPE m_type;					// 種類
	D3DXCOLOR m_Color;					// 色
	CXfile::MODEL m_Model;				// モデルの構造体
	int m_nTexPattern;					// テクスチャのパターン数
	int m_nLife;						// ライフ
	float m_fAlphaNum;					// 透明度の値
};
#endif 