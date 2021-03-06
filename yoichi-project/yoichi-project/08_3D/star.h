#ifndef _STAR_H_
#define _STAR_H_
//=====================================================
//
// 星クラスヘッダー [star.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"

//=====================================================
// マクロ定義
//=====================================================
#define STAR_COLOR_RED			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))						// 赤
#define STAR_COLOR_BLUE			(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))						// 青
#define STAR_COLOR_YELLOW		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))						// 黄
#define STAR_COLOR_GREEN		(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))						// 緑

//=====================================================
// 前方宣言
//=====================================================
class CStarManager;

//=====================================================
// スタークラス
//=====================================================
class CStar : public CBillboard
{
public:
	// 星の色
	enum STAR_COLOR_TYPE
	{
		STAR_COLOR_TYPE_NONE = -1,	// 初期値
		STAR_COLOR_TYPE_RED,		// 赤
		STAR_COLOR_TYPE_BLUE,		// 青
		STAR_COLOR_TYPE_YELLOW,		// 黄
		STAR_COLOR_TYPE_GREEN,		// 緑
		STAR_COLOR_TYPE_MAX,
	};

	// 座標番号保持
	struct POS_NUMBER
	{
		int nNumX;
		int nNumY;
		int nNumZ;
	};

	CStar(PRIORITY Priority = PRIORITY_1);				// コンストラクタ
	~CStar();													// デストラクタ

	HRESULT Init(void);								// 初期化処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	bool Collision(void);										// 当たり判定

	static CStar *Create(D3DXVECTOR3 pos, POS_NUMBER posNum);				// 星の生成

	void SetColorType(void);	// 色の種類設定

	POS_NUMBER GetPosNumber(void) { return m_PosNumber; }		// 座標番号の情報

private:
	POS_NUMBER m_PosNumber;										// 座標番号
	STAR_COLOR_TYPE m_ColorType;					// 色の設定
};

#endif