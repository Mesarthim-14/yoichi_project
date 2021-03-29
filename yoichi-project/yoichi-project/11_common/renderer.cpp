//=============================================================================
//
// レンダラー処理 [renderer.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include "manager.h"
#include "camera.h"
#include "game.h"
#include "keyboard.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
//=============================================================================
// レンダリングクラスのコンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;			// Direct3Dオブジェクト
	m_fillMode = D3DFILL_SOLID;
}

//=============================================================================
// レンダリングクラスのデストラクタ
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// レンダリングクラスの初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ
	D3DDISPLAYMODE d3ddm;	//ディスプレイモード

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

	m_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3DInterface == nullptr)
	{
		// 作成失敗

		return E_FAIL;
	}


	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,				// D3DDEVTYPE_HAL：ハードウェアでラスタ化とシェーディングを行い、(座標変換と照明計算)を行う
		D3DDEVTYPE_HAL,												// D3DDEVTYPE_REF:リファレンスラスタライザ。ドライバのバグをチェックできる
		hWnd,														// D3DCREATE_PUREDEVICE                :ラスタ化、座標変換、照明計算、シェーディングを指定、上のフラグの修飾子
		D3DCREATE_HARDWARE_VERTEXPROCESSING,						// D3DCREATE_SOFTWARE_VERTEXPROCESSING：ソフトウェアによる頂点処理を指定
		&d3dpp, &m_pD3DDevice)))									// D3DCREATE_HARDWARE_VERTEXPROCESSING：ハードウェアによる頂点処理。
	{																// D3DCREATE_MIXED_VERTEXPROCESSING   ：ミックス(ソフトウェアとハードウェアの両方)による頂点処理を指定します。

		// 上記の設定が失敗したら								
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// 裏面を（左回り）をカリング
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);							// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);					// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの設定

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);		// テクスチャのU値の繰り返し
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);		// テクスチャのV値の繰り返し
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		// テクスチャ拡大時の補完設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		// テクスチャ縮小時の補完設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);		// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);		// 最初のアルファ引数（初期値）
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);		// 2番目のアルファ引数（初期値）

	return S_OK;
}

//=============================================================================
// レンダリングクラスの終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	// デバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// レンダリングクラスの更新処理
//=============================================================================
void CRenderer::Update(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	
	// ポリゴンの表示
	if (pKeyboard->GetTrigger(DIK_M))
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスへのポインタ

		switch (m_fillMode)
		{
		case D3DFILL_SOLID:
			m_fillMode = D3DFILL_WIREFRAME;
			break;
		case D3DFILL_WIREFRAME:
			m_fillMode = D3DFILL_SOLID;
			break;
		}

		pDevice->SetRenderState(D3DRS_FILLMODE, m_fillMode);
	}
}

//=============================================================================
// レンダリングクラスの描画処理
//=============================================================================
void CRenderer::Draw(void)
{
	m_pD3DDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 255, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// 選択した人数分回す
		for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
		{
			// 射影行列/ビュー/ワールド
			D3DXMATRIX matProj, matView, matWorld;
			D3DXMATRIX trans;

			if (CGame::GetCamera(nCount) != nullptr)
			{
				CCamera *pCamera = CGame::GetCamera(nCount);
				pCamera->SetCamera();

				D3DXVECTOR3 posV = pCamera->GetposV();
				D3DXVECTOR3 posR = pCamera->GetposR();

				D3DXMatrixLookAtLH(&matView,
					&posV,								// カメラ座標
					&posR,								// 注視点座標
					&D3DXVECTOR3(0.0f, 1.0f, 0.0f));	// カメラの上の向きのベクトル

				// ビューポートの設定
				SetUpViewport(nCount);

				// バックバッファ＆Ｚバッファのクリア
				m_pD3DDevice->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 255, 255, 0), 1.0f, 0);
			}

			CGame* pGame = CManager::GetGame();

			if (CManager::GetMode() == CManager::MODE_TYPE_GAME)
			{
				if (pGame != nullptr)
				{
					pGame->Draw();
				}
			}
		}

		CTitle* pTitle = CManager::GetTitle();
		CTutorial* pTutorial = CManager::GetTutorial();
		switch (CManager::GetMode())
		{
			// タイトル
		case CManager::MODE_TYPE_TITLE:
			if (CManager::GetTitle() != nullptr)
			{
				pTitle->Draw();
			}
			break;

			// チュートリアル
		case CManager::MODE_TYPE_TUTORIAL:
			if (pTutorial != nullptr)
			{
				pTutorial->Draw();
			}
			break;
		}

		if (CGame::GetPlayerNum() == 3)
		{
			// ビューポートの設定
		//	SetUpViewport(3);
		//	CScene::DrawAll();
		}

		D3DVIEWPORT9 ViewPortClear;

		ViewPortClear.X = 0;
		ViewPortClear.Y = 0;
		ViewPortClear.Width = SCREEN_WIDTH;
		ViewPortClear.Height = SCREEN_HEIGHT;
		ViewPortClear.MinZ = 0;
		ViewPortClear.MaxZ = 1;

		m_pD3DDevice->SetViewport(&ViewPortClear);

		CScene::DrawUI();

		//環境光（アンビエント）の設定
		D3DMATERIAL9 material;

		SecureZeroMemory(&material, sizeof(D3DMATERIAL9));
		material.Ambient.r = 1.0f;
		material.Ambient.g = 1.0f;
		material.Ambient.b = 1.0f;
		material.Ambient.a = 1.0f;

		m_pD3DDevice->SetMaterial(&material);
		m_pD3DDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

		//ライティングを無効にする。
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		CFade *pFade = CManager::GetFade();

		if (pFade != nullptr)
		{
			pFade->Draw();
		}

		// バックバッファとフロントバッファの入れ替え
		m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

//=============================================================================
// ビューポートの設定
//=============================================================================
bool CRenderer::SetUpViewport(int nNumber)
{
	int nPlayerNum = CGame::GetPlayerNum();

	// プレイヤーの人数
	switch (nPlayerNum)
	{
	case 1:
		// プレイヤーの番号
		switch (nNumber)
		{
		case 0:
			// ビューポートの左上座標
			m_view_port[nNumber].X = 0;
			m_view_port[nNumber].Y = 0;

			// ビューポートの幅
			m_view_port[nNumber].Width = SCREEN_WIDTH;

			// ビューポートの高さ
			m_view_port[nNumber].Height = SCREEN_HEIGHT;

			// ビューポート深度設定
			m_view_port[nNumber].MinZ = 0.0f;
			m_view_port[nNumber].MaxZ = 1.0f;

			// ビューポート設定
			if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
			{
				return false;
			}
			break;
		}
		break;

	case 2:
		// プレイヤーの番号
		switch (nNumber)
		{
		case 0:
			// ビューポートの左上座標
			m_view_port[nNumber].X = 0;
			m_view_port[nNumber].Y = 0;

			// ビューポートの幅
			m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

			// ビューポートの高さ
			m_view_port[nNumber].Height = SCREEN_HEIGHT;

			// ビューポート深度設定
			m_view_port[nNumber].MinZ = 0.0f;
			m_view_port[nNumber].MaxZ = 1.0f;

			// ビューポート設定
			if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
			{
				return false;
			}
			break;

		case 1:
			// ビューポートの左上座標
			m_view_port[nNumber].X = SCREEN_WIDTH / 2;
			m_view_port[nNumber].Y = (DWORD)0.0f;

			// ビューポートの幅
			m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

			// ビューポートの高さ
			m_view_port[nNumber].Height = SCREEN_HEIGHT;

			// ビューポート深度設定
			m_view_port[nNumber].MinZ = 0.0f;
			m_view_port[nNumber].MaxZ = 1.0f;

			// ビューポート設定
			if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
			{
				return false;
			}

			break;
		default:
			break;
		}
		break;
	case 3:
	case 4:
		// プレイヤーの番号
		switch (nNumber)
		{
		case 0:
			// ビューポートの左上座標
			m_view_port[nNumber].X = 0;
			m_view_port[nNumber].Y = 0;

			// ビューポートの幅
			m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

			// ビューポートの高さ
			m_view_port[nNumber].Height = SCREEN_HEIGHT / 2;

			// ビューポート深度設定
			m_view_port[nNumber].MinZ = 0.0f;
			m_view_port[nNumber].MaxZ = 1.0f;

			// ビューポート設定
			if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
			{
				return false;
			}
			break;

		case 1:
			// ビューポートの左上座標
			m_view_port[nNumber].X = SCREEN_WIDTH / 2;
			m_view_port[nNumber].Y = 0;

			// ビューポートの幅
			m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

			// ビューポートの高さ
			m_view_port[nNumber].Height = SCREEN_HEIGHT / 2;

			// ビューポート深度設定
			m_view_port[nNumber].MinZ = 0.0f;
			m_view_port[nNumber].MaxZ = 1.0f;

			// ビューポート設定
			if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
			{
				return false;
			}
			break;
		case 2:
			// ビューポートの左上座標
			m_view_port[nNumber].X = (DWORD)0.0f;
			m_view_port[nNumber].Y = SCREEN_HEIGHT / 2;

			// ビューポートの幅
			m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

			// ビューポートの高さ
			m_view_port[nNumber].Height = SCREEN_HEIGHT / 2;

			// ビューポート深度設定
			m_view_port[nNumber].MinZ = 0.0f;
			m_view_port[nNumber].MaxZ = 1.0f;

			// ビューポート設定
			if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
			{
				return false;
			}
			break;

		case 3:
			// ビューポートの左上座標
			m_view_port[nNumber].X = SCREEN_WIDTH / 2;
			m_view_port[nNumber].Y = SCREEN_HEIGHT / 2;

			// ビューポートの幅
			m_view_port[nNumber].Width = SCREEN_WIDTH / 2;

			// ビューポートの高さ
			m_view_port[nNumber].Height = SCREEN_HEIGHT / 2;

			// ビューポート深度設定
			m_view_port[nNumber].MinZ = 0.0f;
			m_view_port[nNumber].MaxZ = 1.0f;

			// ビューポート設定
			if (FAILED(m_pD3DDevice->SetViewport(&m_view_port[nNumber])))
			{
				return false;
			}
			break;
		default:
			break;
		}							// プレイヤーの人数の終了

		return true;
	}

	return false;

}

//=============================================================================
// デバイスの取得処理
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
