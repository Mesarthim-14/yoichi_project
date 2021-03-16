#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_
//=============================================================================
//
// アイテム管理クラスヘッダー [item_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CItemBox;

//=============================================================================
// エフェクト生成
//=============================================================================
class CItemBoxManager
{
public:
	// アイテムの種類の列挙型
	enum ITEM_TYPE
	{
		ITEM_TYPE_NONE = -1,	// 初期値
		ITEM_TYPE_BLUE_WING,	// 青い羽根
		ITEM_TYPE_MAX			// 最大値
	};

	~CItemBoxManager();								// デストラクタ

	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	void CreateItemBox(void);						// アイテムボックスクラスの生成
	void CreateItem(void);							// アイテムクラスの生成
	static CItemBoxManager *GetInstance(void);		// インスタンス取得関数

private:
	CItemBoxManager();								// コンストラクタ
	static CItemBoxManager *m_pItemManager;			// 自身のクラスのポインタ
	std::vector<CItemBox*> m_pItemBox;				// アイテムボックスのポインタ
};
#endif
