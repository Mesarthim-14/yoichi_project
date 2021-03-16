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
#define PLAYER_FLY_SPEED				(30.0f)				// 飛行時のプレイヤーの移動量
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
	m_bFly = false;
	m_bDraw = true;
	m_nEndCounter = 0;
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
	// メモリ確保
	for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
	{
		// !nullcheck
		if (m_apItem[nCount] != nullptr)
		{
			// 終了処理
			m_apItem[nCount]->Uninit();
			m_apItem[nCount] = nullptr;
		}
	}

	// 配列があれば
	if (m_apItem.size() != NULL)
	{
		// 配列のクリア
		m_apItem.clear();
	}

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

	// メモリ確保
	for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
	{
		// !nullcheck
		if (m_apItem[nCount] != nullptr)
		{
			// アイテムの削除フラグが立ったら
			if (m_apItem[nCount]->GetEnd() == true)
			{
				// 配列を空にする
				m_apItem.erase(m_apItem.begin() + nCount);
			}
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
	if (m_bFly)
	{
		// 飛行処理
		Fly();
	}
	else
	{
		// プレイヤーの移動処理
		Walk();

		// ジャンプの処理
		Jump();
	}

	// アイテムの使用
	UseItem();
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();				// キーボード取得
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);					// ジョイパッドの取得
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();	// サウンドポインタ取得
	float fSpeed = GetSpeed();											// 速度取得
	float fCameraAngle = CGame::GetCamera(m_nNumber)->Getφ();			// カメラ角度取得
	float fMoveAngle = 0.0f; //移動角度
	D3DXVECTOR3 rot = GetRot();											// 回転取得
	D3DXVECTOR3 pos = GetPos();											// 座標取得
	D3DXMATRIX mtxRot;
	ZeroMemory(&mtxRot, sizeof(mtxRot));

	m_rotDest.x = 0.0f;

	// 移動入力がされていれば
	if (pKeyboard->GetPress(DIK_W) || pKeyboard->GetPress(DIK_A) || pKeyboard->GetPress(DIK_S) || pKeyboard->GetPress(DIK_D) || js.lX != 0.0f || js.lY != 0.0f)
	{
		fMoveAngle = InputToAngle();
		m_bWalk = true;
	}
	else
	{
		m_bWalk = false;
	}

	if (m_bWalk)
	{	// 歩いている時
		if (!GetJump())
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);
		}
		// 移動
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, -PLAYER_SPEED);
		fMoveAngle += fCameraAngle;
		m_rotDest.y = fMoveAngle;
		D3DXMatrixRotationY(&mtxRot, fMoveAngle);
		D3DXVec3TransformNormal(&move, &move, &mtxRot);
		pos += move;
	}
	else
	{	// 歩いていない時
		// 通常モーション
		SetMotion(MOTION_IDOL);
	}

	// 座標設定
	SetPos(pos);

}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::Jump(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACEキーを押したとき・コントローラのYを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nNumber)
		|| pKeyboard->GetTrigger(DIK_SPACE))
	{
		if (GetJump())
		{
			m_rotDest.x -= D3DXToRadian(90.0f);
			SetMove(ZeroVector3);
			m_bFly = true;
		}
		else
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
}

//=============================================================================
// 飛行処理
//=============================================================================
void CPlayer::Fly(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボードを取得
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);		// ジョイパッドを取得
	D3DXVECTOR3 move = ZeroVector3;							// 移動量
	D3DXMATRIX mtxRot;										// 回転計算用行列
	CCamera* pCamera = CGame::GetCamera(m_nNumber);
	// 重力を無効化
	if (GetUseGravity())
	{
		SetUseGravity(false);
	}
	
	//プレイヤーの上方向に移動
	move = D3DXVECTOR3(0.0f, PLAYER_FLY_SPEED, 0.0f);

	//コントローラーの入力を変換
	m_rotDest.y += D3DXToRadian(js.lX / 1000);
	m_rotDest.x += D3DXToRadian(js.lY / 1000);

	//コントローラー入力を利用してプレイヤーの向きを変換
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotDest.y, m_rotDest.x, m_rotDest.z);
	D3DXVec3TransformNormal(&move, &move, &mtxRot);

	// 移動量を足す
	SetPos(GetPos() + move);
	
	// 入力された角度
	if (pKeyboard->GetTrigger(DIK_SPACE)||CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nNumber))
	{
		m_bFly = false;
		if (!GetUseGravity())
		{
			SetUseGravity(true);
		}
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
	D3DXVECTOR3 pos = GetPos();

	if (pos.x > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(MAP_LIMIT, pos.y, pos.z));
	}
	if (pos.x < -MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(-MAP_LIMIT, pos.y, pos.z));
	}
	if (pos.z > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, MAP_LIMIT));
	}
	if (pos.z < -MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, -MAP_LIMIT));
	}
}

//=============================================================================
// 入力情報を角度に変換する
//=============================================================================
float CPlayer::InputToAngle(void)
{
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);					// ジョイスティックの取得
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();				// キーボードの取得
	float fInputAngle = NULL;											//移動アングル
	//コントローラー入力がある場合
	if (js.lX != 0.0f || js.lY != 0.0f)
	{
		fInputAngle = atan2f((float)js.lX, -(float)js.lY);
	}
	else
	{
		//キーボード入力を角度に変換
		if (pKeyboard->GetPress(DIK_A))
		{
			fInputAngle = D3DXToRadian(-90.0f);
		}
		if (pKeyboard->GetPress(DIK_D))
		{
			fInputAngle = D3DXToRadian(90.0f);
		}
		if (pKeyboard->GetPress(DIK_S))
		{
			fInputAngle = D3DXToRadian(180.0f);

			// 同時押し用の処理
			if (pKeyboard->GetPress(DIK_A))
			{
				fInputAngle += D3DXToRadian(45.0f);
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				fInputAngle += D3DXToRadian(-45.0f);
			}
		}
		if (pKeyboard->GetPress(DIK_W))
		{
			fInputAngle = D3DXToRadian(0.0f);

			if (pKeyboard->GetPress(DIK_A))
			{
				fInputAngle += D3DXToRadian(-45.0f);
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				fInputAngle += D3DXToRadian(45.0f);
			}
		}
	}

	return fInputAngle;
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
		for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
		{
			// !nullcheck
			if (m_apItem[nCount] != nullptr)
			{
				if (m_apItem[nCount]->GetUse() == false)
				{
					// アイテムを使う
					m_apItem[nCount]->SetItem();

					break;
				}
			}
		}

	}
}

//=============================================================================
// アイテムのデータを渡す
//=============================================================================
void CPlayer::AcquiredItem(CItem *pItem)
{
	if (m_apItem.size() == 0)
	{
		// アイテムのポインタ
		m_apItem.push_back(pItem);
	}
	else if (m_apItem[0] != nullptr)
	{
		// 使われている状態なら
		if (m_apItem[0]->GetUse() == true)
		{
			// アイテムのポインタ
			m_apItem.push_back(pItem);
		}
	}
}