//=============================================================================
//
// リソースマネージャー処理 [resource_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "resource_manager.h"
#include "texture.h"
#include "xfile.h"
#include "sound.h"

//=============================================================================
// static初期化宣言
//=============================================================================
CResourceManager *CResourceManager::m_pResourceManager = NULL;	// 自身のポインタ

//=============================================================================
// コンストラクタ
//=============================================================================
CResourceManager::CResourceManager()
{
	m_pTexture = NULL;		// テクスチャのポインタ
	m_pXFile = NULL;		// Xファイルのポインタ
	m_pSound = NULL;		// サウンドのポインタ
}

//=============================================================================
// デストラクタ
//=============================================================================
CResourceManager::~CResourceManager()
{
	// アンロード処理
	UnloadAll();
	// nullcheck
	if (m_pTexture != NULL)
	{
		// テクスチャポインタ開放
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// nullcheck
	if (m_pXFile != NULL)
	{
		// Xファイルポインタ開放
		delete m_pXFile;
		m_pXFile = NULL;
	}

	// nullcheck
	if (m_pSound != NULL)
	{
		// 終了処理
		m_pSound->Uninit();

		// サウンドポインタ開放
		delete m_pSound;
		m_pSound = NULL;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResourceManager::Init(void)
{
	// nullcheck
	if (m_pTexture == NULL)
	{
		// テクスチャのインスタンス生成
		m_pTexture = CTexture::Create();
	}

	// nullcheck
	if (m_pXFile == NULL)
	{
		// テクスチャのインスタンス生成
		m_pXFile = CXfile::Create();
	}

	// nullcheck
	if (m_pSound == NULL)
	{
		// サウンドのインスタンス生成
		m_pSound = CSound::Create();
	}

	return S_OK;
}

//=============================================================================
// ロード処理
//=============================================================================
void CResourceManager::LoadAll(void)
{
	// !nullcheck
	if (m_pTexture != NULL)
	{
		// テクスチャロード
		m_pTexture->Load();
		m_pTexture->SeparateTexLoad();
	}

	// !nullcheck
	if (m_pXFile != NULL)
	{
		// モデルのファイルの名前のセット
		m_pXFile->SetFileName();

		// モデルロード
		m_pXFile->ModelLoad();

		// 階層構造のファイル読み込み
		m_pXFile->HierarchyReadFile();

		// 階層構造のモデル読み込み
		m_pXFile->HierarchyModelLoad();
	}
}

//=============================================================================
// アンロード処理
//=============================================================================
void CResourceManager::UnloadAll(void)
{
	// !nullcheck
	if (m_pTexture != NULL)
	{
		// テクスチャアンロード
	}

	// !nullcheck
	if (m_pXFile != NULL)
	{
		// モデルの破棄
		m_pXFile->ModelUnLoad();

		// 階層構造のモデルの破棄
		m_pXFile->HierarchyModelUnLoad();
	}
}

//=============================================================================
// インスタンス取得関数
//=============================================================================
CResourceManager * CResourceManager::GetInstance(void)
{
	if (m_pResourceManager == NULL)
	{
		// メモリ確保
		m_pResourceManager = new CResourceManager;

		// nullcheck
		if (m_pResourceManager != NULL)
		{
			// 初期化処理
			m_pResourceManager->Init();
		}
	}

	return m_pResourceManager;
}