//=============================================================================
//
// �A�C�e���o���A�N���X [item_barrier.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_barrier.h"
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
#define BARRIER_TIME			(200)	// �o���A�̊Ԋu

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemBarrier::CItemBarrier(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBarrier::~CItemBarrier()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemBarrier * CItemBarrier::Create(const int nNumber)
{
	// �������m��
	CItemBarrier *pItemBarrier = new CItemBarrier;

	// !nullcheck
	if (pItemBarrier != nullptr)
	{
		// ����������
		pItemBarrier->Init();
		pItemBarrier->SetNumber(nNumber);
	}

	return pItemBarrier;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemBarrier::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_BARRIER));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBarrier::Update(void)
{
	// �A�C�e���̍X�V����
	CItem::Update();

	// �A�C�e�����g��ꂽ��
	if (GetUse() == true)
	{
		// �t���[���J�E���^�[��i�߂�
		m_nCounter++;

		// �J�E���^�[�����ʂ�
		if (m_nCounter >= BARRIER_TIME)
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
void CItemBarrier::SetItem(void)
{
	// �A�C�e���������Ă���v���C���[���Q��
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// ���G��Ԃɂ���
		pPlayer->SetArmor(true);
	}

	// �g�p��Ԃɂ���
	SetUse(true);

	// Ui�̏I������
	UiUninit();
}

//=============================================================================
// �A�C�e���̌��ʂ�߂�
//=============================================================================
void CItemBarrier::UndoItem(void)
{
	// �A�C�e���������Ă���v���C���[���Q��
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �X�s�[�h���㏸
		pPlayer->SetArmor(false);
	}

	// �I���t���O�𗧂Ă�
	SetEnd(true);
}