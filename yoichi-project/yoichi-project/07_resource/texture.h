#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// テクスチャの管理ヘッダー [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
//クラス宣言
//=============================================================================
class CTexture
{
public:
	// テクスチャの番号の列挙型
	enum TEXTURE_TYPE
	{
		TEXTURE_NUM_NONE = -1,			// 初期値
		TEXTURE_NUM_EFFECT,				// 炎
		TEXTURE_NUM_FLOOR,				// 床テクスチャ
		TEXTURE_NUM_TITLE_LOGO,			// タイトルロゴ
		TEXTURE_NUM_ITEM_BLUE_WING,		// アイテム青い羽根
		TEXTURE_NUM_ITEM_RED_WING,		// アイテム赤い羽
		TEXTURE_NUM_ITEM_BOMB,			// アイテム爆弾
		TEXTURE_NUM_ITEM_BARRIER,		// アイテムバリア
		TEXTURE_NUM_ITEM_THUNDER,		// アイテム雷
		TEXTURE_NUM_ITEM_MHAND,			// アイテムMハンド
		TEXTURE_NUM_ITEM_VORTEX,		// アイテム渦
		TEXTURE_NUM_SEA,				// 海
		TEXTURE_NUM_RESULT_1ST,			// リザルト1位
		TEXTURE_NUM_RESULT_2ND,			// リザルト1位
		TEXTURE_NUM_RESULT_3RD,			// リザルト1位
		TEXTURE_NUM_RESULT_4TH,			// リザルト1位
		TEXTURE_NUM_STAR,			// 星
		TEXTURE_NUM_RING,			// 輪
		TEXTURE_NUM_LACKRING,		// 欠けた輪
		TEXTURE_NUM_SMOKE,			// 煙
		TEXTURE_NUM_KIRAKIRA,		// キラキラ
		TEXTURE_NUM_MAX
	};

	// アニメーションを行うテクスチャの列挙型
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// 初期値
		SEPARATE_TEX_NUMBER,			// コンボのナンバー
		SEPARATE_TEX_LIGHTNINGSTRIKE,	// 落雷のテクスチャ
		SEPARATE_TEX_THUNDER,			// 雷のテクスチャ
		SEPARATE_TEX_SHOCKWAVE,			// 衝撃波のテクスチャ
		SEPARATE_TEX_WIND,				// 風のテクスチャ
		SEPARATE_TEX_EXPLOSION,			// 爆発のテクスチャ
		SEPARATE_TEX_MAGICHANDLEFT,		// マジックハンドの左のテクスチャ
		SEPARATE_TEX_MAGICHANDRIGHT,	// マジックハンドの右のテクスチャ
		SEPARATE_TEX_MAX				// 最大値
	};

	// アニメーションを行うテクスチャの構造体情報
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// 分割テクスチャへのポインタ
		SEPARATE_TEX_TYPE type;						// テクスチャの種類
		D3DXVECTOR2 m_TexInfo;						// テクスチャの分割数、速さ
		bool bLoop;									// ループするか
	};

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	static CTexture *Create(void);												// インスタンス生成

	 HRESULT Load(void);														// テクスチャロード
	 void Unload(void);															// テクスチャアンロード
	 HRESULT SeparateTexLoad(void);												// 分割テクスチャロード
	 void SeparateTexUnload(void);												// 分割テクスチャアンロード

	 LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);						// テクスチャの情報

	 LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);		// 分割テクスチャ情報
	 D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);				// 分割テクスチャ　UVの枚数取得
	 bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ループするか
private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];							// テクスチャのポインタ

	// 分割テクスチャの構造体
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, CTexture::SEPARATE_TEX_NUMBER, D3DXVECTOR2(5, 4), false,
		nullptr, CTexture::SEPARATE_TEX_LIGHTNINGSTRIKE, D3DXVECTOR2(6, 5), false,
		nullptr, CTexture::SEPARATE_TEX_THUNDER, D3DXVECTOR2(10, 5), false,
		nullptr, CTexture::SEPARATE_TEX_SHOCKWAVE, D3DXVECTOR2(5, 3), false,
		nullptr, CTexture::SEPARATE_TEX_WIND, D3DXVECTOR2(30, 1), false,
		nullptr, CTexture::SEPARATE_TEX_WIND, D3DXVECTOR2(8, 5), false,
		nullptr, CTexture::SEPARATE_TEX_MAGICHANDLEFT, D3DXVECTOR2(2, 5), true,
		nullptr, CTexture::SEPARATE_TEX_MAGICHANDRIGHT, D3DXVECTOR2(2, 5), true,
	};
	// 分割テクスチャのポインタ
};
#endif
