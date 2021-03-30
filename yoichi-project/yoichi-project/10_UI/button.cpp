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
#include "resource_manager.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数初期化
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::BUTTON_TYPE CButton::m_eSelectingButton = BUTTON_TYPE_2P;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::CButton()
{
    m_bSelect = false;
	m_eButtonType = BUTTON_TYPE_NONE;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CButton::~CButton()
{
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
	CSound* pSound = GET_SOUND_PTR;
    //選ばれていれば
    if(m_bSelect)
    {
		if (m_bSelectOld)
		{
			//選択したときの処理
			Select();
			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON_SELECT);
		}
        //その状態でボタン入力された時の処理
        if(CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A,0))
        {
            Push();
			pSound->Play(CSound::SOUND_LABEL_SE_BUTTON_PUSH);
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
