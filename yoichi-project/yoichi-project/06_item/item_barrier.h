#ifndef _ITEM_BARRIER_H_
#define _ITEM_BARRIER_H_
//=============================================================================
//
// アイテムバリアクラスヘッダー	[item_barrier.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// アイテムバリアクラス
//=============================================================================
class CItemBarrier : public CItem
{
public:
	CItemBarrier(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemBarrier();									// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Update(void);		// 更新処理

	void SetItem(void);									// アイテムの効果設定
	void UndoItem(void);								// アイテムの効果を戻す
	static CItemBarrier *Create(const int nNumber);		// インスタンス生成

private:
	int m_nCounter;			// フレームカウンター
};

#endif