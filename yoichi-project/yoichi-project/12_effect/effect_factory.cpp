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
#include "effect.h"
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

		//=============================================================================
		// Author : Ito Yogo
		//=============================================================================
		case EFFECT_NUM_PARTICLE:
			// 爆発生成時のパーティクル生成
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_PARTICLE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_PARTICLE],
					CTexture::TEXTURE_NUM_EFFECT);
			}
			break;

		case EFFECT_NUM_LIGHTNINGSTRIKE:
			// 落雷生成
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_LIGHTNINGSTRIKE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_LIGHTNINGSTRIKE],
					CTexture::SEPARATE_TEX_LIGHTNINGSTRIKE);
			}
			break;

		case EFFECT_NUM_THUNDER:
			// 雷生成
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_THUNDER].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_THUNDER],
					CTexture::SEPARATE_TEX_THUNDER);
			}
			break;

		case EFFECT_NUM_STAR:
			// 星生成
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_STAR].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_STAR],
					CTexture::TEXTURE_NUM_STAR);
			}
			break;

		case EFFECT_NUM_SHOCKWAVE:
			// 衝撃波生成
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SHOCKWAVE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_SHOCKWAVE],
					CTexture::SEPARATE_TEX_SHOCKWAVE);
			}
			break;

		case EFFECT_NUM_WIND:
			// 風生成
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_WIND].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_WIND],
					CTexture::SEPARATE_TEX_WIND);
			}
			break;

		case EFFECT_NUM_STATUSUP:
			// 状態が良くなったとき
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_STATUSUP].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_STATUSUP],
					CTexture::TEXTURE_NUM_RING);
			}
			break;

		case EFFECT_NUM_STATUSDOWN:
			// 状態が悪くなったとき
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_STATUSDOWN].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_STATUSDOWN],
					CTexture::TEXTURE_NUM_RING);
			}
			break;

		case EFFECT_NUM_EXPLOSION:
			// 爆発
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSION].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSION],
					CTexture::SEPARATE_TEX_EXPLOSION);
			}
			break;

		case EFFECT_NUM_EXPLOSIONCIRCLE:
			// 爆発の円
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSIONCIRCLE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSIONCIRCLE],
					CTexture::TEXTURE_NUM_RING);
			}
			break;

		case EFFECT_NUM_EXPLOSIONSPARK:
			// 爆発の円
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSIONSPARK].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSIONSPARK],
					CTexture::TEXTURE_NUM_EFFECT);
			}
			break;

		case EFFECT_NUM_SINKER:
			// 重り
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SINKER].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_SINKER],
					CTexture::TEXTURE_NUM_SMOKE);
			}
			break;
			//=============================================================================

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
							if (strcmp(aParticleName, "ROT") == 0)
							{
								// 範囲
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Effect[nParticleIndex].rot.x,
									&m_Effect[nParticleIndex].rot.y,
									&m_Effect[nParticleIndex].rot.z);
							}
							if (strcmp(aParticleName, "RANGE") == 0)
							{
								// 範囲
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].Range.x,
									&m_Effect[nParticleIndex].Range.y, 
									&m_Effect[nParticleIndex].Range.z);
							}
							if (strcmp(aParticleName, "SCALE") == 0)
							{
								// 拡大率の設定
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Effect[nParticleIndex].Scale.x,
									&m_Effect[nParticleIndex].Scale.y,
									&m_Effect[nParticleIndex].Scale.z);
							}
							if (strcmp(aParticleName, "MOVETYPE") == 0)
							{
								// 体力
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].movetype);
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
							if (strcmp(aParticleName, "GRAVITYNUM") == 0)
							{
								// 重力の値
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Effect[nParticleIndex].GravityNum.x,
									&m_Effect[nParticleIndex].GravityNum.y,
									&m_Effect[nParticleIndex].GravityNum.z);
							}
							if (strcmp(aParticleName, "TRANSPARENCY") == 0)
							{
								// 透明度を減らす量
								sscanf(aHeadData, "%*s %*s %f", &m_Effect[nParticleIndex].fTransparency);
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