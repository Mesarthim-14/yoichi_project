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
//ライフクラス
//=============================================================================
class CPolygon
{
public:
	//=========================================================================
	//列挙型定義
	//=========================================================================
	typedef enum
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_TITLE,			//タイトルテクスチャ
		TEX_TYPE_RESULET,		//リザルトテクスチャ
		TEX_TYPE_LIFE_GAUGE,	//ライフテクスチャ
		TEX_TYPE_UNDERUI,		//アンダーUIテクスチャ
		TEX_TYPE_CHEETAH,		//チーター
		TEX_TYPE_GORILLA,		//ゴリラ
		TEX_TYPE_TURTLE,		//カメ
		TEX_TYPE_PRESSENTER,	//PRESS ENTERテクスチャ
		TEX_TYPE_MAX,			//最大テクスチャ
	}TEX_TYPE;

	CPolygon();			// コンストラクタ
	~CPolygon();		// デストラクタ

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const TEX_TYPE type);	// インスタンス生成

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const TEX_TYPE type);				// 初期化処理
	void Uninit(void);																				// 終了処理
	void Update(void);																				// 更新処理
	void Draw(void);																				// 描画処理

	void SetType(const TEX_TYPE type);																// テクスチャタイプ
	void SetColor(const D3DXCOLOR color);															// 色の設定

private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXVECTOR3 m_size;					// ポリゴンのサイズ
	D3DXVECTOR3 m_pos;					// ライフの位置
	TEX_TYPE m_Type;					// タイプ
};
#endif 