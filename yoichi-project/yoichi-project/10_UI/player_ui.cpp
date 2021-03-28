//=============================================================================
//
// プレイヤーUI管理クラス[player_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "player_ui.h"
#include "item.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"
#include "star_ui.h"
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

    //    //ジャンプモーションの再生
    //    SetMotion(4);
    //    SetLanding(false);
    //}
    ////=============================================================================
    //// Author : Ito Yogo
    ////=============================================================================
    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, m_nNumber))
    //{
    //    // 雷のアイテムを使われたときのエフェクト
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_THUNDER);

    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(0.0f, 500.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_LIGHTNINGSTRIKE);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y, m_nNumber))
    //{
    //    // 星がとられたときのエフェクト
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STAR);
    //    //CEffectFactory::CreateEffect(GetPos()/* + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f)*/, CEffectFactory::EFFECT_TYPE::EFFECT_NUM_SHOCKWAVE);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, m_nNumber))
    //{
    //    // 速度が落ちた時のエフェクト
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSDOWN);

    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSDOWNPARTICLE);

    //}
    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nNumber))
    //{
    //    // 速度が上がった時のエフェクト
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSUP);

    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATESUPPARTICLE);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L2_TRIGGER, m_nNumber))
    //{
    //    // 爆発のエフェクト
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSION);
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSIONCIRCLE);
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSIONSPARK);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nNumber))
    //{
    //    // 風のアイテムのエフェクト
    //    CWind::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43),
    //        ZeroVector3, 10.0f, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_nNumber);

    //    CWind::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43),
    //        ZeroVector3, 10.0f, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_nNumber);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R3, m_nNumber))
    //{
    //    // バリアのエフェクト
    //    CBARRIER::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43),
    //        D3DXVECTOR3(50.0f, 50.0f, 50.0f), 10.0f, D3DXVECTOR3(5.0f, 5.0f, 5.0f), m_nNumber);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L3, m_nNumber))
    //{
    //    for (int nCount = 0; nCount < 100; nCount++)
    //    {
    //        // バリアが壊されたときのエフェクト
    //        CBARRIEREFFECT::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //            GetModelAnime(21)->GetMtxWorld()._42,
    //            GetModelAnime(21)->GetMtxWorld()._43),
    //            D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(30.0f, 30.0f, 30.0f), 10.0f);
    //    }
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, m_nNumber))
    //{
    //    // マジックハンドのエフェクト
    //    CMagichand::Create(-MAGICHAND_DISTANCE, CTexture::SEPARATE_TEX_MAGICHANDLEFT, m_nNumber);
    //    CMagichand::Create(MAGICHAND_DISTANCE, CTexture::SEPARATE_TEX_MAGICHANDRIGHT, m_nNumber);
    //}
    ////=============================================================================
//}

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
