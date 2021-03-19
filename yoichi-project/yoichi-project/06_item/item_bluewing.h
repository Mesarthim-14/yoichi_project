#ifndef _ITEM_BLUEWING_H_
#define _ITEM_BLUEWING_H_
//=============================================================================
//
// アイテム青い羽根クラスヘッダー	[item_bluewing.h]
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
class CItemBlueWing : public CItem
{
public:
	CItemBlueWing(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemBlueWing();									// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Update(void);		// 更新処理

	void SetItem(void);									// アイテムの効果設定
	void UndoItem(void);								// アイテムの効果を戻す
	static CItemBlueWing *Create(const int nNumber);	// インスタンス生成

private:
	int m_nCounter;			// フレームカウンター
};

#endif