//=============================================================================
//
// �A�C�e�����N���X [item_thunder.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_thunder.h"
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
#define THUNDER_SPEED_NUM	(0)			// ���x�̏��
#define THUNDER_TIME		(180)		// ���x�A�b�v�̃J�E���g

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemThunder::CItemThunder(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	memset(m_bValid, false, sizeof(m_bValid));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemThunder::~CItemThunder()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemThunder * CItemThunder::Create(const int nNumber)
{
	// �������m��
	CItemThunder *pItemThunder = new CItemThunder;

	// !nullcheck
	if (pItemThunder  != nullptr)
	{
		// ����������
		pItemThunder->SetNumber(nNumber);
		pItemThunder->Init();
	}

	return pItemThunder;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemThunder::Init(void)
{
	// �������m��
	CUi *pUi = CUi::Create(SetPosition(this->GetPlayerNum()), ITEM_UI_SIZE);


	// UI�̃|�C���^�ݒ�
	SetUi(pUi);

	// !nullcheck
	if (pUi != nullptr)
	{
		// �e�N�X�`���̃|�C���^�擾
		CTexture *pTexture = GET_TEXTURE_PTR;

		// �e�N�X�`���̐ݒ�
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_THUNDER));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemThunder::Update(void)
{
	// �A�C�e���̍X�V����
	CItem::Update();

	// �A�C�e�����g��ꂽ��
	if (GetUse() == true)
	{
		// �t���[���J�E���^�[��i�߂�
		m_nCounter++;

		// �J�E���^�[�����ʂ�
		if (m_nCounter >= THUNDER_TIME)
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
void CItemThunder::SetItem(void)
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
				if (pPlayer->GetArmor() == false)
				{
					// ����̑��x�𖳂���
					pPlayer->SetSpeed(THUNDER_SPEED_NUM);

					CModelAnime* pModelAnime = pPlayer->GetModelAnime(21);
					D3DXVECTOR3 Rot = pPlayer->GetRot();
					D3DXVECTOR3 EffectCenter = D3DXVECTOR3(pModelAnime->GetMtxWorld()._41,
						pModelAnime->GetMtxWorld()._42,
						pModelAnime->GetMtxWorld()._43);
					CEffectFactory::CreateEffect(EffectCenter, CEffectFactory::EFFECT_TYPE::EFFECT_NUM_THUNDER);

					CEffectFactory::CreateEffect(EffectCenter + D3DXVECTOR3(0.0f, 500.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_LIGHTNINGSTRIKE);

					// �A�C�e���̗L���t���O
					m_bValid[nCount] = true;

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
void CItemThunder::UndoItem(void)
{
	// �v���C���[����
	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// �g�����v���C���[�ȊO
		if (nCount != GetPlayerNum())
		{
			if (m_bValid[nCount])
			{
				// �A�C�e���������Ă���v���C���[���Q��
				CPlayer *pPlayer = CGame::GetPlayer(nCount);

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
