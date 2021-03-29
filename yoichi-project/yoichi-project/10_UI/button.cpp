//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	button.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "joypad.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数初期化
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::BUTTON_TYPE CButton::m_eSelectingButton = BUTTON_TYPE_2P;
int CButton::nUsingButtons = 0;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::CButton()
{
    m_bSelect = false;
	nUsingButtons++;
	m_eButtonType = BUTTON_TYPE_NONE;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::~CButton()
{
	nUsingButtons--;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CButton::Init(void)
{
    CUi::Init();
	Unselect();
    return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CButton::Uninit(void)
{
	CUi::Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CButton::Update(void)
{
    D3DXVECTOR3 pos  = GetPos();
    D3DXVECTOR3 size = GetSize();
	CUi::Update();

    //選ばれていれば
    if(m_bSelect)
    {
        //選択したときの処理
        Select();
        //その状態でボタン入力された時の処理
        if(CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A,0))
        {
            Push();
        }
    }
    else
    {
        //前フレームで選択されていれば
        if(m_bSelectOld)
        {
            Unselect();
        }
    }
	m_bSelectOld = m_bSelect;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CButton::Draw(void)
{
	CUi::Draw();
}
