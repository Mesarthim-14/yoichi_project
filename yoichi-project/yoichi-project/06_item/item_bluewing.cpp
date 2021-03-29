//=============================================================================
//
// �A�C�e�����H���N���X [item_bluewing.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_bluewing.h"
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
#define BLUE_WING_SPEED_UP_NUM	(2)		// ���x�̏��
#define BLUE_WING_TIME			(180)	// ���x�A�b�v�̃J�E���g

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemBlueWing::CItemBlueWing(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBlueWing::~CItemBlueWing()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemBlueWing * CItemBlueWing::Create(const int nNumber)
{
	// �������m��
	CItemBlueWing *pItemBlueWing = new CItemBlueWing;

	// !nullcheck
	if (pItemBlueWing != nullptr)
	{
		// ����������
		pItemBlueWing->Init();
		pItemBlueWing->SetNumber(nNumber);
	}

	return pItemBlueWing;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemBlueWing::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_BLUE_WING));
	}
	
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBlueWing::Update(void)
{
	// �A�C�e���̍X�V����
	CItem::Update();

	// �A�C�e�����g��ꂽ��
	if (GetUse() == true)
	{
		// �t���[���J�E���^�[��i�߂�
		m_nCounter++;

		// �J�E���^�[�����ʂ�
		if (m_nCounter >= BLUE_WING_TIME)
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
void CItemBlueWing::SetItem(void)
{
	// �A�C�e���������Ă���v���C���[���Q��
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �X�s�[�h���㏸
		pPlayer->SetSpeed(pPlayer->GetBaseSpeed() * BLUE_WING_SPEED_UP_NUM);

		// �g�p��Ԃɂ���
		SetUse(true);

		// Ui�̏I������
		UiUninit();
	}
}

//=============================================================================
// �A�C�e���̌��ʂ�߂�
//=============================================================================
void CItemBlueWing::UndoItem(void)
{
	// �A�C�e���������Ă���v���C���[���Q��
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// !nullcheck
	if (pPlayer != nullptr)
	{
		// �X�s�[�h���㏸
		pPlayer->SetSpeed(pPlayer->GetBaseSpeed());
	}

	// �I���t���O�𗧂Ă�
	SetEnd(true);
}
