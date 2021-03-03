//=============================================================================
//
// エフェクト生成クラス [effect_factory.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "effect_factory.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "effect_3d.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define EFFECT_TEXTURE_NAME	("data/Text/effect.txt")

//=============================================================================
// static初期化
//=============================================================================
CEffectFactory::EFFECT CEffectFactory::m_Effect[EFFECT_NUM_MAX] = {};			// 構造体情報

//=============================================================================
// コンストラクタ
//=============================================================================
CEffectFactory::CEffectFactory()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CEffectFactory::~CEffectFactory()
{
}

//=============================================================================
// パーティクルの生成
//=============================================================================
void CEffectFactory::CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type)
{
	switch (type)
	{
		// ※こんな感じで使えます

		case EFFECT_NUM_EXPLOSION:
		//	// 爆発生成時のパーティクル生成
		//	for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSION].nNum; nCount++)
		//	{
		//		CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSION],
		//			CTexture::TEXTURE_NUM_PARTICLE);
		//	}

			break;
	default:
		break;
	}
}

//=============================================================================
// ファイルの読み込み
//=============================================================================
HRESULT CEffectFactory::ReadFile(void)
{
	FILE *pFile = NULL;		//FILEポインタ
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// モデルのインデックス

	// ファイルオープン
	pFile = fopen(EFFECT_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "PARTICLESET") == 0)
			{
				//インデックスを最初に戻す
				nParticleIndex = 0;

				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aParticleName, "END_PARTICLESET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "EFFECTSET") == 0)
					{
						//END_PARTSSETを読み込むまで繰り返す
						while (strcmp(aParticleName, "END_EFFECTSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// サイズの設定
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].size.x,
									&m_Effect[nParticleIndex].size.y,
									&m_Effect[nParticleIndex].size.z);
							}
							if (strcmp(aParticleName, "MOVE") == 0)
							{
								// 移動量
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].move.x,
									&m_Effect[nParticleIndex].move.y,
									&m_Effect[nParticleIndex].move.z);
							}
							if (strcmp(aParticleName, "DISTANCE") == 0)
							{
								// 距離
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].Distance.x,
									&m_Effect[nParticleIndex].Distance.y, 
									&m_Effect[nParticleIndex].Distance.z);
							}
							if (strcmp(aParticleName, "LIFE") == 0)
							{
								// 体力
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nLife);
							}
							if (strcmp(aParticleName, "NUM") == 0)
							{
								// 数
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nNum);
							}
							if (strcmp(aParticleName, "COLOR") == 0)
							{
								// 色
								sscanf(aHeadData, "%*s %*s %f %f %f %f", 
									&m_Effect[nParticleIndex].color.r,
									&m_Effect[nParticleIndex].color.g, 
									&m_Effect[nParticleIndex].color.b,
									&m_Effect[nParticleIndex].color.a);
							}
							if (strcmp(aParticleName, "GRAVITY") == 0)
							{
								// 重力
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bGravity);
							}
							if (strcmp(aParticleName, "ALPHA") == 0)
							{
								// 透明にするか
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bAlpha);
							}
							if (strcmp(aParticleName, "ALPHANUM") == 0)
							{
								// アルファテストの値
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].nAlphaNum);
							}
							if (strcmp(aParticleName, "ANIMATION") == 0)
							{
								// アニメーション
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bAnimation);
							}
							if (strcmp(aParticleName, "BLEND") == 0)
							{
								// アニメーション
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}
							if (strcmp(aParticleName, "PRIORITY") == 0)
							{
								// アニメーション
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}

							
						}

						//インデックスを１つ進める
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

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