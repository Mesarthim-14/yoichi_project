//=============================================================================
//
// �A�C�e���{�b�N�X�N���X���� [itembombbox.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_bombbox.h"
#include "renderer.h"
#include "collision.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "game.h"
#include "player.h"
#include "item_bluewing.h"
#include "item_vortex.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BOMBBOX_RADIUS				(100.0f)		// �����蔻��̔��a
#define BOMBBOX_ROTATION_NUM		(0.01f)			// ��]�̒l
#define BOMBBOX_ROTATION_NUM_ALL	(D3DXVECTOR3(BOMBBOX_ROTATION_NUM, BOMBBOX_ROTATION_NUM, BOMBBOX_ROTATION_NUM))	// ��]�̒l
#define BOMB_SPEED_NUM				(0)				// ���x�̏��
#define BOMB_TIME					(120)			// ���xDOWN�̃J�E���g

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemBombBox * CItemBombBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPlayerNum)
{
	// �������m��
	CItemBombBox *pItemBombBox = new CItemBombBox;

	// nullcheck
	if (pItemBombBox != nullptr)
	{
		pItemBombBox->SetPos(pos);
		pItemBombBox->SetSize(size);
		// ����������
		pItemBombBox->Init();

		// �v���C���[�̔ԍ�
		pItemBombBox->m_nPlayerNum = nPlayerNum;
	}

	return pItemBombBox;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemBombBox::CItemBombBox(PRIORITY Priority) : CModel(Priority)
{
	m_nPlayerNum = 0;
	m_nCounter = 0;
	m_nHitPlayer = 0;
	m_bUse = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBombBox::~CItemBombBox()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemBombBox::Init(void)
{
	// ����������
	CModel::Init();

	// X�t�@�C���̏��擾
	CXfile *pXfile = GET_XFILE_PTR;

	// ���f�����̐ݒ�
	BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_BOMB_BOX));
	BindTexture(pXfile->GetXfileTexture(CXfile::XFILE_NUM_BOMB_BOX));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItemBombBox::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBombBox::Update(void)
{
	// ��]�̏���
	Rotation(BOMBBOX_ROTATION_NUM_ALL);

	// �X�V����
	CModel::Update();

	 // �����蔻��
	Collision();

	// �g�p����������
	if (m_bUse == true)
	{
		m_nCounter++;

		// ���Ԃ�����
		if (m_nCounter >= BOMB_TIME)
		{
			// �I���t���O
			UndoBox();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItemBombBox::Draw(void)
{
	if (m_bUse == false)
	{
		// �`�揈��
		CModel::Draw();

	}
}

//=============================================================================
// �{�b�N�X�̌��ʂ̏I��
//=============================================================================
void CItemBombBox::UndoBox(void)
{
	// �A�C�e���������Ă���v���C���[���Q��
	CPlayer *pPlayer = CGame::GetPlayer(m_nHitPlayer);

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �X�s�[�h���㏸
		pPlayer->SetSpeed(pPlayer->GetBaseSpeed());
	}

	// �I������
	Uninit();
}

//=============================================================================
// �����蔻��̏���
//=============================================================================
void CItemBombBox::Collision(void)
{
	// �v���C���[�̐�
	int nPlayerNum = CGame::GetPlayerNum();

	// �v���C���[�����
	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		if (m_nPlayerNum != nCount)
		{
			// �v���C���[�̊֐�
			CPlayer *pPlayer = CGame::GetPlayer(nCount);

			// �����蔻��
			if (CCollision::CollisionCircularAndCircular(
				GetPos(), pPlayer->GetPos(),
				BOMBBOX_RADIUS, pPlayer->GetRadius()) == true)
			{
				// !nullcheck
				if (pPlayer != nullptr)
				{
					// Armor���t���Ă��Ȃ�������
					if (pPlayer->GetArmor() == false)
					{
						// ���������v���C���[�̔ԍ�
						m_nHitPlayer = nCount;

						// ����̑��x�𖳂���
						pPlayer->SetSpeed(BOMB_SPEED_NUM);

						// Armor���������
						pPlayer->SetArmor(true);

						// ��ԂƂ��̏���
						pPlayer->SetFly(false);
						pPlayer->SetUseGravity(true);

						// �g�p��
						m_bUse = true;
					}
				}
			}
		}
	}
}