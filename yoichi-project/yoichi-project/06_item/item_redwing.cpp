//=============================================================================
//
// �A�C�e���Ԃ��H���N���X [item_redwing.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_redwing.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RED_WING_SPEED_DOWN_NUM	(2)				// ���x�̏��
#define RED_WING_TIME			(180)			// ���x�A�b�v�̃J�E���g

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemRedWing::CItemRedWing(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	memset(m_bValid, false, sizeof(m_bValid));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemRedWing::~CItemRedWing()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemRedWing * CItemRedWing::Create(const int nNumber)
{
	// �������m��
	CItemRedWing *pItemRedWing = new CItemRedWing;

	// !nullcheck
	if (pItemRedWing != nullptr)
	{
		// ����������
		pItemRedWing->Init();
		pItemRedWing->SetNumber(nNumber);
	}

	return pItemRedWing;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemRedWing::Init(void)
{
	// �������m��
	CUi *pUi = CUi::Create(CItem::SetPosition(GetPlayerNum()), ITEM_UI_SIZE);

	// UI�̃|�C���^�ݒ�
	SetUi(pUi);

	// !nullcheck
	if (pUi != nullptr)
	{
		// �e�N�X�`���̃|�C���^�擾
		CTexture *pTexture = GET_TEXTURE_PTR;

		// �e�N�X�`���̐ݒ�
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_RED_WING));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemRedWing::Update(void)
{
	// �A�C�e���̍X�V����
	CItem::Update();

	// �A�C�e�����g��ꂽ��
	if (GetUse() == true)
	{
		// �t���[���J�E���^�[��i�߂�
		m_nCounter++;

		// �J�E���^�[�����ʂ�
		if (m_nCounter >= RED_WING_TIME)
		{
			// �A�C�e���̌��ʂ�߂�
			UndoItem();

			m_nCounter = 0;
		}
	}
}

//=============================================================================
// �A�C�e���̌��ʐݒ�
//=============================================================================
void CItemRedWing::SetItem(void)
{
	// �v���C���[����
	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// �g�����v���C���[�ȊO
		if (nCount != GetPlayerNum())
		{
			// �A�C�e���������Ă���v���C���[���Q��
			CPlayer *pPlayer = CGame::GetPlayer(nCount);

			// !nullcheck
			if (pPlayer != nullptr)
			{
				// �v���C���[�����G����Ȃ�������
				if (pPlayer->GetArmor() == false)
				{
					if (GetUse() == false)
					{
						// ����̑��x��ቺ
						pPlayer->SetSpeed(pPlayer->GetBaseSpeed() / RED_WING_SPEED_DOWN_NUM);

						// ���ʂ�L���ɂ���
						m_bValid[nCount] = true;
					}
				}
			}
		}
	}

	// �g�p�t���O
	SetUse(true);

	// Ui�̏I������
	UiUninit();
}

//=============================================================================
// �A�C�e���̌��ʂ�߂�
//=============================================================================
void CItemRedWing::UndoItem(void)
{
	// �v���C���[����
	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// �g�����v���C���[�ȊO
		if (nCount != GetPlayerNum())
		{
			// �A�C�e���������Ă���v���C���[���Q��
			CPlayer *pPlayer = CGame::GetPlayer(nCount);

			if (m_bValid[nCount] == true)
			{
				// !nullcheck
				if (pPlayer != nullptr)
				{
					// �X�s�[�h���㏸
					pPlayer->SetSpeed(pPlayer->GetBaseSpeed());

					// �A�C�e���̗L���t���O
					m_bValid[nCount] = false;
				}
			}
		}
	}

	// �I���t���O�𗧂Ă�
	SetEnd(true);
}