//=============================================================================
//
// カメラの処理 [camera.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CAMERA_DEFAULT_FVARTICAL	(D3DXToRadian(75.0f))			// カメラの縦回転初期値
#define DISTANCE					(1700.0f)						// 視点～注視点の距離
#define DISTANCE_FAR_UP				(35.0f)							// カメラを引く値
#define HEIGHT_FROM_PLAYER			(200.0f)						// 注視点の高さ
#define CAMERA_MIN_FHORIZONTAL		(D3DXToRadian(10.0f))			// カメラの最小角
#define CAMERA_MAX_FHORIZONTAL		(D3DXToRadian(170.0f))			// カメラの最大角
#define CAMERA_MIN_HIGHT			(2.0f)							// カメラの最低高度
#define STICK_DEADZONE				(50.0f)						// スティック感度
#define STICK_INPUT_CONVERSION		(D3DXToRadian(2.0f))			// スティック入力最大変化量
#define	ANGLE_FIX_RATE				(0.01f)							// カメラ向き補正率
#define REVERSE_ANGLE				(D3DXToRadian(180.0f))			// カメラ反転用

//=============================================================================
// static初期化宣言
//=============================================================================
int CCamera::m_nAllNum = 0;

//=============================================================================
// インスタンス生成
//=============================================================================
CCamera * CCamera::Create(int nCount)
{
	// メモリ確保
	CCamera *pCamera = new CCamera;

	// !nullcheck
	if (pCamera != NULL)
	{
		// 自身の番号を取得
		pCamera->m_nNumber = nCount;

		// 初期化処理
		pCamera->Init();
	}

	return pCamera;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	//各メンバ変数のクリア
	m_posV = ZeroVector3;		// カメラの座標
	m_posVDest = ZeroVector3;	// カメラの座標（目的地）
	m_posR = ZeroVector3;		// 注視点
	m_posRDest = ZeroVector3;	// 注視点（目的地）
	m_posU = ZeroVector3;		// 上方向ベクトル
	m_rot = ZeroVector3;		// 向き
	m_fDistance = 0.0f;			// 視点～注視点の距離
	m_fMove = 0.0f;				// 移動量
	m_nNumber = ++m_nAllNum;	// カメラの番号の設定
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera()
{
	m_nAllNum = 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_fMove = 5.0f;
	m_fDistance = DISTANCE;
	m_fVartical = CAMERA_DEFAULT_FVARTICAL;
	m_fHorizontal = D3DXToRadian(0.0f);											// 初期値敵のほう向ける
	m_posR = D3DXVECTOR3(0.0f, HEIGHT_FROM_PLAYER, 0.0f);						// 注視点設定
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);										// 上方向ベクトル
	m_posV.x = m_posR.x + m_fDistance* sinf(m_fVartical) * sinf(m_fHorizontal);	// カメラ位置X
	m_posV.y = m_posR.z + m_fDistance* cosf(m_fVartical);						// カメラ位置Y
	m_posV.z = m_posR.y + m_fDistance* sinf(m_fVartical) * cosf(m_fHorizontal);	// カメラ位置Z

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	//キーボードクラス情報の取得
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();
	CPlayer* pPlayer = CGame::GetPlayer(m_nNumber);

	// プレイヤーが使われていたら
	if (CGame::GetPlayer(m_nNumber) != NULL)
	{
		// 通常状態のカメラ移動
		NomalUpdate(pPlayer->GetPos());

		if (pPlayer->GetIsFly())
		{
			FixAngleToPlayerDirection(pPlayer->GetRot());
		}
	}
}

//=============================================================================
// 通常状態の更新処理
//=============================================================================
void CCamera::NomalUpdate(D3DXVECTOR3 PlayerPos)
{
	//キーボードクラス情報の取得
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	// ジョイパッドの取得
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);
	if (js.lZ > STICK_DEADZONE || js.lZ < -STICK_DEADZONE || js.lRz > STICK_DEADZONE || js.lRz < -STICK_DEADZONE)
	{
		if (js.lZ > STICK_DEADZONE || js.lZ < -STICK_DEADZONE)
		{
			m_fHorizontal += js.lZ / (STICK_MAX_VALUE / STICK_INPUT_CONVERSION);
		}
		//視点（カメラ座標）の上旋回
		if (js.lRz > STICK_DEADZONE || js.lRz < -STICK_DEADZONE)
		{
			m_fVartical -= js.lRz / (STICK_MAX_VALUE / STICK_INPUT_CONVERSION);
		}
	}
	else
	{
		//視点（カメラ座標）の左旋回
		if (pKeyInput->GetPress(DIK_LEFT))
		{
			m_fHorizontal += STICK_INPUT_CONVERSION;
		}
		//視点（カメラ座標）の右旋回
		if (pKeyInput->GetPress(DIK_RIGHT))
		{
			m_fHorizontal -= STICK_INPUT_CONVERSION;
		}
		//視点（カメラ座標）の上旋回
		if (pKeyInput->GetPress(DIK_UP))
		{
			m_fVartical -= STICK_INPUT_CONVERSION;
		}
		//視点（カメラ座標）の下旋回
		if (pKeyInput->GetPress(DIK_DOWN))
		{
			m_fVartical += STICK_INPUT_CONVERSION;
		}
	}

	// 縦方向の回転の制限
	if (m_fVartical > CAMERA_MAX_FHORIZONTAL)
	{
		m_fVartical = CAMERA_MAX_FHORIZONTAL;
	}
	if (m_fVartical < CAMERA_MIN_FHORIZONTAL)
	{
		m_fVartical = CAMERA_MIN_FHORIZONTAL;
	}

	// カメラの位置設定
	m_posVDest.x = PlayerPos.x + m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);			// カメラ位置X設定
	m_posVDest.y = PlayerPos.y + HEIGHT_FROM_PLAYER + m_fDistance * cosf(m_fVartical);			// カメラ位置Y設定
	m_posVDest.z = PlayerPos.z + m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);			// カメラ位置Z設定

	m_posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + HEIGHT_FROM_PLAYER, PlayerPos.z);		//注視点設定

	//カメラPOSYの下限
	if (m_posVDest.y <= CAMERA_MIN_HIGHT)
	{
		m_posVDest.y = CAMERA_MIN_HIGHT;	//限界値に戻す
	}

	//設定値の反映
	m_posV += (m_posVDest - m_posV)*0.1f;
	m_posR += (m_posRDest - m_posR)*0.9f;
}

//=============================================================================
// カメラの向きをプレイヤーの向きに補正する
//=============================================================================
void CCamera::FixAngleToPlayerDirection(D3DXVECTOR3 PlayerRot)
{
	m_fHorizontal += (PlayerRot.y - m_fHorizontal) * ANGLE_FIX_RATE;
	m_fVartical += (PlayerRot.x + REVERSE_ANGLE - m_fVartical) * ANGLE_FIX_RATE;
}

//=============================================================================
//カメラクラスのセット処理
//=============================================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	if (CGame::GetPlayerNum() == 2)
	{
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH/2 / (float)SCREEN_HEIGHT,
			10.0f,
			100000.0f);
	}
	else
	{
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			100000.0f);
	}
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//=============================================================================
// ターゲットの設定
//=============================================================================
void CCamera::SetTarget(bool Target)
{
	m_bTarget = Target;
}

//=============================================================================
//カメラの位置取得処理
//=============================================================================
D3DXVECTOR3 CCamera::GetposV(void)
{
	return m_posV;
}

//=============================================================================
//カメラの角度取得処理
//=============================================================================
D3DXVECTOR3 CCamera::GetposR(void)
{
	return m_posR;
}

//=============================================================================
//カメラのビューマトリックス取得処理
//=============================================================================
D3DXMATRIX CCamera::GetMtxView(void)
{
	return m_mtxView;
}

//=============================================================================
// 目的の角度
//=============================================================================
D3DXVECTOR3 CCamera::GetposVDest(void)
{
	return m_posVDest;
}

//=============================================================================
//カメラのターゲットフラグ取得処理
//=============================================================================
bool CCamera::GetTargetBool(void)
{
	return m_bTarget;
}

//=============================================================================
//カメラの縦回転角取得処理
//=============================================================================
float CCamera::GetVartical(void)
{
	return m_fVartical;
}

//=============================================================================
//カメラの横回転角取得処理
//=============================================================================
float CCamera::GetHorizontal(void)
{
	return m_fHorizontal;
}