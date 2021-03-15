#ifndef _ITEM_REDWING_H_
#define _ITEM_REDWING_H_
//=============================================================================
//
// アイテム赤い羽根クラスヘッダー	[item_redwing.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// アイテム赤い羽根クラス
//=============================================================================
class CItemRedWing : public CItem
{
public:
	CItemRedWing(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemRedWing();									// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Update(void);		// 更新処理

	void SetItem(void);									// アイテムの効果設定
	void UndoItem(void);								// アイテムの効果を戻す
	static CItemRedWing *Create(const int nNumber);		// インスタンス生成

private:
	int m_nCounter;					// フレームカウンター
	bool m_bValid[MAX_PLAYER_NUM];	// アイテムの効果有効フラグ
};

#endif