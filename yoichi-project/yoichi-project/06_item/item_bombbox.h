#ifndef _ITEM_VBOMBBOX_H_
#define _ITEM_VBOMBBOX_H_
//=============================================================================
//
// アイテムボックスクラスヘッダー	[item_bombbox.h]
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
class CItemBombBox : public CModel
{
public:
	CItemBombBox(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemBombBox();									// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	void UndoBox(void);									// ボックス効果の終了

	void Collision(void);								// 当たり判定の処理

	static CItemBombBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber);		// インスタンス生成

private:
	int m_nPlayerNum;	// プレイヤーの番号
	int m_nHitPlayer;	// 当たったプレイヤー
	int m_nCounter;		// フレームカウンター
	bool m_bUse;		// 使用中
};

#endif