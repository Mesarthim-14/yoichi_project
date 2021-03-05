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

//=============================================================================
// マクロ定義
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// 重力の強さ
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
	 m_nPart = 0;
	 m_nCharaNum = m_nAllNum++;
	 m_nWeaponTipNum = 0;
	 m_fAngle = 0.0f;
	 m_fSpeed = 0.0f;
	 m_bJump = false;
	 m_fRadius = 0.0f;
	 memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	 memset(m_modelfile, 0, sizeof(m_modelfile));
	 m_pFileName = NULL;
	 memset(m_Motion, 0, sizeof(m_Motion));
	 m_apKeyInfo = NULL;
	 m_nMotionState = 0;
	 m_nNumKey = 0;
	 m_nCountMotion = 0;
	 m_nMotionInterval = 0;
	 m_nStateCounter = 0;
	 m_nKey = 0;
	 m_bMotionPlaing = false;
	 m_nMaxLife = 0;
	 m_diffPos = ZeroVector3;
	 m_diffRot = ZeroVector3;
	 m_Ctype = CHARACTER_TYPE_NONE;
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
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 引数の代入
	m_pos = pos;	// 座標の設定
	m_rot = rot;	// 角度の設定

	//ファイル読み込み
	if (FAILED(CCharacter::ReadFile()))
	{
		return E_FAIL;
	}

	//モデルパーツ数分繰り返す
	for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] == NULL)
		{
			//モデルの生成
			m_apModelAnime[nCntModel] = CModelAnime::Create(m_modelfile[nCntModel].xFileName,
				m_modelfile[nCntModel].offsetPos, m_modelfile[nCntModel].offsetRot);
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
				m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[m_modelfile[nCntModel].nParent]);
			}
		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCharacter::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nPart; nCntModelNum++)
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

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCharacter::Update()
{
	//アニメーションの更新処理
	UpdateMotion();

	// 重力
	if (Gravity() == true)
	{
		if (m_bLanding == false)
		{
			m_bLanding = true;
		}
	}

	// 移動量加算
	m_pos += m_move;

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

	for (int nCntModelNum = 0; nCntModelNum < m_nPart; nCntModelNum++)
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
// モーションの更新処理
//=============================================================================
void CCharacter::UpdateMotion(void)
{
	KEY *pKey[MAX_CHARACTER_PARTS];

	//現在キーが最大キー数未満の場合
	if (m_nKey < m_Motion[m_nMotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
		{
			// 各モデルパーツのキー設定
			m_apKeyInfo = &m_Motion[m_nMotionState].aKeyInfo[m_nKey];

			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
		{
			if (m_apModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = m_apModelAnime[nCntModel]->GetRotAnime();

				//	if (m_nCountMotion == 0)
				if (m_Motion[m_nMotionState].bLoop == false)
				{
					if (m_nKey == 0)
					{
						m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX - startPos.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY - startPos.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ - startPos.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

						// 1フレーム当たりの更新値 = (終点向き-開始向き) / フレーム数
						m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX - startRot.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY - startRot.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ - startRot.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					}
					else
					{
						// 1フレーム当たりの更新値 = (終点位置-開始位置) / フレーム数
						m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fPosX) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fPosY) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fPosZ) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

						// 1フレーム当たりの更新値 = (終点向き-開始向き) / フレーム数
						m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fRotX) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fRotY) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fRotZ) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					}
				}
				else
				{
					// 1フレーム当たりの更新値 = (終点位置-開始位置) / フレーム数
					m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX - startPos.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY - startPos.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ - startPos.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

					// 1フレーム当たりの更新値 = (終点向き-開始向き) / フレーム数
					m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX - startRot.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY - startRot.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ - startRot.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

				}

				D3DXVECTOR3 setPos, setRot;

				setPos.x = m_diffPos.x + startPos.x;
				setPos.y = m_diffPos.y + startPos.y;
				setPos.z = m_diffPos.z + startPos.z;

				setRot.x = m_diffRot.x + startRot.x;
				setRot.y = m_diffRot.y + startRot.y;
				setRot.z = m_diffRot.z + startRot.z;

				//位置の設定
				m_apModelAnime[nCntModel]->SetPosAnime(setPos);

				//向きの設定
				m_apModelAnime[nCntModel]->SetRotAnime(setRot);
			}
		}

		//モーションカウンターの加算
		m_nCountMotion++;

		//現在キーの再生フレームに達したら
		if (m_nCountMotion >= m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame)
		{
			//キーを１つ進める
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//ループするなら
		if (m_Motion[m_nMotionState].bLoop == true)
		{
			m_nKey = 0;
			m_nCountMotion = 0;
		}
		else
		{
			// ループしないとき
			m_nMotionInterval++;

			if (m_nMotionInterval == 10)
			{
				m_bMotionPlaing = false;
				m_nMotionInterval = 0;
			}

			// アイドルモーションに戻す
			SetMotion(0);
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

	// 着地の処理
	if (m_pos.y <= GROUND_RIMIT)
	{
		m_move.y = 0.0f;
		m_pos.y = GROUND_RIMIT;
		m_bJump = false;

		return true;
	}

	return false;
}

//=============================================================================
// モデルファイル読み込み
//=============================================================================
HRESULT CCharacter::ReadFile(void)
{
	FILE *pFile = NULL;		//FILEポインタ
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	// モデルのインデックス
	int nMotionType = 0;	// モーションのタイプ
	int nKeyNum = 0;		// キー番号
	int nMotionNum = 0;		// モーション番号

	// ファイルオープン
	pFile = fopen(m_pFileName, "r");

	if (pFile != NULL)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

			if (strcmp(aModeName, "MODEL_FILENAME") == 0)
			{
				//Xファイルの名前
				sscanf(aHeadData, "%*s %*s %s %*s %*s", m_modelfile[nModelIndex].xFileName);

				//インデックスを１つ進める
				nModelIndex++;
			}

			if (strcmp(aModeName, "CHARACTERSET") == 0)
			{
				//インデックスを最初に戻す
				nModelIndex = 0;

				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aModeName, "END_CHARACTERSET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					if (strcmp(aModeName, "PARTSSET") == 0)
					{
						//END_PARTSSETを読み込むまで繰り返す
						while (strcmp(aModeName, "END_PARTSSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							if (strcmp(aModeName, "PARENT") == 0)
							{
								//親子情報の設定
								sscanf(aHeadData, "%*s %*s %d", &m_modelfile[nModelIndex].nParent);
							}
							if (strcmp(aModeName, "POS") == 0)
							{
								//位置の設定
								sscanf(aHeadData, "%*s %*s %f %f %f", &m_modelfile[nModelIndex].offsetPos.x,
									&m_modelfile[nModelIndex].offsetPos.y, &m_modelfile[nModelIndex].offsetPos.z);
							}
							if (strcmp(aModeName, "ROT") == 0)
							{
								//向きの設定
								sscanf(aHeadData, "%*s %*s %f %f %f", &m_modelfile[nModelIndex].offsetRot.x,
									&m_modelfile[nModelIndex].offsetRot.y, &m_modelfile[nModelIndex].offsetRot.z);
							}
						}
						//インデックスを１つ進める
						nModelIndex++;
					}
				}
			}

			//モーションセット
			if (strcmp(aModeName, "MOTIONSET") == 0)
			{
				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aModeName, "END_MOTIONSET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					//ループ情報の取得
					if (strcmp(aModeName, "LOOP") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].bLoop);
					}

					//キー情報の取得
					if (strcmp(aModeName, "NUM_KEY") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].nNumKey);
					}

					if (strcmp(aModeName, "KEYSET") == 0)
					{
						//END_KEYSETになるまで繰り返す
						while (strcmp(aModeName, "END_KEYSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							//フレーム数の取得
							if (strcmp(aModeName, "FRAME") == 0)
							{
								sscanf(aHeadData, "%*s %*s %d", &m_Motion[nMotionType].aKeyInfo[nMotionNum].nFrame);
							}

							//各キーのオフセット情報の取得
							if (strcmp(aModeName, "KEY") == 0)
							{
								//END_KEYになるまで繰り返す
								while (strcmp(aModeName, "END_KEY") != 0)
								{
									//一列読み込んでモード情報を抽出
									fgets(aHeadData, sizeof(aHeadData), pFile);
									sscanf(aHeadData, "%s", aModeName);

									//位置の取得
									if (strcmp(aModeName, "POS") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosZ);
									}

									//向きの取得
									if (strcmp(aModeName, "ROT") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotZ);
									}
								}
								//読み終わったらカウントを1つ進める
								nKeyNum++;
							}
						}
						nKeyNum = 0;
						nMotionNum++;
					}
				}
				nMotionNum = 0;
				nMotionType++;
			}

		} while (strcmp(aModeName, "END_SCRIPT") != 0);

		//ファイルクローズ
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//失敗した場合メッセージボックスを表示
		MessageBox(NULL, "モーションファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}

}


//=============================================================================
// 当たり判定
//=============================================================================
void CCharacter::BodyCollision(void)
{
//	// キャラクターのポインタ
//	CCharacter *pCharacter = (CCharacter*)GetTop(PRIORITY_CHARACTER);
//
//	while (pCharacter != NULL)
//	{
//		// 自分の番号じゃないとき
//		if (pCharacter->m_nCharaNum != m_nCharaNum)
//		{
//			// 円形と円形の当たり判定
//			if (CCollision::CollisionCircularAndCircular(
//				m_pos, pCharacter->m_pos,
//				m_fRadius, pCharacter->m_fRadius) == true)
//			{
//				if (pCharacter->m_Ctype == CHARACTER_TYPE_PLAYER)
//				{
//					// 外に押し出す
//					D3DXVECTOR3 vec = (pCharacter->GetPos() - m_pos);
//					D3DXVec3Normalize(&vec, &vec);
//					vec *= (pCharacter->m_fRadius + m_fRadius);
//
//					D3DXVECTOR3 pos = pCharacter->GetPos();
//					pCharacter->SetPos(GetPos() + vec);
//				}
//				else
//				{
//					// 外に押し出す
//					D3DXVECTOR3 vec = (m_pos - pCharacter->GetPos());
//					D3DXVec3Normalize(&vec, &vec);
//					vec *= (m_fRadius + pCharacter->m_fRadius);
//
//					D3DXVECTOR3 pos = GetPos();
//					SetPos(pCharacter->GetPos() + vec);
//				}
//			}
//		}
//
//		// 次のポインタ
//		pCharacter = (CCharacter*)pCharacter->GetNext();
//	}
}

//=============================================================================
// モーションの設定
//=============================================================================
void CCharacter::SetMotion(int nMotion)
{
	// 元のモーションと違ったら
		if (m_nMotionState != nMotion)
		{
			// 値の初期化
			m_nKey = 0;
			m_nCountMotion = 0;
			m_nMotionInterval = 0;
			D3DXVECTOR3 pos, rot;
			m_nMotionState = nMotion;
			m_bMotionPlaing = true;

			for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
			{
				if (m_apModelAnime[nCntModel] != NULL)
				{
					//開始位置
					pos.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
					pos.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
					pos.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

					//開始向き
					rot.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
					rot.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
					rot.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

					//位置の設定
					m_apModelAnime[nCntModel]->SetPosAnime(pos);

					//向きの設定
					m_apModelAnime[nCntModel]->SetRotAnime(rot);
				}
			}
		}
}

//=============================================================================
// モデルパーツ情報読み込み
//=============================================================================
void CCharacter::SetCharaModel(char * xfilename, int nPart, int nMotion)
{
	m_pFileName = xfilename;
	m_nPart = nPart;
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
// モーションのカウント設定
//=============================================================================
void CCharacter::SetCountMotion(int CountMotion)
{
	m_nCountMotion = CountMotion;
}

//=============================================================================
// モーションの状態設定
//=============================================================================
void CCharacter::SetMotionState(int nMotionState)
{
	m_nMotionState = nMotionState;
}

//=============================================================================
// キーの設定
//=============================================================================
void CCharacter::SetKey(int nKey)
{
	m_nKey = nKey;
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
// キャラクターのタイプ設定
//=============================================================================
void CCharacter::SetCType(CHARACTER_TYPE Ctype)
{
	m_Ctype = Ctype;
}

//=============================================================================
// キャラクターの速度設定
//=============================================================================
void CCharacter::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// 剣先のパーツ番号設定
//=============================================================================
void CCharacter::SetWeaponTipNum(int nWeaponTipNum)
{
	m_nWeaponTipNum = nWeaponTipNum;
}

//=============================================================================
// 剣の根本のパーツ番号設定
//=============================================================================
void CCharacter::SetWeaponRootNum(int nWeaponRootNum)
{
	m_nWeaponRootNum = nWeaponRootNum;
}

//=============================================================================
// 状態カウンターの設定
//=============================================================================
void CCharacter::SetStateCounter(int nStateCounter)
{
	m_nStateCounter = nStateCounter;
}