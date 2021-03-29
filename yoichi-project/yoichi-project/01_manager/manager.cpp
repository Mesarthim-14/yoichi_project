//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bg.h"
#include "billboard.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "mesh_3d.h"
#include "model.h"
#include "effect_factory.h"
#include "player.h"
#include "renderer.h"
#include "resource_manager.h"
#include "scene3D.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "xfile.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pKeyboard = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CInputJoypad *CManager::m_pJoypad = NULL;
CScene *CManager::m_pScene = NULL;
CResourceManager *CManager::m_pResourceManager = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_���[�N���X�̃C���X�^���X����
	m_pRenderer = new CRenderer;

	//���������m�ۂł�����
	if (m_pRenderer != NULL)
	{
		// ����������
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//���͏����N���X�̃C���X�^���X����
	m_pKeyboard = new CInputKeyboard;

	//���������m�ۂł�����
	if (m_pKeyboard != NULL)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//���͏����N���X�̃C���X�^���X����
	m_pJoypad = new CInputJoypad;

	//���������m�ۂł�����
	if (m_pJoypad != NULL)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	// nullcheck
	if (m_pResourceManager == NULL)
	{
		// ���\�[�X�}�l�[�W���̃C���X�^���X����
		m_pResourceManager = CResourceManager::GetInstance();
	}

	//�T�E���h�̃C���X�^���X����
	//m_pSound = new CSound;
	//if (m_pSound != NULL)
	//{
	//	m_pSound->Init(hWnd);
	//}

	//�t�F�[�h�N���X�̃N���G�C�g
	m_pFade = CFade::Create();

	//�S�e�N�X�`���̓ǂݍ���
	LoadAll();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�S�e�N�X�`���̔j��
	UnloadAll();

	//���݃��[�h�̏I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			// �I������
		//	m_pTitle->Uninit();
			m_pTitle = NULL;
		}

		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			// �I������
		//	m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			// �I������
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	}

	// nullchack
	if (m_pFade != NULL)
	{
		//�t�F�[�h�N���X�̏I�������Ăяo��
		m_pFade->Uninit();

		//�������̔j��
		delete m_pFade;

		//�������̃N���A
		m_pFade = NULL;
	}

	// !nullcheck
	if (m_pResourceManager != NULL)
	{
		// ���\�[�X�̃��[�h
		delete m_pResourceManager;
		m_pResourceManager = NULL;
	}

	if (m_pKeyboard != NULL)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pKeyboard->Uninit();

		//�������̍폜
		delete m_pKeyboard;

		//�������̃N���A
		m_pKeyboard = NULL;
	}

	if (m_pJoypad != NULL)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pJoypad->Uninit();

		//�������̍폜
		delete m_pJoypad;

		//�������̃N���A
		m_pJoypad = NULL;
	}

	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̏I�������Ăяo��
		m_pRenderer->Uninit();

		//�������̍폜
		delete m_pRenderer;

		//�������̃N���A
		m_pRenderer = NULL;
	}

	// �V�[�����̃����[�X
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{

	if (m_pKeyboard != NULL)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pKeyboard->Update();
	}

	if (m_pJoypad != NULL)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pJoypad->Update();
	}


	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			// �^�C�g������
			m_pTitle->Update();
		}
		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	}

	if (m_pFade != NULL)
	{
		//�t�F�[�h�N���X�̍X�V�����Ăяo��
		m_pFade->Update();
	}

	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̕`�揈���Ăяo��
		m_pRenderer->Update();
	}

}

//=============================================================================
//�`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̕`�揈���Ăяo��
		m_pRenderer->Draw();
	}
}

//=============================================================================
//�e�N�X�`���̑S���[�h����
//=============================================================================
void CManager::LoadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != NULL)
	{
		// ���\�[�X�̃��[�h
		m_pResourceManager->LoadAll();
	}

	CTutorial::Load();
	CEffectFactory::ReadFile();
	CMesh3d::ReadFile();
}

//=============================================================================
//�e�N�X�`���̑S�A�����[�h����
//=============================================================================
void CManager::UnloadAll(void)
{
	// !nullcheck
	if (m_pResourceManager != NULL)
	{
		// ���\�[�X�̃��[�h
		m_pResourceManager->UnloadAll();
	}
}

//=============================================================================
//�Q�[�����[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	CSound *pSound = GET_SOUND_PTR;

	//���݃��[�h�̏I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			// �^�C�g������
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);
			m_pTutorial = NULL;
		}
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
			m_pGame = NULL;
		}
		break;
	}

	// �V�[�����̃����[�X
	CScene::ReleaseAll();

	//���[�h��ݒ�
	m_mode = mode;

	//�ݒ肳�ꂽ���[�h���N���G�C�g
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TYPE_TITLE:
		if (m_pTitle == NULL)
		{
			// �^�C�g������
			m_pTitle = CTitle::Create();
		}
		break;

		// �`���[�g���A��
	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			// �`���[�g���A������
			m_pTutorial = CTutorial::Create();
		}
		break;

		// �Q�[��
	case MODE_TYPE_GAME:
		if (m_pGame == NULL)
		{
			// �Q�[������
			m_pGame = CGame::Create();
		}

		break;

	default:
		break;
	}
}

//=============================================================================
//�Q�[�����[�h���̎擾
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//�����_���[���擾
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
//�L�[�{�[�h���擾
//=============================================================================
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=============================================================================
//�t�F�[�h���擾
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
//�W���C�p�b�h���擾
//=============================================================================
CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}