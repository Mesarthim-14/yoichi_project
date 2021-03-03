//=============================================================================
//
// ���\�[�X�}�l�[�W���[���� [resource_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "resource_manager.h"
#include "texture.h"
#include "xfile.h"

//=============================================================================
// static�������錾
//=============================================================================
CResourceManager *CResourceManager::m_pResourceManager = NULL;	// ���g�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResourceManager::CResourceManager()
{
	m_pTexture = NULL;					// �e�N�X�`���̃|�C���^
	m_pXFile = NULL;						// X�t�@�C���̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResourceManager::~CResourceManager()
{
	// �A�����[�h����
	UnLoadAll();

	// nullcheck
	if (m_pTexture != NULL)
	{
		// �e�N�X�`���|�C���^�J��
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// nullcheck
	if (m_pXFile != NULL)
	{
		// X�t�@�C���|�C���^�J��
		delete m_pXFile;
		m_pXFile = NULL;
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResourceManager::Init(void)
{
	// nullcheck
	if (m_pTexture == NULL)
	{
		// �e�N�X�`���̃C���X�^���X����
		m_pTexture = CTexture::Create();
	}

	// nullcheck
	if (m_pXFile == NULL)
	{
		// �e�N�X�`���̃C���X�^���X����
		m_pXFile = CXfile::Create();
	}

	return S_OK;
}

//=============================================================================
// ���[�h����
//=============================================================================
void CResourceManager::LoadAll(void)
{
	// !nullcheck
	if (m_pTexture != NULL)
	{
		// �e�N�X�`�����[�h
		m_pTexture->Load();
		m_pTexture->SeparateTexLoad();
	}

	// !nullcheck
	if (m_pXFile != NULL)
	{
		// ���f�����[�h
		m_pXFile->ModelLoad();
	}
}

//=============================================================================
// �A�����[�h����
//=============================================================================
void CResourceManager::UnLoadAll(void)
{
	// !nullcheck
	if (m_pTexture != NULL)
	{
		// �e�N�X�`���A�����[�h
		m_pTexture->UnLoad();
		m_pTexture->SeparateTexUnLoad();
	}

	// !nullcheck
	if (m_pXFile != NULL)
	{
		// �e�N�X�`���A�����[�h
		m_pXFile->ModelUnLoad();
	}
}

//=============================================================================
// �C���X�^���X�擾�֐�
//=============================================================================
CResourceManager * CResourceManager::GetInstance(void)
{
	if (m_pResourceManager == NULL)
	{
		// �������m��
		m_pResourceManager = new CResourceManager;

		// nullcheck
		if (m_pResourceManager != NULL)
		{
			// ����������
			m_pResourceManager->Init();
		}
	}

	return m_pResourceManager;
}