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

//=============================================================================
// マクロ定義
//=============================================================================
#define ROTATION_NUM		(0.1f)		// 回転の速さ

//=============================================================================
//リザルトクラスのコンストラクタ
//=============================================================================
CTitle::CTitle()
{
	//メンバ変数のクリア
	m_pScene2D = NULL;
	m_pPress = NULL;
	m_pTitleName = NULL;
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
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	if (m_pScene2D == NULL)
	{
		//2Dオブジェクトの生成
		m_pScene2D = CScene2D::Create(SCREEN_SIZE/2, SCREEN_SIZE);

		if (m_pScene2D != NULL)
		{
			m_pScene2D->BindTexture(NULL);
		}
	}

	// PRESSロゴのポインタ
	if (m_pPress == NULL)
	{
		m_pPress = CScene2D::Create(D3DXVECTOR3((SCREEN_SIZE / 2).x, (SCREEN_SIZE / 2).y + TITLE_PRESS_POS_Y, 0.0f), D3DXVECTOR3(TITLE_PRESS_SIZE_X, TITLE_PRESS_SIZE_Y, 0.0f));
		m_pPress->BindTexture(NULL);
	}

	// nullcheck
	if (m_pTitleName == NULL)
	{
		//2Dオブジェクトの生成
		m_pTitleName = CScene2D::Create(D3DXVECTOR3((SCREEN_SIZE / 2).x, (SCREEN_SIZE / 2).y - 125.0f, 0.0f), D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_Y, 0.0f));

		// !nullcheck
		if (m_pTitleName != NULL)
		{
			// テクスチャのポインタ
			m_pTitleName->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE_LOGO));
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

	if (m_pTitleName != NULL)
	{
		m_pTitleName->Uninit();
		m_pTitleName = NULL;
	}
	
	if (m_pPress != NULL)
	{
		m_pPress->Uninit();
		m_pPress = NULL;
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
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
	CScene::UpdateAll();
	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	// プレイヤーのナンバー設定
	SetPlayerNum();
}

//=============================================================================
//リザルトクラスの描画処理
//=============================================================================
void CTitle::Draw(void)
{
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
