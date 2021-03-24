//=============================================================================
//
// �v���C���[UI�Ǘ��N���X[player_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "player_ui.h"
#include "item.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"
#include "star_ui.h"
#include "effect.h"
#include "effect_factory.h"

//=============================================================================
// [CPlayer_UI] �R���X�g���N�^
//=============================================================================
CPlayer_UI::CPlayer_UI(PRIORITY Priority) : CScene(Priority)
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
// ����
// �v���C���[�̔ԍ�
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
// ����
// �v���C���[�̔ԍ�
//=============================================================================
HRESULT CPlayer_UI::Init(void)
{
    return S_OK;
}

//=============================================================================
// [Init] ����������
//=============================================================================
void CPlayer_UI::Init(int nPlayerNum)
{
    m_pStarUI = CStar_UI::Create();
    m_pStarUI->SetPosition(nPlayerNum);
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CPlayer_UI::Uninit(void)
{
    // UI�̔j��
    m_pStarUI->Uninit();

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
    Release();
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
// [Draw]�`�揈��
//=============================================================================
void CPlayer_UI::Draw(void)
{
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

    //    //�W�����v���[�V�����̍Đ�
    //    SetMotion(4);
    //    SetLanding(false);
    //}
    ////=============================================================================
    //// Author : Ito Yogo
    ////=============================================================================
    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, m_nNumber))
    //{
    //    // ���̃A�C�e�����g��ꂽ�Ƃ��̃G�t�F�N�g
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_THUNDER);

    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(0.0f, 500.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_LIGHTNINGSTRIKE);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y, m_nNumber))
    //{
    //    // �����Ƃ�ꂽ�Ƃ��̃G�t�F�N�g
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STAR);
    //    //CEffectFactory::CreateEffect(GetPos()/* + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f)*/, CEffectFactory::EFFECT_TYPE::EFFECT_NUM_SHOCKWAVE);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, m_nNumber))
    //{
    //    // ���x�����������̃G�t�F�N�g
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSDOWN);

    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSDOWNPARTICLE);

    //}
    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nNumber))
    //{
    //    // ���x���オ�������̃G�t�F�N�g
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSUP);

    //    CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
    //        CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATESUPPARTICLE);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L2_TRIGGER, m_nNumber))
    //{
    //    // �����̃G�t�F�N�g
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSION);
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSIONCIRCLE);
    //    CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSIONSPARK);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nNumber))
    //{
    //    // ���̃A�C�e���̃G�t�F�N�g
    //    CWind::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43),
    //        ZeroVector3, 10.0f, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_nNumber);

    //    CWind::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43),
    //        ZeroVector3, 10.0f, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_nNumber);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R3, m_nNumber))
    //{
    //    // �o���A�̃G�t�F�N�g
    //    CBARRIER::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //        GetModelAnime(21)->GetMtxWorld()._42,
    //        GetModelAnime(21)->GetMtxWorld()._43),
    //        D3DXVECTOR3(50.0f, 50.0f, 50.0f), 10.0f, D3DXVECTOR3(5.0f, 5.0f, 5.0f), m_nNumber);
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L3, m_nNumber))
    //{
    //    for (int nCount = 0; nCount < 100; nCount++)
    //    {
    //        // �o���A���󂳂ꂽ�Ƃ��̃G�t�F�N�g
    //        CBARRIEREFFECT::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
    //            GetModelAnime(21)->GetMtxWorld()._42,
    //            GetModelAnime(21)->GetMtxWorld()._43),
    //            D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(30.0f, 30.0f, 30.0f), 10.0f);
    //    }
    //}

    //if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, m_nNumber))
    //{
    //    // �}�W�b�N�n���h�̃G�t�F�N�g
    //    CMagichand::Create(-MAGICHAND_DISTANCE, CTexture::SEPARATE_TEX_MAGICHANDLEFT, m_nNumber);
    //    CMagichand::Create(MAGICHAND_DISTANCE, CTexture::SEPARATE_TEX_MAGICHANDRIGHT, m_nNumber);
    //}
    ////=============================================================================
//}

}

//=============================================================================
// �A�C�e���폜
//=============================================================================
void CPlayer_UI::ItemErase(void)
{
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
