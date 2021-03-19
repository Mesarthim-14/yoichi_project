//=============================================================================
//
// ���̎擾��UI�N���X[star_ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "star_ui.h"
#include "number_2d.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//�v���C�����Ƃ�UI�̈ʒu
#define STARUI_POS_PLAYER1 {SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4+130.0f,0.0f}
#define STARUI_POS_PLAYER2 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4+130.0f,0.0f}
#define STARUI_POS_PLAYER3 {SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)+130.0f,0.0f}
#define STARUI_POS_PLAYER4 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)+130.0f,0.0f}

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
// �v���C���[���Ƃ�UI�̈ʒu
const D3DXVECTOR3 CStar_UI::m_pos[MAX_PLAYER] =
{
    { STARUI_POS_PLAYER1 },
    { STARUI_POS_PLAYER2 },
    { STARUI_POS_PLAYER3 },
    { STARUI_POS_PLAYER4 }
};

//=============================================================================
// [CStar_UI] �R���X�g���N�^
//=============================================================================
CStar_UI::CStar_UI()
{

}

//=============================================================================
// [~CStar_UI] �f�X�g���N�^
//=============================================================================
CStar_UI::~CStar_UI()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CStar_UI *CStar_UI::Create(void)
{
    CStar_UI *StarUI = nullptr;
    if (StarUI == nullptr)
    {
        // �������̊m�ۂƏ�����
        StarUI = new CStar_UI;
        StarUI->Init(ZeroVector3, ZeroVector3);
    }
    return StarUI;
}

//=============================================================================
// [Init] ����������
//=============================================================================
HRESULT CStar_UI::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
    return S_OK;
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CStar_UI::Uninit(void)
{
    // �i���o�[�̔j��
    // �i���o�[����
    for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
    {
        m_apNumber[nCntNum]->Uninit();

    }
    Release();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CStar_UI::Update(void)
{
    // �i���o�[�̍X�V
    for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
    {
        m_apNumber[nCntNum]->SetNumber(nCntNum);
    }
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CStar_UI::Draw(void)
{
}

//=============================================================================
// [SetPosition] �ʒu�̐ݒ�
//=============================================================================
void CStar_UI::SetPosition(int nPlayerNum)
{

    D3DXVECTOR3 pos;
   int nPlayerTotal = CGame::GetPlayerNum();

   CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

   // �i���o�[����
   for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
   {
       pos = { m_pos[nPlayerNum].x + (nCntNum*50.0f), m_pos[nPlayerNum].y ,m_pos[nPlayerNum].z };
       m_apNumber[nCntNum] = CNumber2d::Create(pos, { 50.0f,80.0f,0.0f });
       m_apNumber[nCntNum]->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_NUMBER));
   }
}