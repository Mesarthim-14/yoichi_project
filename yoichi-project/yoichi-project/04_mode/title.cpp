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
#include "playerselectbutton.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define ROTATION_NUM		(0.1f)		// ��]�̑���
#define BUTTON_POS_Y		(SCREEN_HEIGHT * 3/4)
//=============================================================================
//���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	//�����o�ϐ��̃N���A
	m_pScene2D = NULL;
	m_bDisplayButton = false;
	m_nSelectButton = 0;
	ZeroMemory(m_apPlayerSelectButton, sizeof(m_apPlayerSelectButton));
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
	CTexture *pTexture = GET_TEXTURE_PTR;

	if (m_pScene2D == NULL)
	{
		//2D�I�u�W�F�N�g�̐���
		m_pScene2D = CScene2D::Create(SCREEN_SIZE/2, SCREEN_SIZE);

		if (m_pScene2D != NULL)
		{
			m_pScene2D->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_TITLE));
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

	for (int nCount = 0; nCount < MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1; nCount++)
	{
		if (m_apPlayerSelectButton[nCount] != NULL)
		{
			m_apPlayerSelectButton[nCount]->Uninit();
			m_apPlayerSelectButton[nCount] = NULL;
		}
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
	CSound *pSound = GET_SOUND_PTR;
	CScene::UpdateAll();

	SelectButton();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0)|| pKey->GetTrigger(DIK_RETURN))
	{
		if (!m_bDisplayButton)
		{
			m_bDisplayButton = true;
			for (int nCount = 0; nCount < MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1; nCount++)
			{
				m_apPlayerSelectButton[nCount] = CPlayerSelectButton::Create(D3DXVECTOR3(SCREEN_WIDTH / MAX_PLAYER_NUM * (nCount + 1), BUTTON_POS_Y, 0), PLAYER_SELECT_BUTTON, nCount + MIN_PLAYER_NUM);
			}
		}
	}


	// �v���C���[�̃i���o�[�ݒ�
	SetPlayerNum();
}

//=============================================================================
//���U���g�N���X�̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	CScene::DrawAll();
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

void CTitle::SelectButton(void)
{
	CInputJoypad* pJoy = CManager::GetJoypad();
	if (pJoy->GetPushCross(CROSS_KEY_RIGHT, 0))
	{
		if (MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1 >  m_nSelectButton + 1)
		{
			m_nSelectButton++;
		}
	}
	if (pJoy->GetPushCross(CROSS_KEY_LEFT, 0))
	{
		if (0 < m_nSelectButton)
		{
			m_nSelectButton--;
		}
	}
	for (int nCount = 0; nCount < MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1; nCount++)
	{
		if (m_apPlayerSelectButton[nCount] != NULL)
		{
			if (nCount == m_nSelectButton)
			{
				m_apPlayerSelectButton[nCount]->SetSelect(true);
			}
			else
			{
				m_apPlayerSelectButton[nCount]->SetSelect(false);
			}
		}
	}
}