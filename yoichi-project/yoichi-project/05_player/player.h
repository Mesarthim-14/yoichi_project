#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_LIFE_NUM				(100)		// 表示するライフの数
#define MOTION_KEYSET_MAX			(32)		// キーセット最大数
#define PLAYER2_POS_X				(0.0f)		// 座標
#define PLAYER2_POS_Y				(171.0f)	// 座標
#define PLAYER2_POS_Z				(500)		// 座標
#define PLAYER_SIZE_X				(1)			// サイズ
#define PLAYER_SIZE_Y				(1)			// サイズ
#define PLAYER_SIZE_Z				(1)			// サイズ
#define PLAYER_BASE_POS_Y			(200.0f)	// プレイヤーの座標のベース

#define PLAYER_COLLISION_X			(200)		// 当たり判定
#define PLAYER_COLLISION_Y			(175)		// 当たり判定
#define PLAYER_COLLISION_Z			(200)		// 当たり判定
#define WEAPON_COLLISION_X			(150)		// 武器の当たり判定
#define WEAPON_COLLISION_Y			(150)		// 武器の当たり判定
#define WEAPON_COLLISION_Z			(150)		// 武器の当たり判定
#define MAP_LIMIT					(11000)		// マップ上限

//=============================================================================
// 前方宣言
//=============================================================================
class CItem;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter
{

public:
	//=============================================================================
	// プレイヤーのパーツ番号
	//=============================================================================
	enum PARTS_NUM
	{
		PARTS_NUM_NONE = -1,
		PARTS_NUM_WAIST,			// [0]腰
		PARTS_NUM_BODY,				// [1]体
		PARTS_NUM_HEAD,				// [2]頭
		PARTS_NUM_RIGHT_SHOLDER,	// [3]右肩
		PARTS_NUM_RIGHT_UPPERARM,	// [4]右上腕
		PARTS_NUM_RIGHT_ARM,		// [5]右腕
		PARTS_NUM_RIGHT_HAND,		// [6]右手のひら
		PARTS_NUM_LEFT_SHOLDER,		// [7]左肩
		PARTS_NUM_LEFT_UPPERARM,	// [8]左上腕
		PARTS_NUM_LEFT_ARM,			// [9]左腕
		PARTS_NUM_RIGHT_THIGHS,		// [10]右腿
		PARTS_NUM_RIGHT_SHIN,		// [11]右脛
		PARTS_NUM_RIGHT_SHOE,		// [12]右足
		PARTS_NUM_LEFT_THIGHS,		// [13]左腿
		PARTS_NUM_LEFT_SHIN,		// [14]左脛
		PARTS_NUM_LEFT_SHOE,		// [15]左足
		PARTS_NUM_BACKPACK,			// [16]バックパック
		PARTS_NUM_RIGHT_WING,		// [17]右翼
		PARTS_NUM_LEFT_WING,		// [18]左翼
		PARTS_NUM_WEAPON,			// [19]武器
		PARTS_NUM_COLLISION,		// [20]当たり判定
		PARTS_NUM_ROOT,				// [21]剣の根本
		PARTS_NUM_MAX,				// モーション最大数
	};

	//=============================================================================
	// プレイヤーの状態
	//=============================================================================
	enum PLAYER_STATE
	{
		PLAYER_STATE_NONE = 0,		// 初期置
		PLAYER_STATE_NORMAL,		// 通常状態
		PLAYER_STATE_DAMAGE,		// ダメージ
		PLAYER_STATE_EXPLOSION,		// 爆発
		PLAYER_STATE_DRAW,			// 引き分け
		PLAYER_STATE_MAX			// 最大数
	};

	//=============================================================================
	//　モーション状態の列挙型
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// アイドルモーション
		MOTION_WALK,				// 歩行モーション
		MOTION_JUMP,				// ジャンプモーション
		MOTION_MAX,					// モーション最大数
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);			// コンストラクタ
	~CPlayer();													// デストラクタ

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCount);	// クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	void UpdateState(void);										// プレイヤーの状態
	void UpdateMotionState(void);								// モーション状態
	void PlayerControl(void);									// プレイヤーの制御
	void Walk(void);											// プレイヤーの歩く処理
	void Jump(void);											// ジャンプの処理
	void Death(void);											// 死んだときの処理
	void MapLimit(void);										// マップの制限
	void UseItem(void);											// アイテムの使用処理
	void AcquiredItem(CItem *pItem);							// アイテム獲得関数

	// Set関数
	void SetArmor(bool bArmor) { m_bArmor = bArmor; }			// 無敵状態の設定

	// Get関数
	CItem *GetItem(void)		{ return m_pItem; }				// アイテムのポインタ
	bool HasItem(void)			{ return m_pItem != nullptr; }	// ポインタを持っているか
	float GetBaseSpeed(void)	{ return m_fBaseSpeed; }		// 元のスピード
	bool GetArmor(void)			{ return m_bArmor; }			// 無敵状態

private:
	D3DXVECTOR3 m_rotDest;		// 回転(目標値)
	bool m_bWalk;				// 歩いているフラグ
	bool m_bDraw;				// 描画のフラグ
	bool m_bArmor;				// 無敵状態
	int m_nEndCounter;			// 死んだ後のカウンター
	int m_nNumber;				// プレイヤーの番号
	float m_fBaseSpeed;			// 元のスピード
	CItem *m_pItem;				// アイテムのポインタ
};
#endif

