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
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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