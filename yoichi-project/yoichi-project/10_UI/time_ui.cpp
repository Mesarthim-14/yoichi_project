//=============================================================================
//
// 制限時間UIクラス [time_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "time_ui.h"
#include "timer.h"
#include "number_2d.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_UI_SIZE_X (64.0f)  // 数字の大きさ(X軸)
#define NUM_UI_SIZE_Y (128.0f)  // 数字の大きさ(Y軸)
#define NUM_UI_SIZE_Z (0.0f)    // 数字の大きさ(Z軸)

#define GAME_TIME (5)           // ゲームの制限時間(秒)
#define NUM_UI_POS_X (720.0f+(NUM_UI_SIZE_X/2 * MAX_NAM))   // 数字の位置(X軸)
#define NUM_UI_POS_Y (100.0f)   // 数字の位置(Y軸)
#define NUM_UI_POS_Z (0.0f)     // 数字の位置(Z軸)

#define NUM_RADIX    (10.0f)    // スコアの基数

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// [CTime_UI]コンストラクタ
//=============================================================================
CTime_UI::CTime_UI(PRIORITY Priority) : CScene2D(Priority)
{
    m_Timer = nullptr;
}

//=============================================================================
// [CTime_UI]デストラクタ
//=============================================================================
CTime_UI::~CTime_UI()
{

}

//=============================================================================
// [Create]オブジェクトの生成
//=============================================================================
CTime_UI * CTime_UI::Create(void)
{
    CTime_UI *pTimerUI = nullptr;
    if (pTimerUI == nullptr)
    {
        // メモリの確保と初期化
        pTimerUI = new CTime_UI;
        pTimerUI->Init();
    }
    return pTimerUI;
}

//=============================================================================
// [Init]初期化処理
//=============================================================================
void CTime_UI::Init(void)
{
    CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
    // タイマーのセット
    m_Timer = CTimer::Create();
    m_Timer->SetTimer(GAME_TIME);

    // ナンバーの生成
    for (unsigned int nCntNum = 0; nCntNum < MAX_NAM; nCntNum++)
    {
        D3DXVECTOR3 pos = { NUM_UI_POS_X - (nCntNum * NUM_UI_SIZE_X),NUM_UI_POS_Y,NUM_UI_POS_Z };
        m_pNumber[nCntNum] = CNumber2d::Create(pos, { NUM_UI_SIZE_X ,NUM_UI_SIZE_Y ,NUM_UI_SIZE_Z });
        m_pNumber[nCntNum]->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_NUMBER));
    }
}

//=============================================================================
// [Uninit]終了処理
//=============================================================================
void CTime_UI::Uninit(void)
{
    // ナンバーの解放
    for (int nCntNum = 0; nCntNum < MAX_NAM; nCntNum++)
    {
        if (m_pNumber)
        {
            m_pNumber[nCntNum]->Uninit();

        }
    }
    // 終了フラグ
    Release();
}

//=============================================================================
// [Updete]更新処理
//=============================================================================
void CTime_UI::Update(void)
{
    // タイマー更新
    m_Timer->Updete();

    // 数字の変更
    SetNumber();
}

//=============================================================================
// [Draw]描画処理
//=============================================================================
void CTime_UI::Draw(void)
{

}

//=============================================================================
// [SetNumber]数字の設定
//=============================================================================
void CTime_UI::SetNumber(void)
{
    // タイマーの数値を秒に変換
    int nTimeMin = m_Timer->GetTimer() / 60;

    // 桁ごとに分解
    for (unsigned int nCntNum = 0; nCntNum < MAX_NAM; nCntNum++)
    {
        int nDrawRenge = (int)powf(NUM_RADIX, (float)nCntNum + 1);
        int nDrawRenge2 = (int)powf(NUM_RADIX, (float)nCntNum);
        int nAnswer = nTimeMin % nDrawRenge / nDrawRenge2;
        // 1桁ずつ設定
        m_pNumber[nCntNum]->SetNumber(nAnswer);
    }

}
