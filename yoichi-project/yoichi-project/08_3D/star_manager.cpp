//=============================================================================
//
// �A�C�e���Ǘ��N���X [star_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "star_manager.h"
#include "manager.h"
#include "renderer.h"
#include "itembox.h"
#include "star.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_STAR_NUM			(30)						// �A�C�e���̏o����
#define STAR_POS_INTERBAL_XToZ	(1800.0f)					// ���̊Ԋu
#define STAR_POS_INTERBAL_Y		(1000.0f)					// ���̊Ԋu
#define STAR_POS_LIMIT_XToZ		(-MAP_LIMIT+(MAP_LIMIT/2))	// �o���͈̔�
#define STAR_POS_LIMIT_Y		(3000.0f)					// �o���͈̔�
#define STAR_COLOR_CHANGE_FLAME	(1800)						// �F��ς���t���[��

//=============================================================================
// static����������
//=============================================================================
CStar::STAR_COLOR_TYPE CStarManager::m_GameColor = CStar::STAR_COLOR_TYPE_NONE;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CStarManager::CStarManager()
{
	m_nCounter = 0;
	memset(m_bMapFlag, 0, sizeof(m_bMapFlag));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CStarManager::~CStarManager()
{
	m_GameColor = CStar::STAR_COLOR_TYPE_NONE;
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CStarManager * CStarManager::Create(void)
{
	// �������m��
	CStarManager *pStarFactory = new CStarManager;

	// !nullcheck
	if (pStarFactory != nullptr)
	{
		// ����������
		pStarFactory->Init();
	}

	return pStarFactory;
}

//=============================================================================
// ����������
//=============================================================================
void CStarManager::Init(void)
{
	// �X�^�[�̐���
	CreateStar();

	// �{�����オ��F�̐ݒ�
	SetGameColor();
}

//=============================================================================
// �I������
//=============================================================================
void CStarManager::Uninit(void)
{
	// �������m��
	for (unsigned nCount = 0; nCount < m_pStar.size(); nCount++)
	{
		// !nullcheck
		if (m_pStar[nCount] != nullptr)
		{
			// �I������
			m_pStar[nCount]->Uninit();
			m_pStar[nCount] = nullptr;
		}
	}

	// �z�񂪂����
	if (m_pStar.size() != NULL)
	{
		// �z��̃N���A
		m_pStar.clear();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CStarManager::Update(void)
{
	m_nCounter++;

	// �J�E���^�[
	if (m_nCounter <= STAR_COLOR_CHANGE_FLAME)
	{
		// �Q�[���̐F�̐ݒ�
		SetGameColor();

		m_nCounter = 0;
	}

	// ��萔�ȉ��ɂȂ�����
	if (m_pStar.size() < MAX_STAR_NUM)
	{
		// ���̐���
		CreateStar();
	}

	// �z��0�łȂ����
	if (m_pStar.size() != NULL)
	{
		// �T�C�Y����
		for (unsigned nCount = 0; nCount < m_pStar.size(); nCount++)
		{
			// �����蔻��
			if (m_pStar[nCount]->Collision() == true)
			{
				// �X�^�[�����炷
				SubStarNum(nCount, m_pStar[nCount]->GetPosNumber());
			}
		}
	}
}

//=============================================================================
// �A�C�e���N���X�̐���
//=============================================================================
void CStarManager::CreateStar(void)
{
	// �ő吔��菭�Ȃ�������
	while (m_pStar.size() < MAX_STAR_NUM)
	{
		// �z��̔ԍ������߂�
		int nNumX = rand() % STAR_CREATE_SIZE;
		int nNumY = rand() % STAR_CREATE_SIZE;
		int nNumZ = rand() % STAR_CREATE_SIZE;

		// �g���Ă��Ȃ�������
		if (m_bMapFlag[nNumX][nNumY][nNumZ] == false)
		{
			// ���W�ݒ�
			D3DXVECTOR3 pos = D3DXVECTOR3(
				STAR_POS_LIMIT_XToZ +(nNumX * STAR_POS_INTERBAL_XToZ),
				STAR_POS_LIMIT_Y + (nNumY * STAR_POS_INTERBAL_Y),
				STAR_POS_LIMIT_XToZ + (nNumZ * STAR_POS_INTERBAL_XToZ));

			// ���W�ԍ��ݒ�
			CStar::POS_NUMBER posNumber = { nNumX, nNumY, nNumZ };

			// ���̐���
			m_pStar.push_back(CStar::Create(pos, posNumber));

			m_bMapFlag[nNumX][nNumY][nNumZ] = true;
		}
	}
}

//=============================================================================
// �X�^�[�̑��������炷
//=============================================================================
void CStarManager::SubStarNum(int nCount, CStar::POS_NUMBER posNum)
{
	// ���W�ԍ��̃t���O������
	m_bMapFlag[posNum.nNumX][posNum.nNumY][posNum.nNumZ] = false;

	// ����������������
	m_pStar.erase(m_pStar.begin() + nCount);
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
CStar::STAR_COLOR_TYPE CStarManager::SetColorType(void)
{
	// ����
	int nColorType = rand() % (int)CStar::STAR_COLOR_TYPE_MAX;

	return (CStar::STAR_COLOR_TYPE)nColorType;
}

//=============================================================================
// �Q�[���̐F�ݒ�
//=============================================================================
void CStarManager::SetGameColor(void)
{
	// �Q�[���̐F�̐ݒ�
	m_GameColor = SetColorType();
}