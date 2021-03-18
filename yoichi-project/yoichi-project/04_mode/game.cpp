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
#include "effect_factory.h"
#include "mesh_3d.h"
#include "resource_manager.h"
#include "itembox.h"
#include "item_boxmanager.h"
#include "star_manager.h"
#include "result.h"

//=======================================================================================
// static初期化
//=======================================================================================
CCamera *CGame::m_pCamera[MAX_PLAYER_NUM] = {};
CPlayer *CGame::m_pPlayer[MAX_PLAYER_NUM] = {};
CLight *CGame::m_pLight = nullptr;
CMeshField *CGame::m_pMeshField = nullptr;
CBg *CGame::m_pBg = nullptr;
CPause *CGame::m_pPause = nullptr;
CItemBoxManager *CGame::m_pItemManager = nullptr;
int CGame::m_nPlayerNum = 1;
CResult *CGame::m_apResult[MAX_PLAYER_NUM] = {};

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame()
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;
	m_pStarManager = nullptr;

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
	pGame->Init();

	return pGame;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(void)
{
	// プレイヤーの数分ループ
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{	
		// nullcheck
		if (m_pCamera[nCount] == nullptr)
		{
			// カメラクラスのクリエイト
			m_pCamera[nCount] = CCamera::Create(nCount);
		}

		// nullcheck
		if (m_pPlayer[nCount] == nullptr)
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
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// メッシュフィールド
	m_pMeshField = CMeshField::Create();

	// 背景
	if (m_pBg == nullptr)
	{
		m_pBg = CBg::Create(BG_POS, BG_SIZE);
	}

	//BGM
//	CSound *pSound = CManager::GetSound();
//	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	// !nullcheck
	if (m_pStarManager == nullptr)
	{
		// インスタンス生成
		m_pStarManager = CStarManager::Create();
	}

	// nullcheck
	if (m_pItemManager == nullptr)
	{
		// インスタンス生成
		m_pItemManager = CItemBoxManager::GetInstance();

		// !nullcheck
		if (m_pItemManager != nullptr)
		{
			// アイテムボックスの生成
			m_pItemManager->CreateItemBox();
		}
	}

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	// 背景
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// ライトの終了処理
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// リザルト
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{
		if (m_apResult[nCount] != nullptr)
		{
			m_apResult[nCount]->Uninit();
			delete m_apResult[nCount];
			m_apResult[nCount] = nullptr;
		}
	}

	// プレイヤーの数
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{
		if (m_pCamera[nCount] != nullptr)
		{
			//カメラクラスの終了処理呼び出す
			m_pCamera[nCount]->Uninit();

			//メモリの破棄
			delete m_pCamera[nCount];

			//メモリのクリア
			m_pCamera[nCount] = nullptr;
		}

		// プレイヤーの終了処理
		if (m_pPlayer[nCount] != nullptr)
		{
			m_pPlayer[nCount]->Uninit();
			m_pPlayer[nCount] = nullptr;
		}
	}


	// nullcheck
	if (m_pStarManager != nullptr)
	{
		// 終了処理
		m_pStarManager->Uninit();
		delete m_pStarManager;
		m_pStarManager = nullptr;
	}

	// nullcheck
	if (m_pItemManager != nullptr)
	{
		// 終了処理
		m_pItemManager->Uninit();
		m_pItemManager = nullptr;
	}

	// !nullcheck
	if (CManager::GetResourceManager() != nullptr)
	{
		//サウンド情報取得
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

		// !nullcheck
		if (pSound != nullptr)
		{
			//ゲームBGM停止
		//	pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
		}
	}
	
	delete this;
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	if(m_bGameEnd)
	{
		//リザルトが生成されていなければ生成する
		if (m_apResult[0] == nullptr)
		{
			D3DXVECTOR3 pos;
			D3DXVECTOR3 size;
			for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
			{
				if (m_nPlayerNum == 2)
				{
					pos = D3DXVECTOR3(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2)*nCount , SCREEN_HEIGHT / 2, 0.0f);
				}
				else
				{
					pos = D3DXVECTOR3(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2) * (nCount % 2), SCREEN_HEIGHT / 4 + (SCREEN_HEIGHT / 2) * (nCount / 2), 0.0f);
				}
				size = SCREEN_SIZE / 2;
				m_apResult[nCount] = CResult::Create(pos, size, nCount);
			}
		}

		for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
		{
			m_apResult[nCount]->Update();
		}
	}
	else
	{
		CScene::UpdateAll();
		// プレイヤー分
		for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
		{
			// !nullcheck
			if (m_pCamera != nullptr)
			{
				//カメラクラスの更新処理
				m_pCamera[nCount]->Update();
			}
		}

		// nullcheck
		if (m_pStarManager != nullptr)
		{
			// 更新処理
			m_pStarManager->Update();
		}

		// ゲームの設定
		SetGame();
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_P))
	{
		m_bGameEnd = !m_bGameEnd;
	}
#endif
}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{
	// 背景
	if (m_pBg != nullptr)
	{
		m_pBg->Draw();
	}

	// ライト
	if (m_pLight != nullptr)
	{
		m_pLight->ShowLightInfo();
	}
	CScene::DrawAll();
	// リザルト
	for (int nCount = 0; nCount < MAX_PLAYER_NUM; nCount++)
	{
		if (m_apResult[nCount] != nullptr)
		{
			m_apResult[nCount]->Draw();
		}
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