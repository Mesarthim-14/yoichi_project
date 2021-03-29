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
#define TEXTURE_NAME_KIRAKIRA	("data/Texture/kirakira.png")	// キラキラ
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
#define TEXTURE_FILE_SIDE_LINE          ("data/Texture/side_line.png")       // 横線
#define TEXTURE_FILE_VERTICAL_LLINE     ("data/Texture/Vertical_lline.png")  // 縦線
#define TEXTURE_FILE_FRAME              ("data/Texture/frame.png")           // 中央の枠
#define TEXTURE_FILE_POINT_UI           ("data/Texture/pointup.png")         // ポイントアップのテクスチャ

// 分割テクスチャの名前
#define SEPARATE_TEX_NAME_NUMBER	("data/Texture/number000.png")	// ナンバー
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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_TITLE_LOGO, &m_apTexture[TEXTURE_NUM_TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BLUE_WING, &m_apTexture[TEXTURE_NUM_ITEM_BLUE_WING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_RED_WING, &m_apTexture[TEXTURE_NUM_ITEM_RED_WING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BOMB, &m_apTexture[TEXTURE_NUM_ITEM_BOMB]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BARRIER, &m_apTexture[TEXTURE_NUM_ITEM_BARRIER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_THUNDER, &m_apTexture[TEXTURE_NUM_ITEM_THUNDER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_MHAND, &m_apTexture[TEXTURE_NUM_ITEM_MHAND]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_VORTEX, &m_apTexture[TEXTURE_NUM_ITEM_VORTEX]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SEA, &m_apTexture[TEXTURE_NUM_SEA]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_STAR, &m_apTexture[TEXTURE_NUM_STAR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_RING, &m_apTexture[TEXTURE_NUM_RING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LACKRING, &m_apTexture[TEXTURE_NUM_LACKRING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SMOKE, &m_apTexture[TEXTURE_NUM_SMOKE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_KIRAKIRA, &m_apTexture[TEXTURE_NUM_KIRAKIRA]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_1ST, &m_apTexture[TEXTURE_NUM_RESULT_1ST]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_2ND, &m_apTexture[TEXTURE_NUM_RESULT_2ND]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_3RD, &m_apTexture[TEXTURE_NUM_RESULT_3RD]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_4TH, &m_apTexture[TEXTURE_NUM_RESULT_4TH]);

    D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_SIDE_LINE, &m_apTexture[TEXTURE_NUM_SIDE_LINE]);
    D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_VERTICAL_LLINE, &m_apTexture[TEXTURE_NUM_VERTICAL_LLINE]);
    D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_FRAME, &m_apTexture[TEXTURE_NUM_FRAME]);
    D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_POINT_UI, &m_apTexture[TEXTURE_NUM_POINT_UP]);

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