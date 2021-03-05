//=============================================================================
//
// �N�G�X�g���S�̃N���X [quest_logo.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "quest_logo.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"


//=============================================================================
// �}�N����`
//=============================================================================
#define QUEST_LOGO_POS_X		(SCREEN_WIDTH / 2)										// X���W
#define QUEST_LOGO_POS_Y		(250.0f)												// Y���W
#define QUEST_LOGO_SIZE_X		(310.0f)												// X�T�C�Y
#define QUEST_LOGO_SIZE_Y		(40.0f)													// Y�T�C�Y
#define QUEST_LOGO_POS		(D3DXVECTOR3(QUEST_LOGO_POS_X, QUEST_LOGO_POS_Y, 0.0f))		// ���W
#define QUEST_LOGO_SIZE		(D3DXVECTOR3(QUEST_LOGO_SIZE_X, QUEST_LOGO_SIZE_Y, 0.0f))	// �T�C�Y

#define QUEST_LOGO_SCALE_UP_NUM	(0.05f)													// �g��̒l
#define QUEST_LOGO_MAX_NUM		(1.0f)													// �g��̍ő�l
#define QUEST_LOGO_END_FLAME	(100)													// �I���̎���

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
CQuestLogo* CQuestLogo::Create(void)
{
	// �I�u�W�F�N�g�𐶐�
	CQuestLogo* pQuestLogo = new CQuestLogo;

	// ����������
	pQuestLogo->Init(QUEST_LOGO_POS, QUEST_LOGO_SIZE);

	return pQuestLogo;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CQuestLogo::CQuestLogo()
{
	m_nEndCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CQuestLogo::~CQuestLogo()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CQuestLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CUi::Init(pos, size);													// ���W�A�T�C�Y

	return S_OK;
}

//================================================
// �I������
//================================================
void CQuestLogo::Uninit(void)
{
	// �I������
	CUi::Uninit();
}

//================================================
// �X�V����
//================================================
void CQuestLogo::Update(void)
{
	// �X�V����
	CUi::Update();

	// �I���̂��߂̃J�E���^�[
	m_nEndCounter++;

	if (GetScale() < QUEST_LOGO_MAX_NUM)
	{
		// �g��̒l
		ScaleUp(QUEST_LOGO_SCALE_UP_NUM);
	}
	else
	{
		// �ő吔�ɐݒ�
		SetScale(QUEST_LOGO_MAX_NUM);
	}

	// ���ȏ��
	if (m_nEndCounter >= QUEST_LOGO_END_FLAME)
	{
		// �I������
		Uninit();
	}
}

//================================================
// �`�揈��
//================================================
void CQuestLogo::Draw(void)
{
	// �`�揈��
	CUi::Draw();
}