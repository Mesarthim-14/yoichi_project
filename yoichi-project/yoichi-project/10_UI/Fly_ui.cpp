//=============================================================================
//
// 飛行UIクラス[Fly.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "Fly_ui.h"
#include "ui.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//プレイヤごとのUIの位置
#define FLYUI_POS_PLAYER1 {SCREEN_WIDTH/4,SCREEN_HEIGHT/4-150.0f,0.0f}
#define FLYUI_POS_PLAYER2 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2),SCREEN_HEIGHT/4-150.0f,0.0f}
#define FLYUI_POS_PLAYER3 {SCREEN_WIDTH/4,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-150.0f,0.0f}
#define FLYUI_POS_PLAYER4 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2),SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-150.0f,0.0f}

#define FLY_UI_SIZE_X (128.0f)                        // UIのサイズ
#define FLY_UI_SIZE_Y (32.0f)                        // UIのサイズ
#define FLY_UI_SIZE_Z (0.0f)                          // UIのサイズ


#define FLY_UI_COLOR {0.0f,1.0f,1.0f,1.0f}          // UIの色
//*****************************************************************************
// マクロ定義
//*****************************************************************************
const D3DXVECTOR3 CFly_UI::m_UIPos[MAX_PLAYER_NUM] =
{
    { FLYUI_POS_PLAYER1 },
    { FLYUI_POS_PLAYER2 },
    { FLYUI_POS_PLAYER3 },
    { FLYUI_POS_PLAYER4 }
};// プレイヤーごとのUIの位置

//=============================================================================
// [CFly_UI] コンストラクタ
//=============================================================================
CFly_UI::CFly_UI(PRIORITY Priority) : CScene(Priority)
{
}

//=============================================================================
// [~CFly_UI] デストラクタ
//=============================================================================
CFly_UI::~CFly_UI()
{
}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CFly_UI * CFly_UI::Create(void)
{
    CFly_UI *FlyUI = nullptr;
    if (FlyUI == nullptr)
    {
        // メモリの確保と初期化
        FlyUI = new CFly_UI;
        FlyUI->Init();
    }
    return FlyUI;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
HRESULT CFly_UI::Init(void)
{
    return S_OK;
}

//=============================================================================
// [Init] 初期化処理
// 引数
// nPlayerNum　:　プレイヤーの番号
//=============================================================================
void CFly_UI::Init(int nPlayerNum)
{
    // テクスチャのポインタ取得
    CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

    // プレイヤー番号を保存
    m_nPkayerNum = nPlayerNum;

    m_pUI = CUi::Create(m_UIPos[m_nPkayerNum], { FLY_UI_SIZE_X ,FLY_UI_SIZE_Y ,FLY_UI_SIZE_Z });
    m_pUI->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLY_FRAME));

    m_pGauge = CPolygon::Create(m_UIPos[m_nPkayerNum], { FLY_UI_SIZE_X ,FLY_UI_SIZE_Y ,FLY_UI_SIZE_Z });
    m_pGauge->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLY_GAUGE));

}

//=============================================================================
// [Uninit]終了処理
//=============================================================================
void CFly_UI::Uninit(void)
{
        //// !nullcheck
        //if (m_pUI != nullptr)
        //{
        //    // UIの終了処理
        //    m_pUI->Uninit();
        //    m_pUI = NULL;
        //}

        // !nullcheck
        if (m_pGauge != nullptr)
        {
            // ゲージの終了処理
            m_pGauge->Uninit();
            delete m_pGauge;
            m_pGauge = NULL;
        }

    Release();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CFly_UI::Update(void)
{
    SetFly();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CFly_UI::Draw(void)
{
    m_pGauge->Draw();
}

//=============================================================================
// [SetFly] 飛行の設定
//=============================================================================
void CFly_UI::SetFly(void)
{
    // 飛行時間の取得
   int FliTime = CGame::GetPlayer(m_nPkayerNum)->GetFlyTime();

   // 位置とサイズを反映
   m_pGauge->UpdateVertex(FliTime, MAX_FLY_TIME);

}

