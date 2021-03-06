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
#include "effect.h"
#include "effect_factory.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "character.h"
#include "motion.h"
#include "item.h"
#include "stage_map.h"
#include "mesh_pillar.h"
#include "wind.h"
#include "barrier.h"
#include "barrier_effect.h"
#include "magichand.h"
#include "player_ui.h"
#include "wind_effect.h"
#include "shadow.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED			(20.0f)					// プレイヤーの移動量
#define PLAYER_JUMP				(17.0f)					// ジャンプの処理
#define STICK_DEADZONE			(50.0f)					// スティック感度
#define PLAYER_ROT_SPEED		(0.15f)					// キャラクターの回転する速度
#define PLAYER_RADIUS			(200.0f)					// 4半径の大きさ
#define PLAYER_PARTS			(22)						// プレイヤーのパーツ数
#define GAME_END_FLAME			(100)					// ゲームが終わるフレーム
#define PLAYER_FLY_SPEED		(30.0f)					// 飛行時のプレイヤーの移動量
#define FLY_ROT_X_MAX			(-D3DXToRadian(10.0f))	// 飛行の最大角
#define FLY_ROT_X_MIN			(-D3DXToRadian(170.0f))	// 飛行の最小角
#define FLY_GRAVITY_RATE		(0.5f)					// 飛行時の重力
#define SUB_STAR_FLOODED_NUM	(3)						// 浸水

// エフェクトパーツ
#define BLADE_EFFECT_INTER		(190)					// 刀身のパーティクルの間隔
#define WEAPON_TIP_NUM			(20)					// 剣先のパーツ番号
#define WEAPON_ROOT_NUM			(21)					// 剣の根元のパーツ番号

//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCount)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// 番号の設定
	pPlayer->m_nNumber = nCount;

	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);
	// 初期化処理
	pPlayer->Init();
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
	m_bStickReverseVartical = false;
	m_bDraw = true;
	m_nEndCounter = 0;
	m_fBaseSpeed = 0.0f;
	m_bArmor = false;
	m_nStarNum = 0;
    m_nFlyTime = 0;
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
HRESULT CPlayer::Init(void)
{
	// モデル情報取得
	CXfile *pXfile = GET_XFILE_PTR;

	// !nullcheck
	if (pXfile != NULL)
	{
		// モデルの情報を渡す
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

    // UIの生成
    m_pPlayerUI = CPlayer_UI::Create();
    m_pPlayerUI->Init(m_nNumber);

	// 初期化処理
	CCharacter::Init();				// 座標 角度
	SetRadius(PLAYER_RADIUS);				// 半径の設定
	SetSpeed(PLAYER_FLY_SPEED);				// 速度の設定

	m_fBaseSpeed = PLAYER_FLY_SPEED;		// 元のスピード保持
	m_fBaseRadius = PLAYER_RADIUS;			// 半径
    m_nFlyTime = MAX_FLY_TIME;              // 飛行時間

	// 影生成
	CShadow::Create(CTexture::TEXTURE_NUM_SHADOW, m_nNumber);
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

	// 座標代入
	D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
	SetPosOld(pos);				// 古い座標保存

	// プレイヤーの状態
	UpdateState();

	// モーション状態
	UpdateMotionState();

	// プレイヤーの制御
	PlayerControl();

	// アイテムの削除処理
    m_pPlayerUI->ItemErase();

	// 親クラスの更新処理
	CCharacter::Update();

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

	while (m_rotDest.x - rot.x > D3DXToRadian(180))
	{
		m_rotDest.x -= D3DXToRadian(360);
	}

	while (m_rotDest.x - rot.x < D3DXToRadian(-180))
	{
		m_rotDest.x += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	while (rot.y > D3DXToRadian(180))
	{
		rot.y -= D3DXToRadian(360);
	}

	while (rot.y < D3DXToRadian(-180))
	{
		rot.y += D3DXToRadian(360);
	}

	while (rot.x > D3DXToRadian(180))
	{
		rot.x -= D3DXToRadian(360);
	}

	while (rot.x < D3DXToRadian(-180))
	{
		rot.x += D3DXToRadian(360);
	}

    // 着地フラグONのとき
    if (GetLanding())
    {
        m_nFlyTime = MAX_FLY_TIME;              // 飛行時間の回復

    }

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

    // キーボード情報
    CInputKeyboard *pKeyboard = CManager::GetKeyboard();

    // SPACEキーを押したとき・コントローラのYを押したとき
    if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, GetPlayerNum())
        || pKeyboard->GetTrigger(DIK_I))
    {
        // アイテムの使用
        m_pPlayerUI->UseItem();
    }
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();				// キーボード取得
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);					// ジョイパッドの取得
	CSound *pSound = GET_SOUND_PTR;	// サウンドポインタ取得
	float fSpeed = GetSpeed();											// 速度取得
	float fCameraAngle = CGame::GetCamera(m_nNumber)->GetHorizontal();	// カメラ角度取得
	float fMoveAngle = 0.0f; 											// 移動角度
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

			// ジャンプモーションの再生
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
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();		// キーボードを取得
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);		// ジョイパッドを取得
	D3DXVECTOR3 move = ZeroVector3;							// 移動量
	D3DXMATRIX mtxRot;										// 回転計算用行列
	ZeroMemory(&mtxRot, sizeof(mtxRot));
	CCamera* pCamera = CGame::GetCamera(m_nNumber);
    
    // 飛行時間が0以下のときは飛べない
    if (m_nFlyTime <= 0)
    {
        //m_bFly = false;
        if (!GetUseGravity())
        {
            SetUseGravity(true);
        }
        return;
    }

	// 重力を無効化
	if (GetUseGravity())
	{
		SetUseGravity(false);
	}
	// 飛行時間を減らす
    m_nFlyTime--;

	//プレイヤーの上方向に移動
	move = D3DXVECTOR3(0.0f, GetSpeed(), 0.0f);
	// スティックが押し込まれたら上下反転する
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L3, m_nNumber))
	{
		m_bStickReverseVartical = !m_bStickReverseVartical;
	}
	// コントローラーの入力を変換
	m_rotDest.y += D3DXToRadian((float)js.lX / 1000.0f);
	if (m_bStickReverseVartical)
	{
		m_rotDest.x -= D3DXToRadian((float)js.lY / 1000.0f);
	}
	else
	{
		m_rotDest.x += D3DXToRadian((float)js.lY / 1000.0f);
	}
	
	// 上下移動の制限
	if (m_rotDest.x > FLY_ROT_X_MAX)
	{
		m_rotDest.x = FLY_ROT_X_MAX;
	}
	if (m_rotDest.x < FLY_ROT_X_MIN)
	{
		m_rotDest.x = FLY_ROT_X_MIN;
	}
	// コントローラー入力を利用してプレイヤーの向きを変換
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotDest.y, m_rotDest.x, m_rotDest.z);
	D3DXVec3TransformNormal(&move, &move, &mtxRot);
	move.y -= abs(move.y * FLY_GRAVITY_RATE);
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

	// 飛行モーションの再生
	SetMotion(MOTION_FLY);

	// 飛んでいるときの風のエフェクト
	CWindEffect::Create(GetPos(), m_rotDest, D3DXVECTOR3(100.0f, 100.0f, 100.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_PARTICLE);

	switch (m_nNumber)
	{
	case 0:	// 飛んでいるときのキラキラのエフェクト
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_KIRAKIRA_RED);
		break;

	case 1:	// 飛んでいるときのキラキラのエフェクト
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_KIRAKIRA_BLUE);
		break;

	case 2:	// 飛んでいるときのキラキラのエフェクト
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_KIRAKIRA_YELLOW);
		break;

	case 3:	// 飛んでいるときのキラキラのエフェクト
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_KIRAKIRA_GREEN);
		break;

	default:
		break;
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
	// 座標受け取り
	D3DXVECTOR3 pos = GetPos();

	// マップの上限XToZ
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

	// マップ上限Y
	if (pos.y < -MAP_LIMIT_Y)
	{
		// リポップの処理
		Repop();
	}
	if (pos.y > MAP_LIMIT_SKY)
	{
		SetPos(D3DXVECTOR3(pos.x, MAP_LIMIT_SKY, pos.z));
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
// リポップの処理
//=============================================================================
void CPlayer::Repop(void)
{
	// ポインタ情報取得
	CStageMap *pStageMap = CManager::GetGame()->GetStageMap();

	// !nullcheck
	if (pStageMap != nullptr)
	{
		// ローカル変数宣言
		int mMeshPillarNum = pStageMap->GetMeshPillarNum();		// 柱の数
		float fPrevLenght = 0.0f;								// 前回までの距離取得
		int nSortNum = -1;										// 一番小さい配列番号を確保

		for (int nCount = 0; nCount < mMeshPillarNum; nCount++)
		{
			// 柱の情報
			CMeshPillar *pMeshPiller = pStageMap->GetMeshPillar(nCount);

			// !nullcheck
			if (pMeshPiller != nullptr)
			{
				// 座標取得
				D3DXVECTOR3 pos = GetPos();						// 自身の座標
				D3DXVECTOR3 PillerPos = pMeshPiller->GetPos();	// 柱の座標
				
				// 二点の距離
				float fLength = sqrtf(
					powf((PillerPos.x - pos.x), 2) +
					powf((PillerPos.z - pos.z), 2));

				// 前の柱の距離より地下かったら
				if (fPrevLenght > fLength || fPrevLenght == 0.0f)
				{
					fPrevLenght = fLength;	// 近い距離を代入
					nSortNum = nCount;		// 近い配列番号を設定
				}
			}
		}

		// 一番近かった柱の情報取得
		CMeshPillar *pMeshPiller = pStageMap->GetMeshPillar(nSortNum);

		// 座標設定
		SetPos(pMeshPiller->GetPos()*2);
		SetFly(false);
		SetUseGravity(true);
		m_nStarNum -= SUB_STAR_FLOODED_NUM;

		if (m_nStarNum <= 0)
		{
			m_nStarNum = 0;
		}
	}
}