//=============================================================================
//
// ��������UI�N���X [time_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "time_ui.h"
#include "timer.h"
#include "number_2d.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_UI_SIZE_X (64.0f)  // �����̑傫��(X��)
#define NUM_UI_SIZE_Y (128.0f)  // �����̑傫��(Y��)
#define NUM_UI_SIZE_Z (0.0f)    // �����̑傫��(Z��)

#define GAME_TIME (5)           // �Q�[���̐�������(�b)
#define NUM_UI_POS_X (720.0f+(NUM_UI_SIZE_X/2 * MAX_NAM))   // �����̈ʒu(X��)
#define NUM_UI_POS_Y (100.0f)   // �����̈ʒu(Y��)
#define NUM_UI_POS_Z (0.0f)     // �����̈ʒu(Z��)

#define NUM_RADIX    (10.0f)    // �X�R�A�̊

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// [CTime_UI]�R���X�g���N�^
//=============================================================================
CTime_UI::CTime_UI(PRIORITY Priority) : CScene2D(Priority)
{
    m_Timer = nullptr;
}

//=============================================================================
// [CTime_UI]�f�X�g���N�^
//=============================================================================
CTime_UI::~CTime_UI()
{

}

//=============================================================================
// [Create]�I�u�W�F�N�g�̐���
//=============================================================================
CTime_UI * CTime_UI::Create(void)
{
    CTime_UI *pTimerUI = nullptr;
    if (pTimerUI == nullptr)
    {
        // �������̊m�ۂƏ�����
        pTimerUI = new CTime_UI;
        pTimerUI->Init();
    }
    return pTimerUI;
}

//=============================================================================
// [Init]����������
//=============================================================================
void CTime_UI::Init(void)
{
    CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
    // �^�C�}�[�̃Z�b�g
    m_Timer = CTimer::Create();
    m_Timer->SetTimer(GAME_TIME);

    // �i���o�[�̐���
    for (unsigned int nCntNum = 0; nCntNum < MAX_NAM; nCntNum++)
    {
        D3DXVECTOR3 pos = { NUM_UI_POS_X - (nCntNum * NUM_UI_SIZE_X),NUM_UI_POS_Y,NUM_UI_POS_Z };
        m_pNumber[nCntNum] = CNumber2d::Create(pos, { NUM_UI_SIZE_X ,NUM_UI_SIZE_Y ,NUM_UI_SIZE_Z });
        m_pNumber[nCntNum]->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_NUMBER));
    }
}

//=============================================================================
// [Uninit]�I������
//=============================================================================
void CTime_UI::Uninit(void)
{
    // �i���o�[�̉��
    for (int nCntNum = 0; nCntNum < MAX_NAM; nCntNum++)
    {
        if (m_pNumber)
        {
            m_pNumber[nCntNum]->Uninit();

        }
    }
    // �I���t���O
    Release();
}

//=============================================================================
// [Updete]�X�V����
//=============================================================================
void CTime_UI::Update(void)
{
    // �^�C�}�[�X�V
    m_Timer->Updete();

    // �����̕ύX
    SetNumber();
}

//=============================================================================
// [Draw]�`�揈��
//=============================================================================
void CTime_UI::Draw(void)
{

}

//=============================================================================
// [SetNumber]�����̐ݒ�
//=============================================================================
void CTime_UI::SetNumber(void)
{
    // �^�C�}�[�̐��l��b�ɕϊ�
    int nTimeMin = m_Timer->GetTimer() / 60;

    // �����Ƃɕ���
    for (unsigned int nCntNum = 0; nCntNum < MAX_NAM; nCntNum++)
    {
        int nDrawRenge = (int)powf(NUM_RADIX, (float)nCntNum + 1);
        int nDrawRenge2 = (int)powf(NUM_RADIX, (float)nCntNum);
        int nAnswer = nTimeMin % nDrawRenge / nDrawRenge2;
        // 1�����ݒ�
        m_pNumber[nCntNum]->SetNumber(nAnswer);
    }

}
