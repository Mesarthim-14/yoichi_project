//=============================================================================
//
// �v���C���[UI�Ǘ��N���X[player_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "player_ui.h"
#include "item.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"

//=============================================================================
// [CPlayer_UI] �R���X�g���N�^
//=============================================================================
CPlayer_UI::CPlayer_UI(PRIORITY Priority) : CScene2D(Priority)
{

}

//=============================================================================
// [~CPlayer_UI] �f�X�g���N�^
//=============================================================================
CPlayer_UI::~CPlayer_UI()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CPlayer_UI *CPlayer_UI::Create(void)
{
    CPlayer_UI *PlayerUI = nullptr;
    if (PlayerUI == nullptr)
    {
        // �������̊m�ۂƏ�����
        PlayerUI = new CPlayer_UI;
        PlayerUI->Init();
    }
    return PlayerUI;
}

//=============================================================================
// [Init] ����������
//=============================================================================
void CPlayer_UI::Init(void)
{
    // �eUI����
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CPlayer_UI::Uninit(void)
{
    // UI�̔j��
    // �������m��
    for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
    {
        // !nullcheck
        if (m_apItem[nCount] != nullptr)
        {
            // �I������
            m_apItem[nCount]->Uninit();
            m_apItem[nCount] = nullptr;
        }
    }

    // �z�񂪂����
    if (m_apItem.size() != NULL)
    {
        // �z��̃N���A
        m_apItem.clear();
    }

    CScene2D::Uninit();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CPlayer_UI::Update(void)
{
    // �eUI�̍X�V����

    // �������m��
    for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
    {
        // !nullcheck
        if (m_apItem[nCount] != nullptr)
        {
            // �A�C�e���̍폜�t���O����������
            if (m_apItem[nCount]->GetEnd() == true)
            {
                // �z�����ɂ���
                m_apItem.erase(m_apItem.begin() + nCount);
            }
        }
    }
}

//=============================================================================
// �A�C�e���̃f�[�^��n��
//=============================================================================
void CPlayer_UI::AcquiredItem(CItem *pItem)
{
    if (m_apItem.size() == 0)
    {
        // �A�C�e���̃|�C���^
        m_apItem.push_back(pItem);
    }
    else if (m_apItem[0] != nullptr)
    {
        // �g���Ă����ԂȂ�
        if (m_apItem[0]->GetUse() == true)
        {
            // �A�C�e���̃|�C���^
            m_apItem.push_back(pItem);
        }
    }
}

//=============================================================================
// �A�C�e���̎g�p����
//=============================================================================
void CPlayer_UI::UseItem(void)
{
    for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
    {
        // !nullcheck
        if (m_apItem[nCount] != nullptr)
        {
            if (m_apItem[nCount]->GetUse() == false)
            {
                // �A�C�e�����g��
                m_apItem[nCount]->SetItem();

                break;
            }
        }
    }
}