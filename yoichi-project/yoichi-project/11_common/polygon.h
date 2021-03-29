#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// ポリゴン生成クラス処理 [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//ポリゴンクラス
//=============================================================================
class CPolygon
{
public:

	CPolygon();			// コンストラクタ
	virtual ~CPolygon();		// デストラクタ

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// インスタンス生成

	virtual HRESULT Init(void);				// 初期化処理
	virtual void Uninit(void);															// 終了処理
	virtual void Update(void);															// 更新処理
	virtual void Draw(void);															// 描画処理
	virtual void BindTexture(LPDIRECT3DTEXTURE9 pTexture);								// テクスチャ割当
	virtual void SetColor(const D3DXCOLOR color);										// 色の設定
	
    void UpdateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size);       // 頂点の更新
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	D3DXVECTOR3 m_size;						// ポリゴンのサイズ
	D3DXVECTOR3 m_pos;						// ライフの位置
};
#endif 