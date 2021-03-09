//=============================================================================
//
// �L�����N�^�[�N���X [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
// �}�N����`
//=============================================================================
#define GRAVITY_POWAR			(0.7f)						// �d�͂̋���
#define GROUND_RIMIT			(0.0f)						// �n�ʂ̐���

//=============================================================================
// static����������
//=============================================================================
 int CCharacter::m_nAllNum = 0;

//=============================================================================
// �R���X�g���N�^
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
	 m_nWeaponTipNum = 0;
	 m_fAngle = 0.0f;
	 m_fSpeed = 0.0f;
	 m_bJump = false;
	 m_fRadius = 0.0f;
	 m_nStateCounter = 0;
	 m_nMaxLife = 0;
	 m_Ctype = CHARACTER_TYPE_NONE;
	 m_nParts = 0;
	 m_pMotion = NULL;
	 memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
 }

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �����̑��
	m_pos = pos;	// ���W�̐ݒ�
	m_rot = rot;	// �p�x�̐ݒ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCharacter::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//�I������
			m_apModelAnime[nCntModelNum]->Uninit();

			//�������̍폜
			delete m_apModelAnime[nCntModelNum];

			//�������̃N���A
			m_apModelAnime[nCntModelNum] = NULL;
		}
	}

	// !nullcheck
	if (m_pMotion != NULL)
	{
		// �I������
		m_pMotion->Uninit();

		//�������̍폜
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCharacter::Update()
{
	// �d��
	if (Gravity() == true)
	{
		if (m_bLanding == false)
		{
			m_bLanding = true;
		}
	}

	// �ړ��ʉ��Z
	m_pos += m_move;

	//�A�j���[�V�����̍X�V����
	ModelAnimeUpdate();

	// �����蔻��
	BodyCollision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCharacter::Draw()
{
	// �`�揈��
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// ���ʂ��i�����j���J�����O

	for (int nCntModelNum = 0; nCntModelNum < m_nParts; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
}

//=============================================================================
// ���f���̐���
//=============================================================================
void CCharacter::ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum)
{
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != NULL)
	{
		// ���f���p�[�c�̐ݒ�
		m_nParts = pXfile->GetModelParts(FileNum);

		//���f���p�[�c�����J��Ԃ�
		for (int nCntModel = 0; nCntModel < m_nParts; nCntModel++)
		{
			CXfile::MODELFILE ModelFile = pXfile->GetModelFile(nCntModel, FileNum);

			if (m_apModelAnime[nCntModel] == NULL)
			{
				// ����������
				m_apModelAnime[nCntModel] = CModelAnime::Create(ModelFile.offsetPos, ModelFile.offsetRot);

				// ���f���̐���
				m_apModelAnime[nCntModel]->SetModel(pXfile->GetHierarchyXfile(nCntModel, FileNum));
			}

			//�e�q�\���̐ݒ�
			if (m_apModelAnime[nCntModel] != NULL)
			{
				//�e���f���̏ꍇ
				if (nCntModel == 0)
				{
					m_apModelAnime[nCntModel]->SetParent(NULL);
				}
				//�q���f���̏ꍇ
				else
				{
					//�����̐e����ݒ肷��
					m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[ModelFile.nParent]);
				}
			}
		}

		// nullcheck
		if (m_pMotion == NULL)
		{
			// �C���X�^���X����
			m_pMotion = CMotion::Create(pXfile->GetModelFileName(FileNum));
		}
	}
}

//=============================================================================
// ���f���A�j���[�V����
//=============================================================================
void CCharacter::ModelAnimeUpdate(void)
{
	// ���[�V�����̍X�V����
	if (m_pMotion != NULL)
	{
		// ���[�V�����̍X�V
		m_pMotion->UpdateMotion(m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// �d��
//=============================================================================
bool CCharacter::Gravity(void)
{
	// �d�͂�������
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// ����

	// ���n�̏���
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
// ���[�V�����̐ݒ�
//=============================================================================
void CCharacter::SetMotion(int nMotionState)
{
	// !nullcheck
	if (m_pMotion != NULL)
	{
		// ���[�V�����̍X�V
		m_pMotion->SetMotion(nMotionState, m_nParts, m_apModelAnime);
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
void CCharacter::BodyCollision(void)
{
//	// �L�����N�^�[�̃|�C���^
//	CCharacter *pCharacter = (CCharacter*)GetTop(PRIORITY_CHARACTER);
//
//	while (pCharacter != NULL)
//	{
//		// �����̔ԍ�����Ȃ��Ƃ�
//		if (pCharacter->m_nCharaNum != m_nCharaNum)
//		{
//			// �~�`�Ɖ~�`�̓����蔻��
//			if (CCollision::CollisionCircularAndCircular(
//				m_pos, pCharacter->m_pos,
//				m_fRadius, pCharacter->m_fRadius) == true)
//			{
//				if (pCharacter->m_Ctype == CHARACTER_TYPE_PLAYER)
//				{
//					// �O�ɉ����o��
//					D3DXVECTOR3 vec = (pCharacter->GetPos() - m_pos);
//					D3DXVec3Normalize(&vec, &vec);
//					vec *= (pCharacter->m_fRadius + m_fRadius);
//
//					D3DXVECTOR3 pos = pCharacter->GetPos();
//					pCharacter->SetPos(GetPos() + vec);
//				}
//				else
//				{
//					// �O�ɉ����o��
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
//		// ���̃|�C���^
//		pCharacter = (CCharacter*)pCharacter->GetNext();
//	}
}

//=============================================================================
// ���W�̐ݒ�
//=============================================================================
void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �Â����W�̐ݒ�
//=============================================================================
void CCharacter::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �p�x�̐ݒ�
//=============================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �̗͂̐ݒ�
//=============================================================================
void CCharacter::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// �W�����v�̐ݒ�
//=============================================================================
void CCharacter::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// �n�ʂɂ���t���O�ݒ�
//=============================================================================
void CCharacter::SetLanding(bool bLanding)
{
	m_bLanding = bLanding;
}

//=============================================================================
// ���a�̐ݒ�
//=============================================================================
void CCharacter::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
}

//=============================================================================
// �L�����N�^�[�̃^�C�v�ݒ�
//=============================================================================
void CCharacter::SetCType(CHARACTER_TYPE Ctype)
{
	m_Ctype = Ctype;
}

//=============================================================================
// �L�����N�^�[�̑��x�ݒ�
//=============================================================================
void CCharacter::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

//=============================================================================
// ����̃p�[�c�ԍ��ݒ�
//=============================================================================
void CCharacter::SetWeaponTipNum(int nWeaponTipNum)
{
	m_nWeaponTipNum = nWeaponTipNum;
}

//=============================================================================
// ���̍��{�̃p�[�c�ԍ��ݒ�
//=============================================================================
void CCharacter::SetWeaponRootNum(int nWeaponRootNum)
{
	m_nWeaponRootNum = nWeaponRootNum;
}

//=============================================================================
// ��ԃJ�E���^�[�̐ݒ�
//=============================================================================
void CCharacter::SetStateCounter(int nStateCounter)
{
	m_nStateCounter = nStateCounter;
}