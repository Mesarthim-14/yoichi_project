//=============================================================================
//
// リザルトクラス [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"

//=============================================================================
//リザルトクラスのコンストラクタ
//=============================================================================
CResult::CResult(PRIORITY Priority) : CScene(Priority)
{
	//メンバ変数のクリア
	m_pScene2D = NULL;
}

//=============================================================================
//リザルトクラスのデストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
//リザルトクラスのクリエイト処理
//=============================================================================
CResult * CResult::Create(void)
{
	//リザルトクラスのポインタ変数
	CResult *pResult = new CResult;

	//メモリが確保できていたら
	if (pResult != NULL)
	{
		//初期化処理呼び出し
		pResult->Init(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f));
	}

	return pResult;
}

//=============================================================================
//リザルトクラスの初期化処理
//=============================================================================
HRESULT CResult::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//2Dオブジェクトの生成
	m_pScene2D = CScene2D::Create(pos, size);
	if (m_pScene2D != NULL)
	{
		m_pScene2D->BindTexture(NULL);
	}

	return E_NOTIMPL;
}

//=============================================================================
//リザルトクラスの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
//リザルトクラスの更新処理
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

//=============================================================================
//リザルトクラスの描画処理
//=============================================================================
void CResult::Draw(void)
{
}
