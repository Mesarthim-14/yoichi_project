//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include <stdio.h>
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "particle.h"
#include "effect_factory.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "character.h"
#include "motion.h"
#include "item.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED					(20.0f)				// プレイヤーの移動量
#define PLAYER_JUMP						(17.0f)				// ジャンプの処理
#define STICK_SENSITIVITY				(50.0f)				// スティック感度
#define PLAYER_ROT_SPEED				(0.1f)				// キャラクターの回転する速度
#define PLAYER_RADIUS					(200.0f)			// 半径の大きさ
#define PLAYER_PARTS					(22)				// プレイヤーのパーツ数
#define GAME_END_FLAME					(100)				// ゲームが終わるフレーム

// エフェクトパーツ
#define BLADE_EFFECT_INTER				(190)				// 刀身のパーティクルの間隔
#define WEAPON_TIP_NUM					(20)				// 剣先のパーツ番号
#define WEAPON_ROOT_NUM					(21)				// 剣の根元のパーツ番号

//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCount)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// 番号の設定
	pPlayer->m_nNumber = nCount;

	// 初期化処理
	pPlayer->Init(pos, size);

	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bWalk = false;
	m_bDraw = true;
	m_nEndCounter = 0;
	m_pItem = NULL;
	m_fBaseSpeed = 0.0f;
	m_bArmor = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル情報取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != NULL)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	// 初期化処理
	CCharacter::Init(pos, rot);												// 座標　角度
	SetRadius(PLAYER_RADIUS);												// 半径の設定
	SetSpeed(PLAYER_SPEED);													// 速度の設定

	m_fBaseSpeed = PLAYER_SPEED;		// 元のスピード保持

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 親クラスの更新処理
	CCharacter::Update();

	// 座標代入
	D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
	SetPosOld(pos);				// 古い座標保存

	// プレイヤーの状態
	UpdateState();

	// モーション状態
	UpdateMotionState();

	// プレイヤーの制御
	PlayerControl();

	// アイテムが使われていたら
	if (m_pItem != nullptr)
	{
		// アイテムの削除フラグが立ったら
		if (m_pItem->GetEnd() == true)
		{
			m_pItem->Uninit();
			m_pItem = nullptr;
		}
	}

	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// 角度の設定
	SetRot(rot);

	// マップの制限
	MapLimit();

	// 体力が0になったら
	if (GetLife() <= 0)
	{
		// 死んだとき
		Death();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer::UpdateState(void)
{
	switch (GetState())
	{
	case STATE_NORMAL:
		// 通常状態

		break;

	case STATE_DAMAGE:
		break;
	}
}

//=============================================================================
// モーション状態
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	// モーション情報
	switch (MotionState)
	{
	case 0:
		break;
	default:
		break;
	}
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer::PlayerControl()
{
	// プレイヤーの移動処理
	Walk();

	// ジャンプの処理
	Jump();

	// アイテムの使用
	UseItem();
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);				// ジョイパッドの取得
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// カメラ角度取得
	float fAngle = CGame::GetCamera(m_nNumber)->Getφ();
	D3DXVECTOR3 pos = GetPos();

	//入力が存在する
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		//ダメージを受けていないときのみ移動する
		bool bJump = GetJump();

		//ジャンプしていないとき
		if (bJump == false)
		{
			// 歩き状態にする
			m_bWalk = true;

			//歩行モーションの再生
			SetMotion(MOTION_WALK);
		}

		DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);				// ジョイパッドの取得
		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// コントローラの角度
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// コントローラの角度
		float fAngle = CGame::GetCamera(m_nNumber)->Getφ();				// カメラの角度

		// 移動量設定
		pos.x += sinf(fAngle + (fAngle2))* GetSpeed();
		pos.z += cosf(fAngle + (fAngle2))* GetSpeed();

		// 角度の設定
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{
		// 歩いていたら
		if (m_bWalk == true)
		{
			//待機モーションを再生
			SetMotion(MOTION_IDOL);
			m_bWalk = false;
		}
	}

	// 前に移動
	if (pKeyboard->GetPress(DIK_W))
	{
		// 歩きモーション
		SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x -= sinf((CGame::GetCamera(m_nNumber)->Getφ()))*GetSpeed();
		pos.z -= cosf((CGame::GetCamera(m_nNumber)->Getφ()))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Getφ();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Getφ(), GetRot().z));
	}
	// 後ろに移動
	if (pKeyboard->GetPress(DIK_S))
	{
		// 歩きモーション
		SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x += sinf((CGame::GetCamera(m_nNumber)->Getφ()))*GetSpeed();
		pos.z += cosf((CGame::GetCamera(m_nNumber)->Getφ()))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Getφ();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Getφ() + D3DXToRadian(-180.0f), GetRot().z));

	}
	// 左に移動
	if (pKeyboard->GetPress(DIK_A))
	{
		// 歩きモーション
		SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x += sinf((CGame::GetCamera(m_nNumber)->Getφ() + D3DXToRadian(90.0f)))*GetSpeed();
		pos.z += cosf((CGame::GetCamera(m_nNumber)->Getφ() + D3DXToRadian(90.0f)))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Getφ();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Getφ() + D3DXToRadian(-90.0f), GetRot().z));

	}
	// 右に移動
	if (pKeyboard->GetPress(DIK_D))
	{
		// 歩きモーション
		SetMotion(MOTION_WALK);

		// 移動量・角度の設定
		pos.x += sinf((CGame::GetCamera(m_nNumber)->Getφ() + D3DXToRadian(-90.0f)))*GetSpeed();
		pos.z += cosf((CGame::GetCamera(m_nNumber)->Getφ() + D3DXToRadian(-90.0f)))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Getφ();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Getφ() + D3DXToRadian(90.0f), GetRot().z));

	}

	// 座標設定
	SetPos(pos);

	// 古い座標取得
	D3DXVECTOR3 OldPos = GetOldPos();

	// 動いていなかったら
	if (OldPos == pos)
	{
		// 通常モーション
		SetMotion(MOTION_IDOL);
	}
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::Jump(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACEキーを押したとき・コントローラのYを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nNumber) && GetJump() == false
		|| pKeyboard->GetTrigger(DIK_SPACE) && GetJump() == false)
	{
		// 移動量設定
		D3DXVECTOR3 move = GetMove();
		move.y = PLAYER_JUMP;
		SetMove(move);
		SetJump(true);
		m_bWalk = false;

		//ジャンプモーションの再生
		SetMotion(MOTION_JUMP);
		SetLanding(false);
	}
}

//=============================================================================
// 死んだときの処理
//=============================================================================
void CPlayer::Death(void)
{
	m_bDraw = false;
}

//=============================================================================
// 範囲外に行かないようにする処理
//=============================================================================
void CPlayer::MapLimit(void)
{
	//右
	if (GetPos().x > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(MAP_LIMIT, GetPos().y, GetPos().z));
	}

	//左
	if (GetPos().x <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(-MAP_LIMIT, GetPos().y, GetPos().z));
	}

	//奥
	if (GetPos().z > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, MAP_LIMIT));
	}

	//手前
	if (GetPos().z <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, -MAP_LIMIT));
	}
}

//=============================================================================
// アイテムの使用処理
//=============================================================================
void CPlayer::UseItem(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACEキーを押したとき・コントローラのYを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nNumber)
		|| pKeyboard->GetTrigger(DIK_I))
	{
		// !nullcheck
		if (m_pItem != nullptr)
		{
			if (m_pItem->GetUse() == false)
			{
				// アイテムを使う
				m_pItem->SetItem();
			}
		}
	}
}

//=============================================================================
// アイテムのデータを渡す
//=============================================================================
void CPlayer::AcquiredItem(CItem *pItem)
{
	// nullcheck
	if (m_pItem == nullptr)
	{
		m_pItem = pItem;
	}
}