#ifndef _ITEM_MHAND_H_
#define _ITEM_MHAND_H_
//=============================================================================
//
// アイテムMハンドクラスヘッダー	[item_mhand.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// アイテム青い羽根クラス
//=============================================================================
class CItemMhand : public CItem
{
public:
	CItemMhand(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemMhand();									// デストラクタ

	HRESULT Init(void);								// 初期化処理
	void Update(void);								// 更新処理

	void SetItem(void);									// アイテムの効果設定
	void UndoItem(void);								// アイテムの効果を戻す

	static CItemMhand *Create(const int nNumber);		// インスタンス生成

private:
	int m_nCounter;			// フレームカウンター
	float m_fPlayerRadius;	// プレイヤーの半径保持
};

#endif