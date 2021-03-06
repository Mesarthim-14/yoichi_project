//=============================================================================
//
// UIクラス処理 [ui.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "ui.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CUi::CUi(PRIORITY Priority) : CScene2D(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CUi::~CUi()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CUi * CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// メモリ確保
	CUi *pUi = new CUi;

	// nullcheck
	if (pUi != NULL)
	{
		pUi->SetPos(pos);
		pUi->SetSize(size);
		// 初期化処理
		pUi->Init();
	}

	return pUi;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUi::Init(void)
{
	// 初期化処理
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUi::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUi::Update(void)
{
	// 更新処理
	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CUi::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}