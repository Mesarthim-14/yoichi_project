#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// ゲームの処理 [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "manager.h"
#include "gamemode.h"
//***************************************************************************************
// マクロ定義
//***************************************************************************************
#define STAGE_LIMIT_Y		(-2000.0f)
#define TIME_RETURN_TITLE	(120)

//***************************************************************************************
// 前方宣言
//***************************************************************************************
class CCamera;
class CLight;
class CPlayer;
class CPause;
class CItemBoxManager;
class CStarManager;
class CStageMap;
class CTime_UI;
class CResult;
class CGame_UI;

//***************************************************************************************
// ゲームクラス
//***************************************************************************************
class CGame : public ICGameMode
{
public:
	CGame();														// コンストラクタ
	~CGame();														// デストラクタ

	HRESULT Init();													// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	static CGame* Create(void);										// ゲーム生成情報
	void SetResultUi(void);											// リザルトのUiを設定
	void SetRanking(vector<int> *apStarNum, vector<int> *apRank);	// ランキングの設定

	// Set関数
	static void SetPlayerNum(int nPlayerNum) { m_nPlayerNum = nPlayerNum; }	// プレイヤーの数の設定

	// Get関数
	static CCamera *GetCamera(int nCount);										// カメラのポインタ情報
	static CLight *GetLight(void);												// ライトのポインタ情報
	static CPlayer *GetPlayer(int nCount);										// プレイヤーのポインタ情報
	static CPause *GetPause(void);												// ポーズ画面のポインタ情報
	static int GetPlayerNum(void)					{ return m_nPlayerNum; }	// プレイヤーの数
	static CItemBoxManager *GetItemManager(void)	{ return m_pItemManager; }	// リソースマネージャのポインタ
	CStageMap *GetStageMap(void)					{ return m_pStageMap; }		// マップの情報

    void GameEnd(void) { m_bGameEnd = true; }  // ゲーム終了
private:
	static CCamera *m_pCamera[MAX_PLAYER_NUM];	// カメラのポインタ	
	static CLight *m_pLight;					// ライトのポインタ
	static CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// プレイヤーのポインタ
	static CItemBoxManager *m_pItemManager;		// アイテムマネージャのポインタ
	static CResult *m_apResult[MAX_PLAYER_NUM];	// リザルトのポインタ
	CStarManager *m_pStarManager;				// 星生成クラスのポインタ
	CStageMap *m_pStageMap;						// マップの生成
	static CPause *m_pPause;					// ポーズのポインタ
    static CTime_UI *m_pTimeUI;                 // タイマーへのポインタ
    static CGame_UI *m_pGameUI;                 // ゲームUI


	LPD3DXFONT m_pFont;							// デバック用フォント
	int m_nTimeCounter;							// ゲームのカウンター
	bool m_bGameEnd;							// ゲームのエンドフラグ
	static int m_nPlayerNum;					// プレイヤーの人数
	int m_nTimer;								// タイトル画面に戻るまでのタイマー

};
#endif