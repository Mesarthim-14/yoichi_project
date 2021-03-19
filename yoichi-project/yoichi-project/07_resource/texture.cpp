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
#define TEXTURE_NAME_EFFECT			("data/Texture/effect000.png")		// エフェクト
#define TEXTURE_NAME_FLOOR			("data/Texture/scaffold.png")		// 床
#define TEXTURE_NAME_TITLE_LOGO		("data/Texture/titlelogo001.png")	// タイトルのロゴ
#define TEXTURE_NAME_ITEM_BLUE_WING	("data/Texture/item_bluewind.png")	// アイテム青い羽根
#define TEXTURE_NAME_ITEM_RED_WING	("data/Texture/item_redwind.png")	// アイテム赤い羽根
#define TEXTURE_NAME_ITEM_BOMB		("data/Texture/item_bomb.png")		// アイテムボム
#define TEXTURE_NAME_ITEM_BARRIER	("data/Texture/item_barrier.png")	// アイテムバリア
#define TEXTURE_NAME_ITEM_THUNDER	("data/Texture/item_thunder.png")	// アイテム雷
#define TEXTURE_NAME_ITEM_MHAND		("data/Texture/item_mhand.png")		// アイテムMハンド
#define TEXTURE_NAME_ITEM_VORTEX	("data/Texture/item_vortex.png")	// アイテム渦
#define TEXTURE_NAME_SEA			("data/Texture/sea000.jpeg")		// 海
#define TEXTURE_FILE_ITEM_RESULT_1ST	("data/Texture/1st.png")		// リザルト1位
#define TEXTURE_FILE_ITEM_RESULT_2ND	("data/Texture/2nd.png")		// リザルト2位
#define TEXTURE_FILE_ITEM_RESULT_3RD	("data/Texture/3rd.png")		// リザルト3位
#define TEXTURE_FILE_ITEM_RESULT_4TH	("data/Texture/4th.png")		// リザルト4位
// 分割テクスチャの名前
#define SEPARATE_TEX_NAME_NUMBER	("data/Texture/number000.png")	// ナンバー

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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_TITLE_LOGO, &m_apTexture[TEXTURE_NUM_TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BLUE_WING, &m_apTexture[TEXTURE_NUM_ITEM_BLUE_WING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_RED_WING, &m_apTexture[TEXTURE_NUM_ITEM_RED_WING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BOMB, &m_apTexture[TEXTURE_NUM_ITEM_BOMB]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BARRIER, &m_apTexture[TEXTURE_NUM_ITEM_BARRIER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_THUNDER, &m_apTexture[TEXTURE_NUM_ITEM_THUNDER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_MHAND, &m_apTexture[TEXTURE_NUM_ITEM_MHAND]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_VORTEX, &m_apTexture[TEXTURE_NUM_ITEM_VORTEX]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SEA, &m_apTexture[TEXTURE_NUM_SEA]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_1ST, &m_apTexture[TEXTURE_NUM_RESULT_1ST]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_2ND, &m_apTexture[TEXTURE_NUM_RESULT_2ND]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_3RD, &m_apTexture[TEXTURE_NUM_RESULT_3RD]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_4TH, &m_apTexture[TEXTURE_NUM_RESULT_4TH]);
	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::Unload(void)
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

	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnload(void)
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