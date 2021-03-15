//=============================================================================
//
// �A�C�e���Ǘ��N���X [item_manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item_boxmanager.h"
#include "manager.h"
#include "renderer.h"
#include "itembox.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ITEM_NUM		(5)		// �A�C�e���̏o����

//=============================================================================
// static�������錾
//=============================================================================
CItemBoxManager *CItemBoxManager::m_pItemManager = nullptr;	// ���g�̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItemBoxManager::CItemBoxManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItemBoxManager::~CItemBoxManager()
{
}

//=============================================================================
// �I������
//=============================================================================
void CItemBoxManager::Uninit(void)
{
	// �������m��
	for (unsigned nCount = 0; nCount < m_pItemBox.size(); nCount++)
	{
		// !nullcheck
		if (m_pItemBox[nCount] != nullptr)
		{
			// �I������
			m_pItemBox[nCount]->Uninit();
			m_pItemBox[nCount] = nullptr;
		}
	}

	// �z�񂪂����
	if (m_pItemBox.size() != NULL)
	{
		// �z��̃N���A
		m_pItemBox.clear();
	}

	// !nullcheck
	if (m_pItemManager != nullptr)
	{
		// �|�C���^�̊J��
		delete m_pItemManager;
		m_pItemManager = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CItemBoxManager::Update(void)
{

}

//=============================================================================
// �A�C�e���{�b�N�X�̐���
//=============================================================================
void CItemBoxManager::CreateItemBox(void)
{
	// �A�C�e���{�b�N�X�̃��������m��
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(1500.0f, 1000.0f, -3000.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// �A�C�e���{�b�N�X�̃��������m��
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(-2000.0f, 250.0f, 3500.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// �A�C�e���{�b�N�X�̃��������m��
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(900.0f, 250.0f, -1500.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// �A�C�e���{�b�N�X�̃��������m��
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(5000.0f, 200.0f, 5000.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));

	// �A�C�e���{�b�N�X�̃��������m��
	m_pItemBox.push_back(CItemBox::Create(D3DXVECTOR3(-4000.0f, 500.0f, -7000.0f), D3DXVECTOR3(MODEL_DEFAULT_SIZE)));
}

//=============================================================================
// �A�C�e���N���X�̐���
//=============================================================================
void CItemBoxManager::CreateItem(void)
{
}

//=============================================================================
// �C���X�^���X�擾�֐�
//=============================================================================
CItemBoxManager * CItemBoxManager::GetInstance(void)
{
	// nullcheck
	if (m_pItemManager == nullptr)
	{
		// �������m��
		m_pItemManager = new CItemBoxManager;
	}

	return m_pItemManager;
}