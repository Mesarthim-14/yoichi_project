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
#include "itembox.h"
#include "item_boxmanager.h"
#include "star_manager.h"
#include "result.h"

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
CResult *CGame::m_apResult[MAX_PLAYER_NUM] = {};

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame()
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;
	m_pStarManager = nullptr;

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
	pGame->Init();

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(void)
{
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

	//BGM
//	CSound *pSound = CManager::GetSound();
//	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	// !nullcheck
	if (m_pStarManager == nullptr)
	{
		// �C���X�^���X����
		m_pStarManager = CStarManager::Create();
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

	// ���U���g
	for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
	{
		if (m_apResult[nCount] != nullptr)
		{
			m_apResult[nCount]->Uninit();
			delete m_apResult[nCount];
			m_apResult[nCount] = nullptr;
		}
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
	if (m_pStarManager != nullptr)
	{
		// �I������
		m_pStarManager->Uninit();
		delete m_pStarManager;
		m_pStarManager = nullptr;
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
	
	delete this;
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	if(m_bGameEnd)
	{
		//���U���g����������Ă��Ȃ���ΐ�������
		if (m_apResult[0] == nullptr)
		{
			D3DXVECTOR3 pos;
			D3DXVECTOR3 size;
			for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
			{
				if (m_nPlayerNum == 2)
				{
					pos = D3DXVECTOR3(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2)*nCount , SCREEN_HEIGHT / 2, 0.0f);
				}
				else
				{
					pos = D3DXVECTOR3(SCREEN_WIDTH / 4 + (SCREEN_WIDTH / 2) * (nCount % 2), SCREEN_HEIGHT / 4 + (SCREEN_HEIGHT / 2) * (nCount / 2), 0.0f);
				}
				size = SCREEN_SIZE / 2;
				m_apResult[nCount] = CResult::Create(pos, size, nCount);
			}
		}

		for (int nCount = 0; nCount < m_nPlayerNum; nCount++)
		{
			m_apResult[nCount]->Update();
		}
	}
	else
	{
		CScene::UpdateAll();
		// �v���C���[��
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
		if (m_pStarManager != nullptr)
		{
			// �X�V����
			m_pStarManager->Update();
		}

		// �Q�[���̐ݒ�
		SetGame();
	}

#ifdef _DEBUG
	if (pKeyboard->GetTrigger(DIK_P))
	{
		m_bGameEnd = !m_bGameEnd;
	}
#endif
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
	CScene::DrawAll();
	// ���U���g
	for (int nCount = 0; nCount < MAX_PLAYER_NUM; nCount++)
	{
		if (m_apResult[nCount] != nullptr)
		{
			m_apResult[nCount]->Draw();
		}
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
CCamera * CGame::GetCamera(int nCount)
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