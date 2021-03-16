//=============================================================================
//
// �A�C�e�����H���N���X [item_mhand.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_mhand.h"
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
#define MHAND_TIME			(120)	// �A�C�e�����ʂ̃J�E���g
#define MHAND_RADIUS_UP		(5)		// ���a�̊g�嗦

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemMhand::CItemMhand(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	m_fPlayerRadius = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemMhand::~CItemMhand()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemMhand * CItemMhand::Create(const int nNumber)
{
	// �������m��
	CItemMhand *pItemMhand = new CItemMhand;

	// !nullcheck
	if (pItemMhand != nullptr)
	{
		// ����������
		pItemMhand->Init();
		pItemMhand->SetNumber(nNumber);
	}

	return pItemMhand;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemMhand::Init(void)
{
	// �������m��
	CUi *pUi = CUi::Create(ITEM_UI_POS, ITEM_UI_SIZE);

	// UI�̃|�C���^�ݒ�
	SetUi(pUi);

	// !nullcheck
	if (pUi != nullptr)
	{
		// �e�N�X�`���̃|�C���^�擾
		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// �e�N�X�`���̐ݒ�
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_MHAND));
	}

	// �v���C���[�̔ԍ�
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �v���C���[�̔��a
		m_fPlayerRadius = pPlayer->GetRadius();
	}


	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemMhand::Update(void)
{
	// �A�C�e���̍X�V����
	CItem::Update();

	// �A�C�e�����g��ꂽ��
	if (GetUse() == true)
	{
		// �t���[���J�E���^�[��i�߂�
		m_nCounter++;

		// �J�E���^�[�����ʂ�
		if (m_nCounter >= MHAND_TIME)
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
void CItemMhand::SetItem(void)
{
	if (GetUse() == false)
	{
		// �A�C�e���������Ă���v���C���[���Q��
		CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

		// !nullcheck
		if (pPlayer != nullptr)
		{
			// ���a���㏸
			pPlayer->SetRadius(pPlayer->GetRadius() * MHAND_RADIUS_UP);
		}

		// �g�p��Ԃɂ���
		SetUse(true);

		// Ui�̏I������
		UiUninit();
	}
}

//=============================================================================
// �A�C�e���̌��ʂ�߂�
//=============================================================================
void CItemMhand::UndoItem(void)
{
	// �A�C�e���������Ă���v���C���[���Q��
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ���a��߂�
		pPlayer->SetRadius(m_fPlayerRadius);
	}

	// �I���t���O�𗧂Ă�
	SetEnd(true);
}