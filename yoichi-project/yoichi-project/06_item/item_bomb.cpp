//=============================================================================
//
// �A�C�e���{���N���X [item_bomb.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_bomb.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "item_bombbox.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemBomb::CItemBomb(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBomb::~CItemBomb()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemBomb * CItemBomb::Create(const int nNumber)
{
	// �������m��
	CItemBomb *pItemBomb = new CItemBomb;

	// !nullcheck
	if (pItemBomb != nullptr)
	{
		// ����������
		pItemBomb->Init();
		pItemBomb->SetNumber(nNumber);
	}

	return pItemBomb;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemBomb::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_BOMB));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBomb::Update(void)
{
	// �A�C�e���̍X�V����
	CItem::Update();

	// �A�C�e�����g��ꂽ��
	if (GetUse() == true)
	{
		// �t���[���J�E���^�[��i�߂�
		m_nCounter++;
	}
}

//=============================================================================
// �A�C�e���̌��ʐݒ�
//=============================================================================
void CItemBomb::SetItem(void)
{
	// �v���C���[�̔ԍ��擾
	int nPlayerNum = GetPlayerNum();

	// ���W
	D3DXVECTOR3 pos = CGame::GetPlayer(nPlayerNum)->GetPos();
	pos.y += PLAYER_BASE_POS_Y;

	// �U�{�b�N�X�̐���
	CItemBombBox::Create(pos, MODEL_DEFAULT_SIZE, nPlayerNum);

	// Ui�̏I������
	UiUninit();

	// �I���t���O
	UndoItem();
}

//=============================================================================
// �A�C�e���̌��ʂ�߂�
//=============================================================================
void CItemBomb::UndoItem(void)
{
	// �I���t���O
	SetEnd(true);
}