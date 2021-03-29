//=============================================================================
//
// 星の取得数UIクラス[star_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "star_ui.h"
#include "number_2d.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//プレイヤごとのUIの位置
#define STARUI_POS_PLAYER1 {SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4+130.0f,0.0f}
#define STARUI_POS_PLAYER2 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4+130.0f,0.0f}
#define STARUI_POS_PLAYER3 {SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)+130.0f,0.0f}
#define STARUI_POS_PLAYER4 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)+130.0f,0.0f}

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
// プレイヤーごとのUIの位置
const D3DXVECTOR3 CStar_UI::m_posUI[MAX_PLAYER_NUM] =
{
    { STARUI_POS_PLAYER1 },
    { STARUI_POS_PLAYER2 },
    { STARUI_POS_PLAYER3 },
    { STARUI_POS_PLAYER4 }
};

//=============================================================================
// [CStar_UI] コンストラクタ
//=============================================================================
CStar_UI::CStar_UI()
{

}

//=============================================================================
// [~CStar_UI] デストラクタ
//=============================================================================
CStar_UI::~CStar_UI()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CStar_UI *CStar_UI::Create(void)
{
    CStar_UI *StarUI = nullptr;
    if (StarUI == nullptr)
    {
        // メモリの確保と初期化
        StarUI = new CStar_UI;
        StarUI->Init();
    }
    return StarUI;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
HRESULT CStar_UI::Init(void)
{
    return S_OK;
}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CStar_UI::Uninit(void)
{
    // ナンバーの破棄
    // ナンバー生成
    for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
    {
        m_apNumber[nCntNum]->Uninit();

    }
    Release();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CStar_UI::Update(void)
{
    SetNumber();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CStar_UI::Draw(void)
{
}

//=============================================================================
// [SetPosition] 位置の設定
//=============================================================================
void CStar_UI::SetPosition(int nPlayerNum)
{

    D3DXVECTOR3 pos;
   int nPlayerTotal = CGame::GetPlayerNum();
   CTexture *pTexture = GET_TEXTURE_PTR;

   // プレイヤー番号を保存
   m_nPlayerNum = nPlayerNum;

   // ナンバー生成
   for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
   {
       pos = { m_posUI[nPlayerNum].x - (nCntNum*50.0f), m_posUI[nPlayerNum].y ,m_posUI[nPlayerNum].z };
       m_apNumber[nCntNum] = CNumber2d::Create(pos, { 50.0f,80.0f,0.0f });
       m_apNumber[nCntNum]->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_NUMBER));
   }
}
//=============================================================================
// [SetNumber] 数字の設定
//=============================================================================
void CStar_UI::SetNumber(void)
{
    // 星の所持数を取得
    // ナンバーの更新
    for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
    {
        int nStar = CGame::GetPlayer(m_nPlayerNum)->GetStarNum();
        m_apNumber[nCntNum]->SetNumber(nStar);

        // 桁ごとに分解
        int nDrawRenge = (int)powf(NUM_RADIX, (float)nCntNum + 1);
        int nDrawRenge2 = (int)powf(NUM_RADIX, (float)nCntNum);
        int nAnswer = nStar % nDrawRenge / nDrawRenge2;
        // 1桁ずつ設定
        m_apNumber[nCntNum]->SetNumber(nAnswer);
    }
}