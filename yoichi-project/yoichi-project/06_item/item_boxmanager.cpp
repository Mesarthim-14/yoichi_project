//=============================================================================
//
// アイテム管理クラス [item_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "item_boxmanager.h"
#include "manager.h"
#include "renderer.h"
#include "itembox.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_ITEM_NUM		(5)		// アイテムの出現数

//=============================================================================
// static初期化宣言
//=============================================================================
CItemBoxManager *CItemBoxManager::m_pItemManager = nullptr;	// 自身のポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CItemBoxManager::CItemBoxManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CItemBoxManager::~CItemBoxManager()
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CItemBoxManager::Uninit(void)
{
	// メモリ確保
	for (unsigned nCount = 0; nCount < m_pItemBox.size(); nCount++)
	{
		// !nullcheck
		if (m_pItemBox[nCount] != nullptr)
		{
			// 終了処理
			m_pItemBox[nCount]->Uninit();
			m_pItemBox[nCount] = nullptr;
		}
	}

	// 配列があれば
	if (m_pItemBox.size() != NULL)
	{
		// 配列のクリア
		m_pItemBox.clear();
	}

	// !nullcheck
	if (m_pItemManager != nullptr)
	{
		// ポインタの開放
		delete m_pItemManager;
		m_pItemManager = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CItemBoxManager::Update(void)
{

}

//=============================================================================
// アイテムボックスの生成
//=============================================================================
void CItemBoxManager::CreateItemBox(void)
{
	// アイテムボックスのメモリを確保
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(1500.0f, 1000.0f, -3000.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// アイテムボックスのメモリを確保
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(-2000.0f, 250.0f, 3500.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// アイテムボックスのメモリを確保
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(900.0f, 250.0f, -1500.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// アイテムボックスのメモリを確保
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(5000.0f, 200.0f, 5000.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// アイテムボックスのメモリを確保
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(-4000.0f, 500.0f, -7000.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));
}

//=============================================================================
// アイテムクラスの生成
//=============================================================================
void CItemBoxManager::CreateItem(void)
{
}

//=============================================================================
// インスタンス取得関数
//=============================================================================
CItemBoxManager * CItemBoxManager::GetInstance(void)
{
	// nullcheck
	if (m_pItemManager == nullptr)
	{
		// メモリ確保
		m_pItemManager = new CItemBoxManager;
	}

	return m_pItemManager;
}