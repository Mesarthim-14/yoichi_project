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

//=============================================================================
// �}�N����`
//=============================================================================
#define ROTATION_NUM		(0.1f)		// ��]�̑���

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_TITLE_UI_NUM] = {};

//=============================================================================
//���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
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
		pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	return pTitle;
}

//=============================================================================
// �^�C�g���N���X�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CTitle::Load(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/Texture/magic22.jpg", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/StartLogo.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/title_name.png", &m_pTexture[2]);

	return S_OK;
}

void CTitle::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TITLE_UI_NUM; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}

}

//=============================================================================
//���U���g�N���X�̏���������
//=============================================================================
HRESULT CTitle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene2D == NULL)
	{
		//2D�I�u�W�F�N�g�̐���
		m_pScene2D = CScene2D::Create(pos, size);

		if (m_pScene2D != NULL)
		{
			m_pScene2D->BindTexture(m_pTexture[0]);
		}
	}

	// PRESS���S�̃|�C���^
	if (m_pPress == NULL)
	{
		m_pPress = CScene2D::Create(D3DXVECTOR3(pos.x, pos.y + TITLE_PRESS_POS_Y, 0.0f), D3DXVECTOR3(TITLE_PRESS_SIZE_X, TITLE_PRESS_SIZE_Y, 0.0f));
		m_pPress->BindTexture(m_pTexture[1]);
	}

	if (m_pTitleName == NULL)
	{
		//2D�I�u�W�F�N�g�̐���
		m_pTitleName = CScene2D::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 0.0f), D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_Y, 0.0f));

		if (m_pTitleName != NULL)
		{
			m_pTitleName->BindTexture(m_pTexture[2]);
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
	Release();
}

//=============================================================================
//���U���g�N���X�̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	if (m_pPress != NULL)
	{
	//	m_pPress->SetRotation(ROTATION_NUM);
	}

}

//=============================================================================
//���U���g�N���X�̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}
