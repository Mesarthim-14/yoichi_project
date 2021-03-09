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
#include "scene.h"

//***************************************************************************************
// 前方宣言
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CPause;
class CTimer;

//***************************************************************************************
// ゲームクラス
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame(PRIORITY Priority = PRIORITY_0);				// コンストラクタ
	~CGame();											// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	static CGame* Create(void);							// ゲーム生成情報

	// Set関数
	static void SetPlayerNum(int nPlayerNum) { m_nPlayerNum = nPlayerNum; }	// プレイヤーの数の設定

	// Get関数
	static CCamera *GetCamera(int nCount);										// カメラのポインタ情報
	static CLight *GetLight(void);											// ライトのポインタ情報
	static CPlayer *GetPlayer(int nCount);										// プレイヤーのポインタ情報
	static CPause *GetPause(void);											// ポーズ画面のポインタ情報
	static int GetPlayerNum(void) { return m_nPlayerNum; }					// プレイヤーの数

    void GameEnd(void) { m_IsGameEnd = true; }
private:	
	static CCamera *m_pCamera[MAX_PLAYER_NUM];	// カメラのポインタ	
	static CLight *m_pLight;					// ライトのポインタ
	static CMeshField *m_pMeshField;			// メッシュフィールドのポインタ
	static CBg *m_pBg;							// 背景のポインタ
	static CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// プレイヤーのポインタ
	static CPause *m_pPause;					// ポーズのポインタ
    static CTimer *m_Timer;                     // タイマーのポインタ

	LPD3DXFONT m_pFont;							// デバック用フォント
	bool m_IsGameEnd;							// ゲームのエンドフラグ
	static int m_nPlayerNum;					// プレイヤーの人数
};
#endif