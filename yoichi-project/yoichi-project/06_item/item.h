#ifndef _ITEM_H_
#define _ITEM_H_
//=============================================================================
//
// アイテムクラスヘッダー	[item.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ITEM_UI_POS_X	(100.0f)			// アイテムの座標
#define ITEM_UI_POS_Y	(100.0f)			// アイテムの座標
#define ITEM_UI_POS_Z	(0.0f)				// アイテムの座標
#define ITEM_UI_SIZE_X	(70.0f)				// アイテムのサイズ
#define ITEM_UI_SIZE_Y	(70.0f)				// アイテムのサイズ
#define ITEM_UI_SIZE_Z	(0.0f)				// アイテムのサイズ

#define ITEM_UI_POS_PLAYER_1		{SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4-130.0f,0.0f}      // UIの位置(1P)
#define ITEM_UI_POS_PLAYER_2		{SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4-130.0f,0.0f}      // UIの位置(2P)
#define ITEM_UI_POS_PLAYER_3		{SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-130.0f,0.0f}      // UIの位置(3P)
#define ITEM_UI_POS_PLAYER_4		{SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4-(SCREEN_HEIGHT/2)+130.0f,0.0f}      // UIの位置(4P)

#define ITEM_UI_SIZE	(D3DXVECTOR3(ITEM_UI_SIZE_X, ITEM_UI_SIZE_Y, ITEM_UI_SIZE_Z))   // UIの大きさ

//=============================================================================
// 前方宣言
//=============================================================================
class CUi;

//=============================================================================
// アイテムボックスクラス
//=============================================================================
class CItem : public CScene
{
public:
	CItem(PRIORITY Priority = PRIORITY_1);				// コンストラクタ
	~CItem();											// デストラクタ

	virtual HRESULT Init(void);	// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理

	virtual void SetItem(void) = 0;								// アイテムの設定
	virtual void UndoItem(void) = 0;							// アイテムの効果を戻す

	void UiUninit(void);										// UIの終了処理

    D3DXVECTOR3 SetPosition(int nPlayer);                                   // UIの位置の設定

	// Set関数
	void SetUi(CUi *pUi)		{ m_pUi = pUi; }							// Uiの設定
	void SetNumber(int nNumber)	{ m_nPlayerNumber = nNumber; }				// プレイヤーの番号設定
	void SetEnd(bool bEnd)		{ m_bEnd = bEnd; }							// エンドフラグの設定
	void SetUse(bool bUse)		{ m_bUse = bUse; }							// 使用フラグ

	// Get関数
	CUi *GetUi(void)		{ return m_pUi; }				// UIのポインタ
	int GetPlayerNum(void)	{ return m_nPlayerNumber; }		// プレイヤーの番号
	bool GetEnd(void)		{ return m_bEnd; }				// 削除フラグ
	bool GetUse(void)		{ return m_bUse; }				// 使用フラグ

private:
    static const D3DXVECTOR3 m_position[MAX_PLAYER_NUM];// アイテムのUIの位置

	CUi *m_pUi;				// UIのポインタ
	int m_nPlayerNumber;	// ブレイヤーの番号
	bool m_bEnd;			// アイテムの削除フラグ
	bool m_bUse;
};

#endif