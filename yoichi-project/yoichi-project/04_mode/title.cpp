//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ROTATION_NUM		(0.1f)		// ��]�̑���

//=============================================================================
//���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	//�����o�ϐ��̃N���A
	m_pScene2D = NULL;
	m_pPress = NULL;
	m_pTitleName = NULL;
}

//=============================================================================
//���U���g�N���X�̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
//���U���g�N���X�̃N���G�C�g����
//=============================================================================
CTitle * CTitle::Create(void)
{
	//���U���g�N���X�̃|�C���^�ϐ�
	CTitle *pTitle = new CTitle;

	//���������m�ۂł��Ă�����
	if (pTitle != NULL)
	{
		//�����������Ăяo��
		pTitle->Init();
	}

	return pTitle;
}

//=============================================================================
//���U���g�N���X�̏���������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// �e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	if (m_pScene2D == NULL)
	{
		//2D�I�u�W�F�N�g�̐���
		m_pScene2D = CScene2D::Create(SCREEN_SIZE/2, SCREEN_SIZE);

		if (m_pScene2D != NULL)
		{
			m_pScene2D->BindTexture(NULL);
		}
	}

	// PRESS���S�̃|�C���^
	if (m_pPress == NULL)
	{
		m_pPress = CScene2D::Create(D3DXVECTOR3((SCREEN_SIZE / 2).x, (SCREEN_SIZE / 2).y + TITLE_PRESS_POS_Y, 0.0f), D3DXVECTOR3(TITLE_PRESS_SIZE_X, TITLE_PRESS_SIZE_Y, 0.0f));
		m_pPress->BindTexture(NULL);
	}

	// nullcheck
	if (m_pTitleName == NULL)
	{
		//2D�I�u�W�F�N�g�̐���
		m_pTitleName = CScene2D::Create(D3DXVECTOR3((SCREEN_SIZE / 2).x, (SCREEN_SIZE / 2).y - 125.0f, 0.0f), D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_Y, 0.0f));

		// !nullcheck
		if (m_pTitleName != NULL)
		{
			// �e�N�X�`���̃|�C���^
			m_pTitleName->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE_LOGO));
		}

	}
	return S_OK;
}

//=============================================================================
//���U���g�N���X�̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	if (m_pTitleName != NULL)
	{
		m_pTitleName->Uninit();
		m_pTitleName = NULL;
	}
	
	if (m_pPress != NULL)
	{
		m_pPress->Uninit();
		m_pPress = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	delete this;
}

//=============================================================================
//���U���g�N���X�̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();
	CScene::UpdateAll();
	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	// �v���C���[�̃i���o�[�ݒ�
	SetPlayerNum();
}

//=============================================================================
//���U���g�N���X�̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// �v���C���[�̐���ݒ�
//=============================================================================
void CTitle::SetPlayerNum(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (pKey->GetTrigger(DIK_1))
	{
		// �v���C���[�̐ݒ�
		CGame::SetPlayerNum(1);
	}
	else if (pKey->GetTrigger(DIK_2))
	{
		// �v���C���[�̐ݒ�
		CGame::SetPlayerNum(2);
	}
	else if (pKey->GetTrigger(DIK_3))
	{
		// �v���C���[�̐ݒ�
		CGame::SetPlayerNum(3);
	}
	else if (pKey->GetTrigger(DIK_4))
	{
		// �v���C���[�̐ݒ�
		CGame::SetPlayerNum(4);
	}
}
