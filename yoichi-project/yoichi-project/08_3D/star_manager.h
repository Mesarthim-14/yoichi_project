#ifndef _STAR_FACTORY_H_
#define _STAR_FACTORY_H_
//=============================================================================
//
// 星の生成クラスヘッダー [star_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "star.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define STAR_CREATE_SIZE		(8)		// スター配置のサイズ

//=============================================================================
// 前方宣言
//=============================================================================
class CStar;

//=============================================================================
// スター管理クラス
//=============================================================================
class CStarManager
{
public:
	CStarManager();																	// コンストラクタ
	~CStarManager();																// デストラクタ

	void Init(void);																// 初期化処理
	void Uninit(void);																// 終了処理
	void Update(void);																// 更新処理
	void CreateStar(void);															// アイテムクラスの生成

	CStar::STAR_COLOR_TYPE SetColorType(void);										// 色の設定
	void SetGameColor(void);														// ゲームの色の変更
	static CStarManager *Create(void);												// インスタンス生成
	void SubStarNum(int nCount, CStar::POS_NUMBER posNum);							// 星の総数を減算
	static CStar::STAR_COLOR_TYPE GetGameStarColor(void) { return m_GameColor; }	// 色の情報

private:
	std::vector<CStar*> m_pStar;													// アイテムボックスのポインタ
	bool m_bMapFlag[STAR_CREATE_SIZE][STAR_CREATE_SIZE][STAR_CREATE_SIZE];			// 座標のフラグ
	int m_nCounter;																	// カウンター

	static CStar::STAR_COLOR_TYPE m_GameColor;										// ゲームの色

};
#endif
