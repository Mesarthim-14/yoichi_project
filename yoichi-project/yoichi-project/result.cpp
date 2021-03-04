//=============================================================================
//
// ���U���g�N���X���� [result.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "joypad.h"
#include "resource_manager.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CResult::m_pTexture[2] = {};

//=============================================================================
//���U���g�N���X�̃R���X�g���N�^
//=============================================================================
CResult::CResult(PRIORITY Priority) : CScene(Priority)
{
	//�����o�ϐ��̃N���A
	m_pScene2D = NULL;
}

//=============================================================================
//���U���g�N���X�̃f�X�g���N�^
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
//���U���g�N���X�̃N���G�C�g����
//=============================================================================
CResult * CResult::Create(void)
{
	//���U���g�N���X�̃|�C���^�ϐ�
	CResult *pResult = new CResult;

	//���������m�ۂł��Ă�����
	if (pResult != NULL)
	{
		//�����������Ăяo��
		pResult->Init(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f),D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f));
	}

	return pResult;
}

//=============================================================================
//���U���g�N���X�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CResult::Load(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	
	D3DXCreateTextureFromFile(pDevice, "data/Texture/Result.png", &m_pTexture[0]);

	return S_OK;
}

void CResult::UnLoad(void)
{
	for (int nCount = 0; nCount < 1; nCount++)
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
HRESULT CResult::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//2D�I�u�W�F�N�g�̐���
	m_pScene2D = CScene2D::Create(pos, size);
	if (m_pScene2D != NULL)
	{
		m_pScene2D->BindTexture(m_pTexture[0]);
	}

	return E_NOTIMPL;
}

//=============================================================================
//���U���g�N���X�̏I������
//=============================================================================
void CResult::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
//���U���g�N���X�̍X�V����
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TITLE);
	}
}

//=============================================================================
//���U���g�N���X�̕`�揈��
//=============================================================================
void CResult::Draw(void)
{
}
