//=============================================================================
//
// キャラクタークラス [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "renderer.h"
#include "manager.h"
#include "collision.h"
#include "game.h"
#include "player.h"
#include "particle.h"
#include "effect_factory.h"
#include "texture.h"
#include "number_3d.h"
#include "sound.h"
#include "xfile.h"
#include "resource_manager.h"
#include "motion.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GRAVITY_POWAR			(0.3f)						// 重力の強さ
#define GROUND_RIMIT			(0.0f)						// 地面の制限

//=============================================================================
// static初期化処理
//=============================================================================
 int CCharacter::m_nAllNum = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
 CCharacter::CCharacter(PRIORITY Priority) : CScene(Priority)
 {
	 m_State = STATE_NONE;
	 m_pos = ZeroVector3;
	 m_posOld = ZeroVector3;
	 m_move = ZeroVector3;
	 m_rot = ZeroVector3;
	 m_nLife = 0;
	 m_nCharaNum = m_nAllNum++;
	 m_fAngle = 0.0f;
	 m_fSpeed = 0.0f;
	 m_bJump = false;
	 m_fRadius = 0.0f;
	 m_nStateCounter = 0;
	 m_nMaxLife = 0;
	 m_nParts = 0;
	 m_pMotion = NULL;
	 m_bUseGravity = true;
	 memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
 }

//=============================================================================
// デストラクタ
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCharacter::Init()
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacter::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//終了処理
			m_apModelAnime[nCntModelNum]->Uninit();

			//メモリの削除
			delete m_apModelAnime[nCntModelNum];

			//メモリのクリア
			m_apModelAnime[nCntModelNum] = NULL;
		}
	}

	// !nullcheck
	if (m_pMotion != NULL)
	{
		// 終了処理
		m_pMotion->Uninit();

		//メモリの削除
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacter::Update()
{
	// 重力
	if (m_bUseGravity)
	{
		if (Gravity() == true)
		{

		}
	}
	// 移動量加算
	m_pos += m_move;

	//アニメーションの更新処理
	ModelAnimeUpdate();

	// 当たり判定
	BodyCollision();
}

//=============================================================================
// 描画処理
//=============================================================================
void CCharacter::Draw()
{
	// 描画処理
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 裏面を（左回り）をカリング

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//階層モデルクラスの描画処理
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// 裏面を（左回り）をカリング
}

//=============================================================================
// モデルの生成
//=============================================================================
void CCharacter::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	// XFileのポインタ取得
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != NULL)
	{
		// モデルパーツの設定
		m_nParts = pXfile->GetModelParts(FileNum);

		//モデルパーツ数分繰り返す
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);

			if (m_apModelAnime[nCntModel] == NULL)
			{
				// 初期化処理
				m_apModelAnime[nCntModel] = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot);

				// モデルの生成
				m_apModelAnime[nCntModel]->SetModel(pXfile->GetHierarchyXfile(nCntModel, FileNum));
			}

			//親子構造の設定
			if (m_apModelAnime[nCntModel] != NULL)
			{
				//親モデルの場合
				if (nCntModel == 0)
				{
					m_apModelAnime[nCntModel]->SetParent(NULL);
				}
				//子モデルの場合
				else
				{
					//自分の親情報を設定する
					m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[ModelFile.nParent]);
				}
			}
		}

		// nullcheck
		if (m_pMotion == NULL)
		{
			// インスタンス生成
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// モデルアニメーション
//=============================================================================
void CCharacter::ModelAnimeUpdate(void)
{
	// モーションの更新処理
	if (m_pMotion != NULL)
	{
		// モーションの更新
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 着地の処理
//=============================================================================
void CCharacter::Landing(float fPosY)
{
	// 着地の処理
	if (m_pos.y <= fPosY)
	{
		m_move.y = 0.0f;
		m_pos.y = fPosY;
		m_bJump = false;

		if (m_bLanding == false)
		{
			m_bLanding = true;
		}
	}
}

//=============================================================================
// 重力
//=============================================================================
bool CCharacter::Gravity(void)
{
	// 重力をかける
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// 落下

	return false;
}

//=============================================================================
// モーションの設定
//=============================================================================
void CCharacter::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != NULL)
	{
		// モーションの更新
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
void CCharacter::BodyCollision(void)
{
}

//=============================================================================
// 座標の設定
//=============================================================================
void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 古い座標の設定
//=============================================================================
void CCharacter::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//=============================================================================
// 移動量の設定
//=============================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 角度の設定
//=============================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 体力の設定
//=============================================================================
void CCharacter::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ジャンプの設定
//=============================================================================
void CCharacter::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// 地面にいるフラグ設定
//=============================================================================
void CCharacter::SetLanding(bool bLanding)
{
	m_bLanding = bLanding;
}

//=============================================================================
// 半径の設定
//=============================================================================
void CCharacter::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
}

//=============================================================================
// キャラクターの速度設定
//=============================================================================
void CCharacter::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// 状態カウンターの設定
//=============================================================================
void CCharacter::SetStateCounter(int nStateCounter)
{
	m_nStateCounter = nStateCounter;
}

//=============================================================================
// 重力の設定
//=============================================================================
void CCharacter::SetUseGravity(bool bUseGravity)
{
	m_bUseGravity = bUseGravity;
}