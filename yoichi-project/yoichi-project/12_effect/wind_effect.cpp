//=====================================================
//
// マジックハンドクラス [magichand.cpp]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "wind_effect.h"
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
#define DEFAULT_SIZE		(D3DXVECTOR3(10.0f, 200.0f, 0.0f))	// 基本の大きさ
#define DEFAULT_LIFE		(20)								// 基本の体力

//=====================================================
// コンストラクタ
//=====================================================
CWindEffect::CWindEffect(PRIORITY Priority) : CBillboard(Priority)
{

}

//=====================================================
// デストラクタ
//=====================================================
CWindEffect::~CWindEffect()
{

}

//=====================================================
// インスタンス生成
//=====================================================
CWindEffect * CWindEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Distance, int nTexInfo)
{
	// メモリ確保
	CWindEffect *pEffect = new CWindEffect;

	if (pEffect != NULL)
	{
		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// アニメーションテクスチャ設定
		pEffect->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));

		float fAngle = D3DXToRadian((float)(rand() % 360));
		D3DXVECTOR3 Createrot = D3DXVECTOR3(rot.x + D3DXToRadian(90.0f) + fAngle, rot.y + D3DXToRadian(90.0f) + fAngle, rot.z);

		// 範囲の設定
		D3DXVECTOR3 Range = D3DXVECTOR3(
			(300.0f),
			(300.0f),
			(300.0f));

		// ランダムで出現を決める
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			(float)(rand() % (int)(Range.x)) + pos.x - (Range.x / 2),
			(float)(rand() % (int)(Range.y)) + pos.y - (Range.y / 2),
			(float)(rand() % (int)(Range.z)) + pos.z - (Range.z / 2));

		pEffect->SetPos(TargetPos);

		pEffect->SetRot(rot);
		pEffect->SetSize(DEFAULT_SIZE);
		pEffect->SetSizeBase(DEFAULT_SIZE);
		pEffect->SetLife(DEFAULT_LIFE);		// 体力の設定
		pEffect->SetAlpha(true);			// アルファテストの設定

		// 初期化処理
		pEffect->Init();
	}

	return pEffect;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CWindEffect::Init()
{
	// 初期化処理
	CBillboard::Init();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CWindEffect::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CWindEffect::Update(void)
{
	// 更新処理
	CBillboard::Update();

	D3DXCOLOR col = GetColor();
	col.a -= 0.1f;
	SetColor(col);

	//D3DXVECTOR3 pos =
	//	D3DXVECTOR3(CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._41,
	//		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._42,
	//		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._43) +
	//	D3DXVECTOR3(m_Distance.x * sinf(CGame::GetCamera(m_nPlayerNum)->GetHorizontal() + D3DXToRadian(90.0f)),
	//		m_Distance.y,
	//		m_Distance.x * cosf(CGame::GetCamera(m_nPlayerNum)->GetHorizontal() + D3DXToRadian(90.0f)));
	//SetPos(pos);

	//D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,
	//	CGame::GetCamera(m_nPlayerNum)->GetHorizontal(),
	//	0.0f);
	//SetRot(rot);
}

//=====================================================
// 描画処理
//=====================================================
void CWindEffect::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}