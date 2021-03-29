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
#include "player.h"

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
const D3DXVECTOR3 CStar_UI::m_posUI[MAX_PLAYER_NUM] =
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
        StarUI->Init();
    }
    return StarUI;
}

//=============================================================================
// [Init] ����������
//=============================================================================
HRESULT CStar_UI::Init(void)
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
    SetStarNum();
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
    // �ϐ��錾
    D3DXVECTOR3 pos;
   int nPlayerTotal = CGame::GetPlayerNum();
   CTexture *pTexture = GET_TEXTURE_PTR;

   // �v���C���[�ԍ���ۑ�
   m_nPlayerNum = nPlayerNum;

   // �v���C���[�ԍ��̕ۑ�
   m_nPlayerNum = nPlayerNum;

   // �i���o�[����
   for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
   {
       pos = { m_posUI[nPlayerNum].x - (nCntNum*50.0f), m_posUI[nPlayerNum].y ,m_posUI[nPlayerNum].z };
       m_apNumber[nCntNum] = CNumber2d::Create(pos, { 50.0f,80.0f,0.0f });
       m_apNumber[nCntNum]->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_NUMBER));
   }
}

//=============================================================================
// [SetStarNum] ���̐��̐ݒ�
//=============================================================================
void CStar_UI::SetStarNum(void)
{
    // �v���C���[�̐��̏��������擾
   int nStarNum = CGame::GetPlayer(m_nPlayerNum)->GetStarNum();

    // �i���o�[�̕���
    for (int nCntNum = 0; nCntNum < STAR_NUM; nCntNum++)
    {
        int nDrawRenge = (int)powf(10.0f, (float)nCntNum + 1);
        int nDrawRenge2 = (int)powf(10.0f, (float)nCntNum);
        int nAnswer = nStarNum % nDrawRenge / nDrawRenge2;
        // 1�����ݒ�
        m_apNumber[nCntNum]->SetNumber(nAnswer);
    }
}
