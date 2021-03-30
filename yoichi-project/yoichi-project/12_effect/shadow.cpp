//=====================================================
//
// シャドウクラス [shadow.cpp]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"

//=====================================================
// マクロ定義
//=====================================================
#define DEFAULT_SIZE		(D3DXVECTOR3(150.0f, 150.0f, 0.0f))	// 基本の大きさ
#define DEFAULT_ROT			(D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f))	// 基本の角度
#define DEFAULT_COLOR		(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f))	// 基本の色

//=====================================================
// コンストラクタ
//=====================================================
CShadow::CShadow(PRIORITY Priority) : CBillboard(Priority)
{
	m_nPlayerNum = 0;
}

//=====================================================
// デストラクタ
//=====================================================
CShadow::~CShadow()
{

}

//=====================================================
// インスタンス生成
//=====================================================
CShadow * CShadow::Create(int nTexInfo, int nPlayerNum)
{
	// メモリ確保
	CShadow *pEffect = new CShadow;

	if (pEffect != NULL)
	{
		CTexture *pTexture = GET_TEXTURE_PTR;

		// アニメーションテクスチャ設定
		pEffect->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));

		pEffect->SetSize(DEFAULT_SIZE);
		pEffect->SetRot(DEFAULT_ROT);
		pEffect->SetColor(DEFAULT_COLOR);
		pEffect->SetAlpha(true);			// アルファテストの設定
		pEffect->m_nPlayerNum = nPlayerNum; // 追従させるプレイヤーの番号

		// 初期化処理
		pEffect->Init();

	}

	return pEffect;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CShadow::Init()
{
	// 初期化処理
	CBillboard::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CShadow::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CShadow::Update(void)
{
	// 更新処理
	CBillboard::Update();

	// 座標の更新
	D3DXVECTOR3 pos =
		D3DXVECTOR3(CGame::GetPlayer(m_nPlayerNum)->GetPos().x,
			0.0f,
			CGame::GetPlayer(m_nPlayerNum)->GetPos().z);
	SetPos(pos);

	// 色の更新
	D3DXCOLOR col = GetColor();
	float fAlphaSub = (CGame::GetPlayer(m_nPlayerNum)->GetPos().y - pos.y) / 2000.0f;
	col.a = 1.0f - fAlphaSub;
	SetColor(col);
}

//=====================================================
// 描画処理
//=====================================================
void CShadow::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}