//=============================================================================
//
// �G�t�F�N�g�����N���X [effect_factory.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "effect_factory.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "effect_3d.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_TEXTURE_NAME	("data/Text/effect.txt")

//=============================================================================
// static������
//=============================================================================
CEffectFactory::EFFECT CEffectFactory::m_Effect[EFFECT_NUM_MAX] = {};			// �\���̏��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffectFactory::CEffectFactory()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffectFactory::~CEffectFactory()
{
}

//=============================================================================
// �p�[�e�B�N���̐���
//=============================================================================
void CEffectFactory::CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type)
{
	switch (type)
	{
		// ������Ȋ����Ŏg���܂�

		//=============================================================================
		// Author : Ito Yogo
		//=============================================================================
		case EFFECT_NUM_PARTICLE:
			// �����������̃p�[�e�B�N������
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_PARTICLE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_PARTICLE],
					CTexture::TEXTURE_NUM_EFFECT);
			}
			break;

		case EFFECT_NUM_LIGHTNINGSTRIKE:
			// ��������
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_LIGHTNINGSTRIKE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_LIGHTNINGSTRIKE],
					CTexture::SEPARATE_TEX_LIGHTNINGSTRIKE);
			}
			break;

		case EFFECT_NUM_THUNDER:
			// ������
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_THUNDER].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_THUNDER],
					CTexture::SEPARATE_TEX_THUNDER);
			}
			break;

		case EFFECT_NUM_STAR:
			// ������
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_STAR].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_STAR],
					CTexture::TEXTURE_NUM_STAR);
			}
			break;

		case EFFECT_NUM_SHOCKWAVE:
			// �Ռ��g����
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_SHOCKWAVE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_SHOCKWAVE],
					CTexture::SEPARATE_TEX_SHOCKWAVE);
			}
			break;

		case EFFECT_NUM_WIND:
			// ������
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_WIND].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_WIND],
					CTexture::SEPARATE_TEX_WIND);
			}
			break;

		case EFFECT_NUM_STATUSUP:
			// ��Ԃ��ǂ��Ȃ����Ƃ�
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_STATUSUP].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_STATUSUP],
					CTexture::TEXTURE_NUM_RING);
			}
			break;

		case EFFECT_NUM_STATUSDOWN:
			// ��Ԃ������Ȃ����Ƃ�
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_STATUSDOWN].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_STATUSDOWN],
					CTexture::TEXTURE_NUM_RING);
			}
			break;

		case EFFECT_NUM_EXPLOSION:
			// ����
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSION].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSION],
					CTexture::SEPARATE_TEX_EXPLOSION);
			}
			break;

		case EFFECT_NUM_EXPLOSIONCIRCLE:
			// �����̉~
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSIONCIRCLE].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSIONCIRCLE],
					CTexture::TEXTURE_NUM_RING);
			}
			break;

		case EFFECT_NUM_EXPLOSIONSPARK:
			// �����̉~
			for (int nCount = 0; nCount < m_Effect[EFFECT_NUM_EXPLOSIONSPARK].nNum; nCount++)
			{
				CEffect::Create(pos, m_Effect[EFFECT_NUM_EXPLOSIONSPARK],
					CTexture::TEXTURE_NUM_EFFECT);
			}
			break;

		case EFFECT_NUM_SINKER:
			// �d��
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
// �t�@�C���̓ǂݍ���
//=============================================================================
HRESULT CEffectFactory::ReadFile(void)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// ���f���̃C���f�b�N�X

	// �t�@�C���I�[�v��
	pFile = fopen(EFFECT_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "PARTICLESET") == 0)
			{
				//�C���f�b�N�X���ŏ��ɖ߂�
				nParticleIndex = 0;

				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aParticleName, "END_PARTICLESET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "EFFECTSET") == 0)
					{
						//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (strcmp(aParticleName, "END_EFFECTSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].size.x,
									&m_Effect[nParticleIndex].size.y,
									&m_Effect[nParticleIndex].size.z);
							}
							if (strcmp(aParticleName, "MOVE") == 0)
							{
								// �ړ���
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].move.x,
									&m_Effect[nParticleIndex].move.y,
									&m_Effect[nParticleIndex].move.z);
							}
							if (strcmp(aParticleName, "ROT") == 0)
							{
								// �͈�
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Effect[nParticleIndex].rot.x,
									&m_Effect[nParticleIndex].rot.y,
									&m_Effect[nParticleIndex].rot.z);
							}
							if (strcmp(aParticleName, "RANGE") == 0)
							{
								// �͈�
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Effect[nParticleIndex].Range.x,
									&m_Effect[nParticleIndex].Range.y, 
									&m_Effect[nParticleIndex].Range.z);
							}
							if (strcmp(aParticleName, "SCALE") == 0)
							{
								// �g�嗦�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Effect[nParticleIndex].Scale.x,
									&m_Effect[nParticleIndex].Scale.y,
									&m_Effect[nParticleIndex].Scale.z);
							}
							if (strcmp(aParticleName, "MOVETYPE") == 0)
							{
								// �̗�
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].movetype);
							}
							if (strcmp(aParticleName, "LIFE") == 0)
							{
								// �̗�
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nLife);
							}
							if (strcmp(aParticleName, "NUM") == 0)
							{
								// ��
								sscanf(aHeadData, "%*s %*s %d", &m_Effect[nParticleIndex].nNum);
							}
							if (strcmp(aParticleName, "COLOR") == 0)
							{
								// �F
								sscanf(aHeadData, "%*s %*s %f %f %f %f", 
									&m_Effect[nParticleIndex].color.r,
									&m_Effect[nParticleIndex].color.g, 
									&m_Effect[nParticleIndex].color.b,
									&m_Effect[nParticleIndex].color.a);
							}
							if (strcmp(aParticleName, "GRAVITY") == 0)
							{
								// �d��
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bGravity);
							}
							if (strcmp(aParticleName, "GRAVITYNUM") == 0)
							{
								// �d�͂̒l
								sscanf(aHeadData, "%*s %*s %f %f %f",
									&m_Effect[nParticleIndex].GravityNum.x,
									&m_Effect[nParticleIndex].GravityNum.y,
									&m_Effect[nParticleIndex].GravityNum.z);
							}
							if (strcmp(aParticleName, "TRANSPARENCY") == 0)
							{
								// �����x�����炷��
								sscanf(aHeadData, "%*s %*s %f", &m_Effect[nParticleIndex].fTransparency);
							}
							if (strcmp(aParticleName, "ALPHA") == 0)
							{
								// �����ɂ��邩
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].bAlpha);
							}
							if (strcmp(aParticleName, "ALPHANUM") == 0)
							{
								// �A���t�@�e�X�g�̒l
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Effect[nParticleIndex].nAlphaNum);
							}
							if (strcmp(aParticleName, "ANIMATION") == 0)
							{
								// �A�j���[�V����
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bAnimation);
							}
							if (strcmp(aParticleName, "BLEND") == 0)
							{
								// �A�j���[�V����
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}
							if (strcmp(aParticleName, "PRIORITY") == 0)
							{
								// �A�j���[�V����
								sscanf(aHeadData, "%*s %*s %d ", (int*)&m_Effect[nParticleIndex].bBlend);
							}

							
						}

						//�C���f�b�N�X���P�i�߂�
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

		//�t�@�C���N���[�Y
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}