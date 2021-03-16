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
#include "effect_factory.h"
#include "mesh_3d.h"
#include "resource_manager.h"
#include "fade.h"
#include "time_ui.h"
#include "timer.h"
#include "itembox.h"
#include "item_boxmanager.h"
#include "star_factory.h"

//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_pCamera[MAX_PLAYER_NUM] = {};
CPlayer *CGame::m_pPlayer[MAX_PLAYER_NUM] = {};
CLight *CGame::m_pLight = nullptr;
CMeshField *CGame::m_pMeshField = nullptr;
CBg *CGame::m_pBg = nullptr;
CPause *CGame::m_pPause = nullptr;
CItemBoxManager *CGame::m_pItemManager = nullptr;
int CGame::m_nPlayerNum = 1;
CTime_UI *CGame::m_pTimeUI=nullptr;

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
    m_IsGameEnd = false;
	m_pStarFactory = nullptr;

	// 0��������
	if (m_nPlayerNum == 0)
	{
		m_nPlayerNum = 1;
	}
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
	// static�ϐ�������
	m_nPlayerNum = 0;
}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CGame* CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame();

	// ����������
	pGame->Init(ZeroVector3, ZeroVector3);

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �v���C���[�̐������[�v
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{	
		// nullcheck
		if (m_pCamera[nCount] == nullptr)
		{
			// �J�����N���X�̃N���G�C�g
			m_pCamera[nCount] = CCamera::Create(nCount);
		}

		// nullcheck
		if (m_pPlayer[nCount] == nullptr)
		{
			// �v���C���[�̐���
			m_pPlayer[nCount] = CPlayer::Create(
				ZeroVector3, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), 
				nCount);
		}
	}

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != nullptr)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// ���b�V���t�B�[���h
	m_pMeshField = CMeshField::Create();

	// �w�i
	if (m_pBg == nullptr)
	{
		m_pBg = CBg::Create(BG_POS, BG_SIZE);
	}

    m_pTimeUI = CTime_UI::Create();
	//BGM
//	CSound *pSound = CManager::GetSound();
//	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	// !nullcheck
	if (m_pStarFactory == nullptr)
	{
		// �C���X�^���X����
		m_pStarFactory = CStarFactory::Create();
	}

	// nullcheck
	if (m_pItemManager == nullptr)
	{
		// �C���X�^���X����
		m_pItemManager = CItemBoxManager::GetInstance();

		// !nullcheck
		if (m_pItemManager != nullptr)
		{
			// �A�C�e���{�b�N�X�̐���
			m_pItemManager->CreateItemBox();
		}
	}

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
	// �w�i
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		m_pBg = nullptr;
	}

	// ���C�g�̏I������
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	// �v���C���[�̐�
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{
		if (m_pCamera[nCount] != nullptr)
		{
			//�J�����N���X�̏I�������Ăяo��
			m_pCamera[nCount]->Uninit();

			//�������̔j��
			delete m_pCamera[nCount];

			//�������̃N���A
			m_pCamera[nCount] = nullptr;
		}

		// �v���C���[�̏I������
		if (m_pPlayer[nCount] != nullptr)
		{
			m_pPlayer[nCount]->Uninit();
			m_pPlayer[nCount] = nullptr;
		}
	}


	// nullcheck
	if (m_pStarFactory != nullptr)
	{
		// �I������
		m_pStarFactory->Uninit();
		delete m_pStarFactory;
		m_pStarFactory = nullptr;
	}

	// nullcheck
	if (m_pItemManager != nullptr)
	{
		// �I������
		m_pItemManager->Uninit();
		m_pItemManager = nullptr;
	}

	// !nullcheck
	if (CManager::GetResourceManager() != nullptr)
	{
		//�T�E���h���擾
		CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

		// !nullcheck
		if (pSound != nullptr)
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
	// �v���C���[��
    for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
    {
        //�L�[���͂Ńt���OON 
        if (pKey->GetTrigger(DIK_TAB))
        {
            GameEnd();// �Q�[�����I��
        }
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{
		// !nullcheck
		if (m_pCamera != nullptr)
		{
			//�J�����N���X�̍X�V����
			m_pCamera[nCount]->Update();
		}
	}

	// nullcheck
	if (m_pStarFactory != nullptr)
	{
		// �X�V����
		m_pStarFactory->Update();
	}

	// �Q�[���̐ݒ�
        if (m_pCamera != NULL)
        {
            // !nullcheck
            if (m_pCamera != NULL)
            {
                //�J�����N���X�̍X�V����
                m_pCamera[nCount]->Update();
            }
        }
    }

    // ���Ԑ؂ꂾ������
    if (m_pTimeUI->GetTimer()->IsTimeOver())
    {
        GameEnd();// �Q�[�����I��
    }

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
	if (m_pBg != nullptr)
	{
		m_pBg->Draw();
	}

	// ���C�g
	if (m_pLight != nullptr)
	{
		m_pLight->ShowLightInfo();
	}
}

//=======================================================================================
// �J�����̏��
//=======================================================================================
CCamera *CGame::GetCamera(int nCount)
{
	return m_pCamera[nCount];
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
CPlayer * CGame::GetPlayer(int nCount)
{
	return m_pPlayer[nCount];
}

//=======================================================================================
// �R���e�j���[�̏��
//=======================================================================================
CPause * CGame::GetPause(void)
{
	return m_pPause;
}
