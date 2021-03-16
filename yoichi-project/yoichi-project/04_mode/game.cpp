//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "quest_logo.h"
#include "effect_factory.h"
#include "mesh_3d.h"
#include "resource_manager.h"
#include "effect_factory.h"

//=======================================================================================
// static初期化
//=======================================================================================
CCamera *CGame::m_pCamera[MAX_PLAYER_NUM] = {};
CPlayer *CGame::m_pPlayer[MAX_PLAYER_NUM] = {};
CLight *CGame::m_pLight = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CBg *CGame::m_pBg = NULL;
CPause *CGame::m_pPause = NULL;
int CGame::m_nPlayerNum = 1;

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;

	// 0だったら
	if (m_nPlayerNum == 0)
	{
		m_nPlayerNum = 1;
	}
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{
	// static変数初期化
	m_nPlayerNum = 0;
}

//=======================================================================================
// クリエイト
//=======================================================================================
CGame* CGame::Create(void)
{
	// メモリ確保
	CGame* pGame = new CGame();

	// 初期化処理
	pGame->Init(ZeroVector3, ZeroVector3);

	return pGame;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// プレイヤーの数分ループ
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{	
		// nullcheck
		if (m_pCamera[nCount] == NULL)
		{
			// カメラクラスのクリエイト
			m_pCamera[nCount] = CCamera::Create(nCount);
		}

		// nullcheck
		if (m_pPlayer[nCount] == NULL)
		{
			// プレイヤーの生成
			m_pPlayer[nCount] = CPlayer::Create(
				ZeroVector3, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), 
				nCount);
		}
	}

	//ライトクラスの生成
	m_pLight = new CLight;

	// ライトの初期化処理
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// メッシュフィールド
	m_pMeshField = CMeshField::Create();

	// 背景
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create(BG_POS, BG_SIZE);
	}

	//BGM
//	CSound *pSound = CManager::GetSound();
//	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//フォントの生成
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}

	// ライトの終了処理
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// プレイヤーの数
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{
		if (m_pCamera[nCount] != NULL)
		{
			//カメラクラスの終了処理呼び出す
			m_pCamera[nCount]->Uninit();

			//メモリの破棄
			delete m_pCamera[nCount];

			//メモリのクリア
			m_pCamera[nCount] = NULL;
		}

		// プレイヤーの終了処理
		if (m_pPlayer[nCount] != NULL)
		{
			m_pPlayer[nCount]->Uninit();
			m_pPlayer[nCount] = NULL;
		}
	}

	// !nullcheck
	if (CManager::GetResourceManager() != NULL)
	{
		//サウンド情報取得
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

		// !nullcheck
		if (pSound != NULL)
		{
			//ゲームBGM停止
		//	pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	//オブジェクトの破棄
	Release();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	// プレイヤー分
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{
		// !nullcheck
		if (m_pCamera != NULL)
		{
			//カメラクラスの更新処理
			m_pCamera[nCount]->Update();
		}
	}
	// ゲームの設定
	SetGame();
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{
	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}

	// ライト
	if (m_pLight != NULL)
	{
		m_pLight->ShowLightInfo();
	}
}

//=======================================================================================
// ゲームの設定
//=======================================================================================
void CGame::SetGame(void)
{
	// ゲームのタイムカウンター
	m_nTimeCounter++;
}

//=======================================================================================
// カメラの情報
//=======================================================================================
CCamera * CGame::GetCamera(int nCount)
{
	return m_pCamera[nCount];
}

//=======================================================================================
// ライトの情報
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// プレイヤーの情報
//=======================================================================================
CPlayer * CGame::GetPlayer(int nCount)
{
	return m_pPlayer[nCount];
}

//=======================================================================================
// コンテニューの情報
//=======================================================================================
CPause * CGame::GetPause(void)
{
	return m_pPause;
}