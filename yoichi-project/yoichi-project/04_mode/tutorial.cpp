//=======================================================================================
//
//  [tutorial.cpp]
// Author : 佐藤颯紀
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "tutorial.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"

//=======================================================================================
//静的メンバ変数宣言
//=======================================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[1] = {};

//=======================================================================================
// タイトルクラスのコンストラクタ
//=======================================================================================
CTutorial::CTutorial(PRIORITY Priority) : CScene(Priority)
{
	m_pScene = NULL;
}

//=======================================================================================
// タイトルクラスのデストラクタ
//=======================================================================================
CTutorial::~CTutorial()
{

}

//=======================================================================================
// タイトルクラスのクリエイト処理
//=======================================================================================
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = new CTutorial();

	pTutorial->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	return pTutorial;
}

//=======================================================================================
// タイトルクラスのテクスチャ読み込み処理
//=======================================================================================
HRESULT CTutorial::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/tutorial.png", &m_pTexture[0]);
	return S_OK;
}

//=======================================================================================
// タイトルクラスの初期化処理
//=======================================================================================
HRESULT CTutorial::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene == NULL)
	{
		m_pScene = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

		//テクスチャの設定
		m_pScene->BindTexture(m_pTexture[0]);
	}
	
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
	//pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// タイトルクラスの終了処理
//=======================================================================================
void CTutorial::Uninit(void)
{
	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
	}


	//オブジェクトの破棄
	Release();
}

//=======================================================================================
// タイトルクラスの更新処理
//=======================================================================================
void CTutorial::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();

	// コントローラのstartを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	//エンターキーを押したとき
	if (pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

}

//=======================================================================================
// タイトルクラスの描画処理
//=======================================================================================
void CTutorial::Draw(void)
{

}
