//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "bg.h"
#include "billboard.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "mesh_3d.h"
#include "model.h"
#include "effect_factory.h"
#include "player.h"
#include "renderer.h"
#include "resource_manager.h"
#include "scene3D.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "xfile.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pKeyboard = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CInputJoypad *CManager::m_pJoypad = NULL;
CScene *CManager::m_pScene = NULL;
CResourceManager *CManager::m_pResourceManager = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダラークラスのインスタンス生成
	m_pRenderer = new CRenderer;

	//メモリが確保できたら
	if (m_pRenderer != NULL)
	{
		// 初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//入力処理クラスのインスタンス生成
	m_pKeyboard = new CInputKeyboard;

	//メモリが確保できたら
	if (m_pKeyboard != NULL)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//入力処理クラスのインスタンス生成
	m_pJoypad = new CInputJoypad;

	//メモリが確保できたら
	if (m_pJoypad != NULL)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	// nullcheck
	if (m_pResourceManager == NULL)
	{
		// リソースマネージャのインスタンス生成
		m_pResourceManager = CResourceManager::GetInstance();
	}

	//サウンドのインスタンス生成
	//m_pSound = new CSound;
	//if (m_pSound != NULL)
	//{
	//	m_pSound->Init(hWnd);
	//}

	//フェードクラスのクリエイト
	m_pFade = CFade::Create();

	//全テクスチャの読み込み
	LoadAll();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//全テクスチャの破棄
	UnloadAll();

	//現在モードの終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			// 終了処理
		//	m_pTitle->Uninit();
			m_pTitle = NULL;
		}

		break;

		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			// 終了処理
		//	m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			// 終了処理
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	}

	// nullchack
	if (m_pFade != NULL)
	{
		//フェードクラスの終了処理呼び出し
		m_pFade->Uninit();

		//メモリの破棄
		delete m_pFade;

		//メモリのクリア
		m_pFade = NULL;
	}

	// !nullcheck
	if (m_pResourceManager != NULL)
	{
		// リソースのロード
		delete m_pResourceManager;
		m_pResourceManager = NULL;
	}

	if (m_pKeyboard != NULL)
	{
		//入力処理クラスの終了処理呼び出し
		m_pKeyboard->Uninit();

		//メモリの削除
		delete m_pKeyboard;

		//メモリのクリア
		m_pKeyboard = NULL;
	}

	if (m_pJoypad != NULL)
	{
		//入力処理クラスの終了処理呼び出し
		m_pJoypad->Uninit();

		//メモリの削除
		delete m_pJoypad;

		//メモリのクリア
		m_pJoypad = NULL;
	}

	if (m_pRenderer != NULL)
	{
		//レンダラークラスの終了処理呼び出し
		m_pRenderer->Uninit();

		//メモリの削除
		delete m_pRenderer;

		//メモリのクリア
		m_pRenderer = NULL;
	}

	// シーン情報のリリース
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{

	if (m_pKeyboard != NULL)
	{
		//入力処理クラスの更新処理呼び出し
		m_pKeyboard->Update();
	}

	if (m_pJoypad != NULL)
	{
		//入力処理クラスの更新処理呼び出し
		m_pJoypad->Update();
	}


	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			// タイトル処理
			m_pTitle->Update();
		}
		break;

		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	}

	if (m_pFade != NULL)
	{
		//フェードクラスの更新処理呼び出し
		m_pFade->Update();
	}

	if (m_pRenderer != NULL)
	{
		//レンダラークラスの描画処理呼び出し
		m_pRenderer->Update();
	}

}

//=============================================================================
//描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//レンダラークラスの描画処理呼び出し
		m_pRenderer->Draw();
	}
}

//=============================================================================
//テクスチャの全ロード処理
//=============================================================================
void CManager::LoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != NULL)
	{
		// リソースのロード
		m_pResourceManager->LoadAll();
	}

	CTutorial::Load();
	CEffectFactory::ReadFile();
	CMesh3d::ReadFile();
}

//=============================================================================
//テクスチャの全アンロード処理
//=============================================================================
void CManager::UnloadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != NULL)
	{
		// リソースのロード
		m_pResourceManager->UnloadAll();
	}
}

//=============================================================================
//ゲームモードの設定処理
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	CSound *pSound = GET_SOUND_PTR;

	//現在モードの終了
	switch (m_mode)
	{
		// タイトル
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			// タイトル処理
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);
			m_pTutorial = NULL;
		}
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
			m_pGame = NULL;
		}
		break;
	}

	// シーン情報のリリース
	CScene::ReleaseAll();

	//モードを設定
	m_mode = mode;

	//設定されたモードをクリエイト
	switch (m_mode)
	{
		// タイトル
	case MODE_TYPE_TITLE:
		if (m_pTitle == NULL)
		{
			// タイトル生成
			m_pTitle = CTitle::Create();
		}
		break;

		// チュートリアル
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			// チュートリアル生成
			m_pTutorial = CTutorial::Create();
		}
		break;

		// ゲーム
	case MODE_TYPE_GAME:
		if (m_pGame == NULL)
		{
			// ゲーム生成
			m_pGame = CGame::Create();
		}

		break;

	default:
		break;
	}
}

//=============================================================================
//ゲームモード情報の取得
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//レンダラー情報取得
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
//キーボード情報取得
//=============================================================================
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=============================================================================
//フェード情報取得
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
//ジョイパッド情報取得
//=============================================================================
CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}