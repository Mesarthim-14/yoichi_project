//=============================================================================
//
// �A�C�e���Q�N���X [item_vortex.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_vortex.h"
#include "renderer.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "ui.h"
#include "texture.h"
#include "game.h"
#include "player.h"
#include "collision.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define VORTEX_TIME			(50)	// ���ʂ̗L���J�E���g
#define VORTEX_RADIUS_UP	(0.1f)	// ���a�̊g�嗦

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemVortex::CItemVortex(PRIORITY Priority) : CItem(Priority)
{
	m_nCounter = 0;
	m_fRadiusNum = 1.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemVortex::~CItemVortex()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemVortex * CItemVortex::Create(const int nNumber)
{
	// �������m��
	CItemVortex *pItemVortex = new CItemVortex;

	// !nullcheck
	if (pItemVortex != nullptr)
	{
		// ����������
		pItemVortex->Init();
		pItemVortex->SetNumber(nNumber);
	}

	return pItemVortex;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemVortex::Init(void)
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
		pUi->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_ITEM_VORTEX));
	}

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemVortex::Update(void)
{
	// �A�C�e�����g��ꂽ��
	if (GetUse() == true)
	{
		// �t���[���J�E���^�[��i�߂�
		m_nCounter++;

		// ���a�g��
		RadiusUp();

		// �J�E���^�[�����ʂ�
		if (m_nCounter >= VORTEX_TIME)
		{
			// �A�C�e���̌��ʂ�߂�
			UndoItem();

			m_nCounter = 0;
		}
	}
}

//=============================================================================
// ���a�̊g��
//=============================================================================
void CItemVortex::RadiusUp(void)
{
	// �{�������Z
	m_fRadiusNum += VORTEX_RADIUS_UP;

	// �A�C�e���������Ă���v���C���[���Q��
	CPlayer *pPlayer = CGame::GetPlayer(GetPlayerNum());

	// ���a
	pPlayer->GetRadius();

	// ���W�󂯎��
	D3DXVECTOR3 pos = pPlayer->GetPos();
	float fRadius = pPlayer->GetRadius() * m_fRadiusNum;

	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// �����̔ԍ�����Ȃ��Ƃ�
		if (GetPlayerNum() != nCount)
		{
			// �L�����N�^�[�̃|�C���^
			CPlayer *pTarget = CGame::GetPlayer(nCount);

			// !nullcheck
			if (pTarget != nullptr)
			{
				D3DXVECTOR3 TargetPos = pTarget->GetPos();
				float fTargetRadius = pTarget->GetRadius();

				// �~�`�Ɖ~�`�̓����蔻��
				if (CCollision::CollisionCircularAndCircular(
					pos, TargetPos,
					fRadius, fTargetRadius) == true)
				{
					// �O�ɉ����o��
					D3DXVECTOR3 vec = (TargetPos - pos);
					D3DXVec3Normalize(&vec, &vec);
					vec *= (fTargetRadius + fRadius);

					// ���W�ݒ�
					D3DXVECTOR3 pos = TargetPos;
					pTarget->SetPos(pos + vec);
				}
			}
		}
	}
}

//=============================================================================
// �A�C�e���̌��ʐݒ�
//=============================================================================
void CItemVortex::SetItem(void)
{
	// �g�p��Ԃɂ���
	SetUse(true);

	// Ui�̏I������
	UiUninit();
}

//=============================================================================
// �A�C�e���̌��ʂ�߂�
//=============================================================================
void CItemVortex::UndoItem(void)
{
	// �I���t���O�𗧂Ă�
	SetEnd(true);
}