#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// キャラクター処理  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"
#include "xfile.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_CHARACTER_PARTS (22)	// キャラクターのパーツ数
#define MAX_KEYFRAME		(10)	// キーフレームの最大数

//=============================================================================
// 前方宣言
//=============================================================================
class CLifeBar;
class CLifeFrame;
class CMotion;

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter : public CScene
{
public:
	typedef enum
	{
		STATE_NONE = 0,		// 初期値
		STATE_APPEAR,		// 出現
		STATE_NO_ACTIVE,	// 非戦闘状態
		STATE_NORMAL,		// 通常状態
		STATE_DAMAGE,		// ダメージ状態
		STATE_MAX,			// 最大値
	}STATE;

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// コンストラクタ
	virtual ~CCharacter();											// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// 初期化処理
	virtual void Uninit();											// 終了処理
	virtual void Update();											// 更新処理
	virtual void Draw();											// 描画処理

	bool Gravity(void);												// 地面の制限
	void BodyCollision(void);										// 当たり判定
	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// モデルの生成
	void ModelAnimeUpdate(void);									// モデルアニメーション
	void Landing(float fPosY);										// 着地処理

	// 純粋仮想関数
	virtual void UpdateState(void) = 0;								// キャラクター状態
	virtual void UpdateMotionState(void) = 0;						// モーションの状態
	virtual void Death(void) = 0;									// 死んだときの処理

	// Set関数
	void SetPos(D3DXVECTOR3 pos);									// 座標の設定
	void SetPosOld(D3DXVECTOR3 posOld);								// 座標の設定
	void SetMove(D3DXVECTOR3 move);									// 移動量の設定
	void SetRot(D3DXVECTOR3 rot);									// 角度の設定
	void SetLife(int nLife);										// ライフの設定
	void SetJump(bool bJump);										// ジャンプのフラグ
	void SetLanding(bool bLanding);									// 着地の設定
	void SetRadius(float fRadius);									// 半径の設定
	void SetSpeed(float fSpeed);									// 速度の設定
	void SetStateCounter(int nStateCounter);						// 状態カウンターの設定
	void SetMotion(int nMotionState);								// モーションの設定
	void SetUseGravity(bool bUseGravity);

	// Get関数
	D3DXVECTOR3 GetPos(void) { return m_pos; }									// 現在の座標情報
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }							// 古い座標情報
	D3DXVECTOR3 GetRot(void) { return m_rot; }									// 角度情報
	D3DXVECTOR3 GetMove(void) { return m_move; }								// 移動量の情報
	int GetLife(void) { return m_nLife; }										// ライフの情報
	int GetStateCounter(void) { return m_nStateCounter; }						// 状態カウンターの情報
	float GetSpeed(void) { return m_fSpeed; }									// スピードの情報
	float GetRadius(void) { return m_fRadius; }									// 半径の情報
	CModelAnime *GetModelAnime(int nCount) { return m_apModelAnime[nCount]; }	// モーションのカウント情報
	bool GetJump(void) { return m_bJump; }										// ジャンプ
	bool GetLanding(void) { return m_bLanding; }								// 着地のフラグ
	bool GetUseGravity(void) { return m_bUseGravity; }
	STATE GetState(void) { return m_State; }									// ステート情報
	CMotion *GetMotion(void) { return m_pMotion; }								// モーションのポインタ情報

private:
	// モデル用変数
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// モデルパーツ用のポインタ
	CMotion *m_pMotion;								// モーションクラスのポインタ
	STATE m_State;									// ステート
	D3DXVECTOR3 m_pos;								// 座標
	D3DXVECTOR3 m_posOld;							// 古い座標
	D3DXVECTOR3 m_move;								// 移動量
	D3DXVECTOR3 m_rot;								// 現在の回転
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	int m_nLife;									// 体力
	int m_nMaxLife;									// ライフの最大量
	int m_nCharaNum;								// キャラクターのナンバー
	int m_nStateCounter;							// 状態のカウンター
	int m_nParts;									// パーツ数
	float m_fSpeed;									// 移動量
	float m_fAngle;									// 角度
	float m_fRadius;								// 半径
	bool m_bJump;									// ジャンプしているフラグ
	bool m_bLanding;								// 着地のフラグ
	bool m_bUseGravity;								// 重力を適用するか
	// 静的メンバ変数
	static int m_nAllNum;							// キャラクターの総数
};
#endif