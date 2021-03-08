//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "quest_logo.h"
#include "effect_factory.h"
#include "mesh_3d.h"
#include "resource_manager.h"
#include "fade.h"

//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_pCamera = NULL;
CLight *CGame::m_pLight = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CBg *CGame::m_pBg = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CPause *CGame::m_pPause = NULL;

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
    m_IsGameEnd = false;
	m_nTimeCounter = 0;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{

}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CGame* CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame();

	// ����������
	pGame->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �J�����N���X�̃N���G�C�g
	m_pCamera = CCamera::Create();

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// �v���C���[�̐���
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));	
	}

	// ���b�V���t�B�[���h
	m_pMeshField = CMeshField::Create();

	// �w�i
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create(BG_POS, BG_SIZE);
	}

	//BGM
//	CSound *pSound = CManager::GetSound();
//	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�t�H���g�̐���
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{
	if (m_pCamera != NULL)
	{
		//�J�����N���X�̏I�������Ăяo��
		m_pCamera->Uninit();

		//�������̔j��
		delete m_pCamera;

		//�������̃N���A
		m_pCamera = NULL;
	}

	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}

	// ���C�g�̏I������
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �v���C���[�̏I������
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	// !nullcheck
	if (CManager::GetResourceManager() != NULL)
	{
		//�T�E���h���擾
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

		// !nullcheck
		if (pSound != NULL)
		{
			//�Q�[��BGM��~
		//	pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
    CInputKeyboard* pKey = CManager::GetKeyboard();
    CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
    //�L�[���͂Ńt���OON 
    if ( pKey->GetTrigger(DIK_TAB))
    {
        GameEnd();// �Q�[�����I��
    }

	if (m_pCamera != NULL)
	{
		//�J�����N���X�̍X�V����
		m_pCamera->Update();
	}

    if (m_nTimeCounter>=300)
    {
        GameEnd();// �Q�[�����I��
    }

    // �Q�[���̐ݒ�
    SetGame();

    if (m_IsGameEnd && mode == CFade::FADE_MODE_NONE)
    {
        CFade *pFade = CManager::GetFade();
        pFade->SetFade(CManager::MODE_TYPE_RESULT);
    }

}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}

	// ���C�g
	if (m_pLight != NULL)
	{
		m_pLight->ShowLightInfo();
	}
}

//=======================================================================================
// �Q�[���̐ݒ�
//=======================================================================================
void CGame::SetGame(void)
{
	// �Q�[���̃^�C���J�E���^�[
	m_nTimeCounter++;
}

//=======================================================================================
// �J�����̏��
//=======================================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=======================================================================================
// ���C�g�̏��
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// �v���C���[�̏��
//=======================================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=======================================================================================
// �R���e�j���[�̏��
//=======================================================================================
CPause * CGame::GetPause(void)
{
	return m_pPause;
}

#if _DEBUG

#endif // _DEBUG

