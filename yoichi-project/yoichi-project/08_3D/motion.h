#ifndef _MOTION_H_
#define _MOTION_H_
//=============================================================================
//
// モーションクラスヘッダー [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "xfile.h"
#include "modelanime.h"

//=============================================================================
// モーションクラス
//=============================================================================
class CMotion
{
public:
	//=============================================================================
	//　各要素のキー情報
	//=============================================================================
	struct KEY
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	};

	//=============================================================================
	//	キー情報の構造体
	//=============================================================================
	struct KEY_INFO
	{
		int nFrame;						// フレーム数
		KEY aKey[MAX_MODEL_PARTS];		// 各パーツのキー情報
	};

	//=============================================================================
	//　モーション情報の構造体
	//=============================================================================
	struct Motion_Info
	{
		bool bLoop;				// ループするかどうか
		int nNumKey;			// キー数
		KEY_INFO aKeyInfo[20];	// キー情報
	};

	CMotion();		// コンストラクタ
	~CMotion();		// デストラクタ

	static CMotion *Create(char *pFileName);

	HRESULT Init(void);															// 初期化処理
	void Uninit(void);															// 終了処理
	void Update(void);															// 更新処理

	void SetMotion(int nMotion, int nMaxParts, CModelAnime **pModelAnime);		// モーションの設定
	void UpdateMotion(int nMaxParts, CModelAnime **pModelAnime);				// モーションの更新
	HRESULT ReadMotionFile(char *pFileName);									// モーションデータを読み込む

	// Get関数
	int GetMotionState(void) { return m_nMotionState; }		// モーション状態

private:
	// モーション用変数
	Motion_Info m_Motion[30];		// モーション情報
	KEY_INFO *m_apKeyInfo;			// キー情報のポインタ
	int m_nMotionState;				// モーションの状態
	int m_nNumKey;					// キーの総数
	int m_nCountMotion;				// モーションカウンター
	int m_nMotionInterval;			// モーションのインターバル
	int m_nKey;						// 現在キーのNo
	bool m_bMotionPlaing;			// モーションの再生

	D3DXVECTOR3 m_diffPos;			// 変更座標
	D3DXVECTOR3 m_diffRot;			// 変更角度
};

#endif 