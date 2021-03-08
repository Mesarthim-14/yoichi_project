//=============================================================================
//
// モーションクラス [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "motion.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//階層モデルクラスのコンストラクタ
//=============================================================================
CMotion::CMotion()
{
	m_nKey = 0;
	memset(m_Motion, 0, sizeof(m_Motion));
	m_apKeyInfo = NULL;
	m_nMotionState = 0;
	m_nNumKey = 0;					// キーの総数
	m_nCountMotion = 0;				// モーションカウンター
	m_nMotionInterval = 0;			// モーションのインターバル
	m_nKey = 0;						// 現在キーのNo
	m_bMotionPlaing = false;		// モーションの再生

	m_diffPos = ZeroVector3;			// 変更座標
	m_diffRot = ZeroVector3;			// 変更角度
}

//=============================================================================
//階層モデルクラスのデストラクタ
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
//階層モデルクラスのクリエイト処理
//=============================================================================
CMotion * CMotion::Create(char *pFileName)
{
	//階層モデルクラスのポインタ変数
	CMotion *pMotion = NULL;

	//インスタンス生成
	pMotion = new CMotion;

	// nullcheck
	if (pMotion != NULL)
	{
		//初期化処理呼び出し
		pMotion->Init();

		// ファイルデータ読み込み
		pMotion->ReadMotionFile(pFileName);
	}
	//失敗していた場合
	else
	{
		return NULL;
	}

	return pMotion;
}

//=============================================================================
//階層モデルクラスの初期化処理
//=============================================================================
HRESULT CMotion::Init(void)
{

	return S_OK;
}

//=============================================================================
//階層モデルクラスの終了処理
//=============================================================================
void CMotion::Uninit(void)
{
	
}

//=============================================================================
//階層モデルクラスの更新処理
//=============================================================================
void CMotion::Update(void)
{
}

//=============================================================================
// モーションの更新処理
//=============================================================================
void CMotion::UpdateMotion(int nMaxParts, CModelAnime **pModelAnime)
{
	KEY *pKey[MAX_MODEL_PARTS];

	//現在キーが最大キー数未満の場合
	if (m_nKey < m_Motion[m_nMotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
		{
			// 各モデルパーツのキー設定
			m_apKeyInfo = &m_Motion[m_nMotionState].aKeyInfo[m_nKey];

			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
		{
			if (pModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = pModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = pModelAnime[nCntModel]->GetRotAnime();

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
				pModelAnime[nCntModel]->SetPosAnime(setPos);

				//向きの設定
				pModelAnime[nCntModel]->SetRotAnime(setRot);
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
			SetMotion(0, nMaxParts, pModelAnime);
		}
	}
}

//=============================================================================
// モーションファイル読み込み
//=============================================================================
HRESULT CMotion::ReadMotionFile(char *pFileName)
{
	FILE *pFile = NULL;		//FILEポインタ
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	// モデルのインデックス
	int nMotionType = 0;	// モーションのタイプ
	int nKeyNum = 0;		// キー番号
	int nMotionNum = 0;		// モーション番号

	// ファイルオープン
	pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

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
// モーションの設定
//=============================================================================
void CMotion::SetMotion(int nMotion, int nMaxParts, CModelAnime **pModelAnime)
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

		for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
		{
			if (pModelAnime[nCntModel] != NULL)
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
				pModelAnime[nCntModel]->SetPosAnime(pos);

				//向きの設定
				pModelAnime[nCntModel]->SetRotAnime(rot);
			}
		}
	}
}