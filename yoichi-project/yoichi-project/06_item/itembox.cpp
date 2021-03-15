//=============================================================================
//
// �A�C�e���{�b�N�X�N���X���� [itembox.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "itembox.h"
#include "renderer.h"
#include "collision.h"
#include "manager.h"
#include "resource_manager.h"
#include "xfile.h"
#include "game.h"
#include "player.h"
#include "item_bluewing.h"
#include "item_redwing.h"
#include "item_bomb.h"
#include "item_barrier.h"
#include "item_thunder.h"
#include "item_vortex.h"
#include "item_mhand.h"
#include "item.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEMBOX_ROTATION_NUM		(0.01f)																			// ��]�̒l
#define ITEMBOX_ROTATION_NUM_ALL	(D3DXVECTOR3(ITEMBOX_ROTATION_NUM, ITEMBOX_ROTATION_NUM, ITEMBOX_ROTATION_NUM))	// ��]�̒l
#define ITEMBOX_RADIUS				(100.0f)																		// �����蔻��̔��a
#define ITEMBOX_GENERATE_INTER		(300.0f)																		// �Đ����t���[��

//=============================================================================
// �C���X�^���X����
//=============================================================================
CItemBox * CItemBox::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �������m��
	CItemBox *pItemBox = new CItemBox;

	// nullcheck
	if (pItemBox != nullptr)
	{
		// ����������
		pItemBox->Init(pos, size);
	}

	return pItemBox;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemBox::CItemBox(PRIORITY Priority) : CModel(Priority)
{
	m_bDraw = true;
	m_nDrawCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBox::~CItemBox()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItemBox::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CModel::Init(pos, size);

	// X�t�@�C���̏��擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// ���f�����̐ݒ�
	BindModel(pXfile->GetXfile(CXfile::XFILE_NUM_ITEM_BOX));
	BindTexture(pXfile->GetXfileTexture(CXfile::XFILE_NUM_ITEM_BOX));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItemBox::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBox::Update(void)
{
	// �`�撆
	if (m_bDraw == true)
	{
		// ��]�̏���
		Rotation(ITEMBOX_ROTATION_NUM_ALL);

		// �����蔻��
		Collision();

		// �X�V����
		CModel::Update();
	}
	else
	{
		// �`��̂��߂̃J�E���g
		m_nDrawCount++;

		// ���ʂ𒴂�����
		if (m_nDrawCount >= ITEMBOX_GENERATE_INTER)
		{
			m_bDraw = true;
			m_nDrawCount = 0;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItemBox::Draw(void)
{
	// �`��̃t���O
	if (m_bDraw == true)
	{
		// Renderer�N���X����f�o�C�X���擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ���C�g�̌��ʂ���������
	//	pDevice->LightEnable(0, false);

		// �`�揈��
		CModel::Draw();

		// ���C�g�̌��ʂ�t���Ȃ���
	//	pDevice->LightEnable(0, true);
	}
}

//=============================================================================
// �����蔻��̏���
//=============================================================================
void CItemBox::Collision(void)
{
	// �v���C���[�̐�
	int nPlayerNum = CGame::GetPlayerNum();

	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		// �v���C���[�̊֐�
		CPlayer *pPlayer = CGame::GetPlayer(nCount);

		// �����蔻��
		if (CCollision::CollisionCircularAndCircular(
			GetPos(), pPlayer->GetPos(),
			ITEMBOX_RADIUS, pPlayer->GetRadius()) == true)
		{
			// �����Ȃ�����
			m_bDraw = false;

			if (pPlayer->GetItem() == nullptr)
			{
				// �A�C�e������
				ItemCreate(nCount);
			}
		}
	}
}

//=============================================================================
// �A�C�e���̐���
//=============================================================================
void CItemBox::ItemCreate(int nCount)
{
	// �����̃i���o�[
	int nNumber = rand() % (int)ITEM_TYPE_MAX;

		// �v���C���[�̊֐�
	CPlayer *pPlayer = CGame::GetPlayer(nCount);

		// �i���o�[
		switch ((ITEM_TYPE)nNumber)
		{
		case ITEM_TYPE_BLUE_WING:
			pPlayer->AcquiredItem(CItemBlueWing::Create(nCount));
			break;

		case ITEM_TYPE_RED_WING:
			pPlayer->AcquiredItem(CItemRedWing::Create(nCount));
			break;

		case ITEM_TYPE_BARRIER:
			pPlayer->AcquiredItem(CItemBarrier::Create(nCount));
			break;

		case ITEM_TYPE_BOMB:
			pPlayer->AcquiredItem(CItemBomb::Create(nCount));
			break;

		case ITEM_TYPE_THUNDER:
			pPlayer->AcquiredItem(CItemThunder::Create(nCount));
			break;

		case ITEM_TYPE_VORTEX:
			pPlayer->AcquiredItem(CItemVortex::Create(nCount));
			break;

		case ITEM_TYPE_MHAND:
			pPlayer->AcquiredItem(CItemMhand::Create(nCount));
			break;

		default:
			break;
		}
}