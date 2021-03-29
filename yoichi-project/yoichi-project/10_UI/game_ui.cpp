//=============================================================================
//
// ゲーム画面のUIヘッダ[game_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "game_ui.h"
#include "ui.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "star_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_UI_POS_000 {SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f} // UIの位置
#define GAME_UI_POS_001 {SCREEN_WIDTH/2-60.0f,SCREEN_HEIGHT/2,0.0f} // UIの位置
#define GAME_UI_POS_002 {SCREEN_WIDTH/2+30.0f,SCREEN_HEIGHT/2,0.0f} // UIの位置

#define GAME_UI_SIZE_000 {128.0f,128.0f,0.0f} // UIのサイズ
#define GAME_UI_SIZE_001 {32.0f,32.0f,0.0f} // UIのサイズ
#define GAME_UI_SIZE_002 {64.0f,32.0f,0.0f} // UIのサイズ
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
const CGame_UI::GEME_UI_DATA CGame_UI::m_UI_DATA[CGame_UI::GAME_UI_MAX] = 
{
    { GAME_UI_POS_000 ,GAME_UI_SIZE_000 ,CTexture::TEXTURE_NUM_FRAME },
    { GAME_UI_POS_001 ,GAME_UI_SIZE_001 ,CTexture::TEXTURE_NUM_STAR },
    { GAME_UI_POS_002 ,GAME_UI_SIZE_002 ,CTexture::TEXTURE_NUM_POINT_UP },

};// UIの情報

//=============================================================================
// [CGame_UI] コンストラクタ
//=============================================================================
CGame_UI::CGame_UI()
{

}

//=============================================================================
// [~CGame_UI] デストラクタ
//=============================================================================
CGame_UI::~CGame_UI()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CGame_UI * CGame_UI::Create(void)
{
    CGame_UI *pGameUI = nullptr;
    if (pGameUI == nullptr)
    {
        // メモリの確保と初期化
        pGameUI = new CGame_UI;
        pGameUI->Init();
    }
    return pGameUI;

}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
HRESULT CGame_UI::Init(void)
{
    // テクスチャのポインタ取得
    CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

    for (int nCntUI = 0; nCntUI < GAME_UI_MAX; nCntUI++)
    {
        m_pUI[nCntUI] = CUi::Create(m_UI_DATA[nCntUI].pos, m_UI_DATA[nCntUI].size);
        m_pUI[nCntUI]->BindTexture(pTexture->GetTexture(m_UI_DATA[nCntUI].FileName));
    }

    // テクスチャの設定
    return S_OK;
}

//=============================================================================
// [Uninit]終了処理
//=============================================================================
void CGame_UI::Uninit(void)
{
    for (int nCntUI = 0; nCntUI < GAME_UI_MAX; nCntUI++)
    {
        // !nullcheck
        if (m_pUI[nCntUI] != nullptr)
        {
            // UIの終了処理
            m_pUI[nCntUI]->Uninit();
            m_pUI[nCntUI] = NULL;
        }
    }
    Release();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CGame_UI::Update(void)
{
    CGame_UI::SetColor();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CGame_UI::Draw(void)
{
}


//=============================================================================
// [SetColor] 色の設定
//=============================================================================
void CGame_UI::SetColor(void)
{
    CStar::STAR_COLOR_TYPE Color = CStarManager::GetGameStarColor();
    // 現在の色を取得
    switch (Color)
    {
        break;
    case CStar::STAR_COLOR_TYPE_RED:
        m_pUI[GAME_UI_STAR]->SetCol(STAR_COLOR_RED);
        break;
    case CStar::STAR_COLOR_TYPE_BLUE:
        m_pUI[GAME_UI_STAR]->SetCol(STAR_COLOR_BLUE);
        break;
    case CStar::STAR_COLOR_TYPE_YELLOW:
        m_pUI[GAME_UI_STAR]->SetCol(STAR_COLOR_YELLOW);
        break;
    case CStar::STAR_COLOR_TYPE_GREEN:
        m_pUI[GAME_UI_STAR]->SetCol(STAR_COLOR_GREEN);
        break;
    default:

        break;
    }

}
