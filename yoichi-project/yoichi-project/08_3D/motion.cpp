//=============================================================================
//
// ���[�V�����N���X [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "motion.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//�K�w���f���N���X�̃R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{
	m_nKey = 0;
	memset(m_Motion, 0, sizeof(m_Motion));
	m_apKeyInfo = NULL;
	m_nMotionState = 0;
	m_nNumKey = 0;					// �L�[�̑���
	m_nCountMotion = 0;				// ���[�V�����J�E���^�[
	m_nMotionInterval = 0;			// ���[�V�����̃C���^�[�o��
	m_nKey = 0;						// ���݃L�[��No
	m_bMotionPlaing = false;		// ���[�V�����̍Đ�

	m_diffPos = ZeroVector3;			// �ύX���W
	m_diffRot = ZeroVector3;			// �ύX�p�x
}

//=============================================================================
//�K�w���f���N���X�̃f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
//�K�w���f���N���X�̃N���G�C�g����
//=============================================================================
CMotion * CMotion::Create(char *pFileName)
{
	//�K�w���f���N���X�̃|�C���^�ϐ�
	CMotion *pMotion = NULL;

	//�C���X�^���X����
	pMotion = new CMotion;

	// nullcheck
	if (pMotion != NULL)
	{
		//�����������Ăяo��
		pMotion->Init();

		// �t�@�C���f�[�^�ǂݍ���
		pMotion->ReadMotionFile(pFileName);
	}
	//���s���Ă����ꍇ
	else
	{
		return NULL;
	}

	return pMotion;
}

//=============================================================================
//�K�w���f���N���X�̏���������
//=============================================================================
HRESULT CMotion::Init(void)
{

	return S_OK;
}

//=============================================================================
//�K�w���f���N���X�̏I������
//=============================================================================
void CMotion::Uninit(void)
{
	
}

//=============================================================================
//�K�w���f���N���X�̍X�V����
//=============================================================================
void CMotion::Update(void)
{
}

//=============================================================================
// ���[�V�����̍X�V����
//=============================================================================
void CMotion::UpdateMotion(int nMaxParts, CModelAnime **pModelAnime)
{
	KEY *pKey[MAX_MODEL_PARTS];

	//���݃L�[���ő�L�[�������̏ꍇ
	if (m_nKey < m_Motion[m_nMotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
		{
			// �e���f���p�[�c�̃L�[�ݒ�
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

						// 1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
						m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX - startRot.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY - startRot.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ - startRot.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					}
					else
					{
						// 1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
						m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fPosX) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fPosY) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fPosZ) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

						// 1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
						m_diffRot.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fRotX) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fRotY) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
						m_diffRot.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ - m_Motion[m_nMotionState].aKeyInfo[m_nKey - 1].aKey[nCntModel].fRotZ) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					}
				}
				else
				{
					// 1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
					m_diffPos.x = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX - startPos.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffPos.y = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY - startPos.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
					m_diffPos.z = (m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ - startPos.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

					// 1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
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

				//�ʒu�̐ݒ�
				pModelAnime[nCntModel]->SetPosAnime(setPos);

				//�����̐ݒ�
				pModelAnime[nCntModel]->SetRotAnime(setRot);
			}
		}

		//���[�V�����J�E���^�[�̉��Z
		m_nCountMotion++;

		//���݃L�[�̍Đ��t���[���ɒB������
		if (m_nCountMotion >= m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame)
		{
			//�L�[���P�i�߂�
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//���[�v����Ȃ�
		if (m_Motion[m_nMotionState].bLoop == true)
		{
			m_nKey = 0;
			m_nCountMotion = 0;
		}
		else
		{
			// ���[�v���Ȃ��Ƃ�
			m_nMotionInterval++;

			if (m_nMotionInterval == 10)
			{
				m_bMotionPlaing = false;
				m_nMotionInterval = 0;
			}

			// �A�C�h�����[�V�����ɖ߂�
			SetMotion(0, nMaxParts, pModelAnime);
		}
	}
}

//=============================================================================
// ���[�V�����t�@�C���ǂݍ���
//=============================================================================
HRESULT CMotion::ReadMotionFile(char *pFileName)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	// ���f���̃C���f�b�N�X
	int nMotionType = 0;	// ���[�V�����̃^�C�v
	int nKeyNum = 0;		// �L�[�ԍ�
	int nMotionNum = 0;		// ���[�V�����ԍ�

	// �t�@�C���I�[�v��
	pFile = fopen(pFileName, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

			//���[�V�����Z�b�g
			if (strcmp(aModeName, "MOTIONSET") == 0)
			{
				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aModeName, "END_MOTIONSET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					//���[�v���̎擾
					if (strcmp(aModeName, "LOOP") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].bLoop);
					}

					//�L�[���̎擾
					if (strcmp(aModeName, "NUM_KEY") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].nNumKey);
					}

					if (strcmp(aModeName, "KEYSET") == 0)
					{
						//END_KEYSET�ɂȂ�܂ŌJ��Ԃ�
						while (strcmp(aModeName, "END_KEYSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							//�t���[�����̎擾
							if (strcmp(aModeName, "FRAME") == 0)
							{
								sscanf(aHeadData, "%*s %*s %d", &m_Motion[nMotionType].aKeyInfo[nMotionNum].nFrame);
							}

							//�e�L�[�̃I�t�Z�b�g���̎擾
							if (strcmp(aModeName, "KEY") == 0)
							{
								//END_KEY�ɂȂ�܂ŌJ��Ԃ�
								while (strcmp(aModeName, "END_KEY") != 0)
								{
									//���ǂݍ���Ń��[�h���𒊏o
									fgets(aHeadData, sizeof(aHeadData), pFile);
									sscanf(aHeadData, "%s", aModeName);

									//�ʒu�̎擾
									if (strcmp(aModeName, "POS") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosZ);
									}

									//�����̎擾
									if (strcmp(aModeName, "ROT") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotZ);
									}
								}
								//�ǂݏI�������J�E���g��1�i�߂�
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

//=============================================================================
// ���[�V�����̐ݒ�
//=============================================================================
void CMotion::SetMotion(int nMotion, int nMaxParts, CModelAnime **pModelAnime)
{
	// ���̃��[�V�����ƈ������
	if (m_nMotionState != nMotion)
	{
		// �l�̏�����
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
				//�J�n�ʒu
				pos.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
				pos.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
				pos.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

				//�J�n����
				rot.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
				rot.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
				rot.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

				//�ʒu�̐ݒ�
				pModelAnime[nCntModel]->SetPosAnime(pos);

				//�����̐ݒ�
				pModelAnime[nCntModel]->SetRotAnime(rot);
			}
		}
	}
}