//=====================================================
//
// マジックハンドクラス [magichand.cpp]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "magichand.h"
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
#define DEFAULT_SIZE		(D3DXVECTOR3(200.0f, 277.5f, 0.0f))	// 基本の大きさ
#define DEFAULT_LIFE		(300)								// 基本の体力

//=====================================================
// コンストラクタ
//=====================================================
CMagichand::CMagichand(PRIORITY Priority) : CBillboard(Priority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CMagichand::~CMagichand()
{

}

//=====================================================
// インスタンス生成
//=====================================================
CMagichand * CMagichand::Create(D3DXVECTOR3 Distance, int nTexInfo, int nPlayerNum)
{
	// メモリ確保
	CMagichand *pEffect = new CMagichand;

	if (pEffect != NULL)
	{
		// 初期化処理
		pEffect->Init(CGame::GetPlayer(nPlayerNum)->GetPos() + Distance, DEFAULT_SIZE);

		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// アニメーションテクスチャ設定
		pEffect->BindTexture(pTexture->GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
		pEffect->InitAnimation(
			pTexture->GetSparateTexInfo((CTexture::SEPARATE_TEX_TYPE)nTexInfo),
			pTexture->GetSparateTexLoop((CTexture::SEPARATE_TEX_TYPE)nTexInfo));

		pEffect->SetLife(DEFAULT_LIFE);		// 体力の設定
		pEffect->SetAlpha(true);			// アルファテストの設定
		pEffect->m_nPlayerNum = nPlayerNum; // 追従させるプレイヤーの番号
		pEffect->m_Distance = Distance;		// 距離
	}

	return pEffect;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CMagichand::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CMagichand::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CMagichand::Update(void)
{
	// 更新処理
	CBillboard::Update();

	D3DXVECTOR3 pos =
		D3DXVECTOR3(CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._41,
		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._42,
		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._43) +
		D3DXVECTOR3(m_Distance.x * sinf(CGame::GetCamera(m_nPlayerNum)->Getφ() + D3DXToRadian(90.0f)),
			m_Distance.y,
			m_Distance.x * cosf(CGame::GetCamera(m_nPlayerNum)->Getφ() + D3DXToRadian(90.0f)));
	SetPos(pos);

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,
		CGame::GetCamera(m_nPlayerNum)->Getφ(),
		0.0f);
	SetRot(rot);
}

//=====================================================
// 描画処理
//=====================================================
void CMagichand::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}