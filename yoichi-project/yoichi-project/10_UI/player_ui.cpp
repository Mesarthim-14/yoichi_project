//=============================================================================
//
// プレイヤーUI管理クラス[player_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "player_ui.h"
#include "item.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"
#include "star_ui.h"
#include "Fly_ui.h"
#include "effect.h"
#include "effect_factory.h"

//=============================================================================
// [CPlayer_UI] コンストラクタ
//=============================================================================
CPlayer_UI::CPlayer_UI(PRIORITY Priority) : CScene(Priority)
{

}

//=============================================================================
// [~CPlayer_UI] デストラクタ
//=============================================================================
CPlayer_UI::~CPlayer_UI()
{

}

//=============================================================================
// [Create] オブジェクトの生成
// 引数
// プレイヤーの番号
//=============================================================================
CPlayer_UI *CPlayer_UI::Create(void)
{
    CPlayer_UI *PlayerUI = nullptr;
    if (PlayerUI == nullptr)
    {
        // メモリの確保と初期化
        PlayerUI = new CPlayer_UI;
        PlayerUI->Init();
    }
    return PlayerUI;
}

//=============================================================================
// [Init] 初期化処理
// 引数
// プレイヤーの番号
//=============================================================================
HRESULT CPlayer_UI::Init(void)
{
    return S_OK;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
void CPlayer_UI::Init(int nPlayerNum)
{
    m_pStarUI = CStar_UI::Create();
    m_pStarUI->SetPosition(nPlayerNum);

    m_pFlyUI = CFly_UI::Create();
    m_pFlyUI->Init(nPlayerNum);
}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CPlayer_UI::Uninit(void)
{
    // UIの破棄
    m_pStarUI->Uninit();

    // メモリ確保
    for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
    {
        // !nullcheck
        if (m_apItem[nCount] != nullptr)
        {
            // 終了処理
            m_apItem[nCount]->Uninit();
            m_apItem[nCount] = nullptr;
        }
    }

    // 飛行UIの破棄
    if (m_pFlyUI != nullptr)
    {
        // 終了処理
        m_pFlyUI->Uninit();
        m_pFlyUI = nullptr;
    }

    // 配列があれば
    if (m_apItem.size() != NULL)
    {
        // 配列のクリア
        m_apItem.clear();
    }
    Release();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CPlayer_UI::Update(void)
{
    // 各UIの更新処理

    // メモリ確保
    for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
    {
        // !nullcheck
        if (m_apItem[nCount] != nullptr)
        {
            // アイテムの削除フラグが立ったら
            if (m_apItem[nCount]->GetEnd() == true)
            {
                // 配列を空にする
                m_apItem.erase(m_apItem.begin() + nCount);
            }
        }
    }
}

//=============================================================================
// [Draw]描画処理
//=============================================================================
void CPlayer_UI::Draw(void)
{
}

//=============================================================================
// アイテムのデータを渡す
//=============================================================================
void CPlayer_UI::AcquiredItem(CItem *pItem)
{
    if (m_apItem.size() == 0)
    {
        // アイテムのポインタ
        m_apItem.push_back(pItem);
    }
    else if (m_apItem[0] != nullptr)
    {
        // 使われている状態なら
        if (m_apItem[0]->GetUse() == true)
        {
            // アイテムのポインタ
            m_apItem.push_back(pItem);
        }
    }
}

//=============================================================================
// アイテムの使用処理
//=============================================================================
void CPlayer_UI::UseItem(void)
{
    for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
    {
        // !nullcheck
        if (m_apItem[nCount] != nullptr)
        {
            if (m_apItem[nCount]->GetUse() == false)
            {
                // アイテムを使う
                m_apItem[nCount]->SetItem();

                break;
            }
        }
    }

}

//=============================================================================
// アイテム削除
//=============================================================================
void CPlayer_UI::ItemErase(void)
{
    // メモリ確保
    for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
    {
        // !nullcheck
        if (m_apItem[nCount] != nullptr)
        {
            // アイテムの削除フラグが立ったら
            if (m_apItem[nCount]->GetEnd() == true)
            {
                // 配列を空にする
                m_apItem.erase(m_apItem.begin() + nCount);
            }
        }
    }
}
