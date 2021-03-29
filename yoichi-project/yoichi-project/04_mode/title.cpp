//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "game.h"
#include "playerselectbutton.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define ROTATION_NUM		(0.1f)		// 回転の速さ
#define BUTTON_POS_Y		(SCREEN_HEIGHT * 3/4)
//=============================================================================
//リザルトクラスのコンストラクタ
//=============================================================================
CTitle::CTitle()
{
	//メンバ変数のクリア
	m_pScene2D = NULL;
	m_bDisplayButton = false;
	m_nSelectButton = 0;
	ZeroMemory(m_apPlayerSelectButton, sizeof(m_apPlayerSelectButton));
}

//=============================================================================
//リザルトクラスのデストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
//リザルトクラスのクリエイト処理
//=============================================================================
CTitle * CTitle::Create(void)
{
	//リザルトクラスのポインタ変数
	CTitle *pTitle = new CTitle;

	//メモリが確保できていたら
	if (pTitle != NULL)
	{
		//初期化処理呼び出し
		pTitle->Init();
	}

	return pTitle;
}

//=============================================================================
//リザルトクラスの初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	// テクスチャのポインタ
	CTexture *pTexture = GET_TEXTURE_PTR;

	if (m_pScene2D == NULL)
	{
		//2Dオブジェクトの生成
		m_pScene2D = CScene2D::Create(SCREEN_SIZE/2, SCREEN_SIZE);

		if (m_pScene2D != NULL)
		{
			m_pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE));
		}
	}
	return S_OK;
}

//=============================================================================
//リザルトクラスの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	for (int nCount = 0; nCount < MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1; nCount++)
	{
		if (m_apPlayerSelectButton[nCount] != NULL)
		{
			m_apPlayerSelectButton[nCount]->Uninit();
			m_apPlayerSelectButton[nCount] = NULL;
		}
	}
	//オブジェクトの破棄
	delete this;
}

//=============================================================================
//リザルトクラスの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = GET_SOUND_PTR;
	CScene::UpdateAll();

	SelectButton();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0)|| pKey->GetTrigger(DIK_RETURN))
	{
		if (!m_bDisplayButton)
		{
			m_bDisplayButton = true;
			for (int nCount = 0; nCount < MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1; nCount++)
			{
				m_apPlayerSelectButton[nCount] = CPlayerSelectButton::Create(D3DXVECTOR3(SCREEN_WIDTH / MAX_PLAYER_NUM * (nCount + 1), BUTTON_POS_Y, 0), PLAYER_SELECT_BUTTON, nCount + MIN_PLAYER_NUM);
			}
		}
	}


	// プレイヤーのナンバー設定
	SetPlayerNum();
}

//=============================================================================
//リザルトクラスの描画処理
//=============================================================================
void CTitle::Draw(void)
{
	CScene::DrawAll();
}

//=============================================================================
// プレイヤーの数を設定
//=============================================================================
void CTitle::SetPlayerNum(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (pKey->GetTrigger(DIK_1))
	{
		// プレイヤーの設定
		CGame::SetPlayerNum(1);
	}
	else if (pKey->GetTrigger(DIK_2))
	{
		// プレイヤーの設定
		CGame::SetPlayerNum(2);
	}
	else if (pKey->GetTrigger(DIK_3))
	{
		// プレイヤーの設定
		CGame::SetPlayerNum(3);
	}
	else if (pKey->GetTrigger(DIK_4))
	{
		// プレイヤーの設定
		CGame::SetPlayerNum(4);
	}
}

void CTitle::SelectButton(void)
{
	CInputJoypad* pJoy = CManager::GetJoypad();
	if (pJoy->GetPushCross(CROSS_KEY_RIGHT, 0))
	{
		if (MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1 >  m_nSelectButton + 1)
		{
			m_nSelectButton++;
		}
	}
	if (pJoy->GetPushCross(CROSS_KEY_LEFT, 0))
	{
		if (0 < m_nSelectButton)
		{
			m_nSelectButton--;
		}
	}
	for (int nCount = 0; nCount < MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1; nCount++)
	{
		if (m_apPlayerSelectButton[nCount] != NULL)
		{
			if (nCount == m_nSelectButton)
			{
				m_apPlayerSelectButton[nCount]->SetSelect(true);
			}
			else
			{
				m_apPlayerSelectButton[nCount]->SetSelect(false);
			}
		}
	}
}