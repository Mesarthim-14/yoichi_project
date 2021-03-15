#ifndef _ITEM_THUNDER_H_
#define _ITEM_THUNDER_H_
//=============================================================================
//
// アイテム雷クラスヘッダー	[item_thunder.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// アイテム雷クラス
//=============================================================================
class CItemThunder : public CItem
{
public:
	CItemThunder(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemThunder();									// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Update(void);		// 更新処理

	void SetItem(void);									// アイテムの効果設定
	void UndoItem(void);								// アイテムの効果を戻す
	static CItemThunder *Create(const int nNumber);		// インスタンス生成

private:
	int m_nCounter;					// フレームカウンター
	bool m_bValid[MAX_PLAYER_NUM];	// アイテムの効果有効フラグ
};

#endif