//=============================================================================
//
// アイテムクラス処理 [item.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//プレイヤごとのUIの位置
#define ITEM_POS_PLAYER1 {SCREEN_WIDTH/4-280,SCREEN_HEIGHT/4-120.0f,0.0f}
#define ITEM_POS_PLAYER2 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+280,SCREEN_HEIGHT/4-120.0f,0.0f}
#define ITEM_POS_PLAYER3 {SCREEN_WIDTH/4-280,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-120.0f,0.0f}
#define ITEM_POS_PLAYER4 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+280,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-120.0f,0.0f}

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
const D3DXVECTOR3 CItem::m_UI_DATA[MAX_PLAYER_NUM] =
{
    { ITEM_POS_PLAYER1 },
    { ITEM_POS_PLAYER2 },
    { ITEM_POS_PLAYER3 },
    { ITEM_POS_PLAYER4 }
};// UIの位置


//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem(PRIORITY Priority) : CScene(Priority)
{
	m_pUi = NULL;
	m_nPlayerNumber = 0;
	m_bEnd = NULL;
	m_bUse = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	// !nullcheck
	if (m_pUi != nullptr)
	{
		m_pUi->Uninit();
		m_pUi = NULL;
	}

	// リリース
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	// 終了フラグ
	if (m_bEnd == true)
	{
		// 終了処理
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{

}

//=============================================================================
// UIの終了処理
//=============================================================================
void CItem::UiUninit()
{
	// !nullcheck
	if (m_pUi != nullptr)
	{
		// UIの終了処理
		m_pUi->Uninit();
		m_pUi = NULL;
	}
}

//=============================================================================
// [SetPosition] UIの位置設定
//=============================================================================
D3DXVECTOR3 CItem::SetPosition(int nPlayerNum)
{  
    return m_UI_DATA[nPlayerNum];
}
