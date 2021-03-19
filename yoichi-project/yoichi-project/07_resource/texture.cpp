//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
// テクスチャの名前
#define TEXTURE_NAME_EFFECT	("data/Texture/effect000.png")		// エフェクト
#define TEXTURE_NAME_FLOOR	("data/Texture/floor.jpg")			// 床
#define TEXTURE_NAME_STAR	("data/Texture/star.png")			// 星
#define TEXTURE_NAME_RING	("data/Texture/ring.png")			// 輪
#define TEXTURE_NAME_SMOKE	("data/Texture/smoke.png")			// 煙
#define TEXTURE_NAME_LACKRING	("data/Texture/lackring.png")	// 欠けた輪

// 分割テクスチャの名前
#define SEPARATE_TEX_NAME_NUMBER			("data/Texture/sharp_effect.png")		// ナンバー
#define SEPARATE_TEX_NAME_LIGHTNINGSTRIKE	("data/Texture/thunder.jpg")			// 落雷
#define SEPARATE_TEX_NAME_THUNDER			("data/Texture/thundereffect.png")		// 雷
#define SEPARATE_TEX_NAME_SHOCKWAVE			("data/Texture/shockwave.jpg")			// 衝撃波
#define SEPARATE_TEX_NAME_WIND				("data/Texture/wind.png")				// 風
#define SEPARATE_TEX_NAME_EXPLOSION			("data/Texture/explosion02.png")		// 爆発
#define SEPARATE_TEX_NAME_MAGICHANDLEFT		("data/Texture/magichand_left.png")		// マジックハンドの左
#define SEPARATE_TEX_NAME_MAGICHANDRIGHT	("data/Texture/magichand_right.png")	// マジックハンドの右


//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create(void)
{
	CTexture *pTexture = new CTexture;

	return pTexture;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EFFECT, &m_apTexture[TEXTURE_NUM_EFFECT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FLOOR, &m_apTexture[TEXTURE_NUM_FLOOR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_STAR, &m_apTexture[TEXTURE_NUM_STAR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_RING, &m_apTexture[TEXTURE_NUM_RING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LACKRING, &m_apTexture[TEXTURE_NUM_LACKRING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SMOKE, &m_apTexture[TEXTURE_NUM_SMOKE]);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_NUMBER, &m_apSeparateTexture[SEPARATE_TEX_NUMBER].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_LIGHTNINGSTRIKE, &m_apSeparateTexture[SEPARATE_TEX_LIGHTNINGSTRIKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_THUNDER, &m_apSeparateTexture[SEPARATE_TEX_THUNDER].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_SHOCKWAVE, &m_apSeparateTexture[SEPARATE_TEX_SHOCKWAVE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_WIND, &m_apSeparateTexture[SEPARATE_TEX_WIND].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_EXPLOSION, &m_apSeparateTexture[SEPARATE_TEX_EXPLOSION].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_MAGICHANDLEFT, &m_apSeparateTexture[SEPARATE_TEX_MAGICHANDLEFT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_MAGICHANDRIGHT, &m_apSeparateTexture[SEPARATE_TEX_MAGICHANDRIGHT].pSeparateTexture);

	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{ 
	// テクスチャの解放
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != NULL)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != NULL)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != NULL)
		{
			// テクスチャ情報
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}