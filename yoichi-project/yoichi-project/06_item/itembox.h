#ifndef _ITEMBOX_H_
#define _ITEMBOX_H_
//=============================================================================
//
// アイテムボックスクラスヘッダー	[itembox.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "model.h"

//=============================================================================
// アイテムボックスクラス
//=============================================================================
class CItemBox : public CModel
{
public:

	enum ITEM_TYPE
	{
		ITEM_TYPE_NONE = -1,	// 初期値
		ITEM_TYPE_BLUE_WING,	// 青い羽根
		ITEM_TYPE_RED_WING,		// 赤い羽根
		ITEM_TYPE_BOMB,			// ボム
		ITEM_TYPE_BARRIER,		// バリア
		ITEM_TYPE_THUNDER,		// サンダー
		ITEM_TYPE_VORTEX,		// 渦
		ITEM_TYPE_MHAND,		// Mハンド
		ITEM_TYPE_MAX			// 最大値
	};

	CItemBox(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemBox();									// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void Collision(void);											// 当たり判定の処理
	void ItemCreate(int nCount);											// アイテムの生成

	static CItemBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// インスタンス生成
private:
	bool m_bDraw;			// 描画のフラグ
	int m_nDrawCount;		// 描画のためのフレームカウンタ
};

#endif