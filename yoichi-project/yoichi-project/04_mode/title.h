#ifndef _TITLET_H_
#define _TITLET_H_
//=============================================================================
//
// タイトル処理 [title.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gamemode.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TITLE_UI_SIZE			(700.0f)	// UIサイズ
#define TITLE_UI_POS_X			(640.0f)	// UIのX座標
#define TITLE_UI_POS_Y			(360.0f)	// UIのY座標

#define TITLE_SIZE_X			(500.0f)	// タイトルのXサイズ
#define TITLE_SIZE_Y			(200.0f)	// タイトルのYサイズ
#define TITLE_POS_X				(640.0f)	// タイトルのX座標
#define TITLE_POS_Y				(350.0f)	// タイトルのY座標

#define TITLE_PRESS_SIZE_X		(400.0f)	// PRESSサイズ
#define TITLE_PRESS_SIZE_Y		(30.0f)		// PRESSサイズ
#define TITLE_PRESS_POS_X		(640.0f)	// PRESSのX座標
#define TITLE_PRESS_POS_Y		(260.0f)	// PRESSのY座標

#define MAX_TITLE_UI_NUM		(3)			// UIの数

//=============================================================================
//前方宣言
//=============================================================================
class CScene2D;

//=============================================================================
//リザルトクラス
//=============================================================================
class CTitle : public ICGameMode
{
public:
	CTitle();					// コンストラクタ
	~CTitle();												// デストラクタ

	static CTitle* Create(void);							// インスタンス生成

	HRESULT Init(void);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理

	void SetPlayerNum(void);								// プレイヤー数の設定
private:
	CScene2D* m_pScene2D;									// シーン2Dのポインタ
	CScene2D* m_pPress;										// シーン2Dのポインタ
	CScene2D* m_pTitleName;									// シーン2Dのポインタ
};
#endif