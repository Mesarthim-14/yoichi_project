#ifndef _ITEM_VORTEX_H_
#define _ITEM_VORTEX_H_
//=============================================================================
//
// アイテム渦クラスヘッダー	[item_vortex.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"

//=============================================================================
// アイテム渦クラス
//=============================================================================
class CItemVortex : public CItem
{
public:
	CItemVortex(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CItemVortex();										// デストラクタ

	HRESULT Init(void);		// 初期化処理
	void Update(void);		// 更新処理

	void SetItem(void);									// アイテムの効果設定
	void UndoItem(void);								// アイテムの効果を戻す
	static CItemVortex *Create(const int nNumber);		// インスタンス生成
	void RadiusUp(void);								// 半径の拡大

private:
	int m_nCounter;			// フレームカウンター
	float m_fRadiusNum;		// プレイヤーの半径保持
};

#endif