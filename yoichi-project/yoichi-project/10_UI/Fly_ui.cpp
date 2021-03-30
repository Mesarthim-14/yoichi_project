//=============================================================================
//
// ��sUI�N���X[Fly.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "Fly_ui.h"
#include "ui.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//�v���C�����Ƃ�UI�̈ʒu
#define FLYUI_POS_PLAYER1 {SCREEN_WIDTH/4,SCREEN_HEIGHT/4-150.0f,0.0f}
#define FLYUI_POS_PLAYER2 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2),SCREEN_HEIGHT/4-150.0f,0.0f}
#define FLYUI_POS_PLAYER3 {SCREEN_WIDTH/4,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-150.0f,0.0f}
#define FLYUI_POS_PLAYER4 {SCREEN_WIDTH/4+(SCREEN_WIDTH/2),SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-150.0f,0.0f}

#define FLY_UI_SIZE_X (128.0f)                        // UI�̃T�C�Y
#define FLY_UI_SIZE_Y (32.0f)                        // UI�̃T�C�Y
#define FLY_UI_SIZE_Z (0.0f)                          // UI�̃T�C�Y


#define FLY_UI_COLOR {0.0f,1.0f,1.0f,1.0f}          // UI�̐F
//*****************************************************************************
// �}�N����`
//*****************************************************************************
const D3DXVECTOR3 CFly_UI::m_UIPos[MAX_PLAYER_NUM] =
{
    { FLYUI_POS_PLAYER1 },
    { FLYUI_POS_PLAYER2 },
    { FLYUI_POS_PLAYER3 },
    { FLYUI_POS_PLAYER4 }
};// �v���C���[���Ƃ�UI�̈ʒu

//=============================================================================
// [CFly_UI] �R���X�g���N�^
//=============================================================================
CFly_UI::CFly_UI(PRIORITY Priority) : CScene(Priority)
{
}

//=============================================================================
// [~CFly_UI] �f�X�g���N�^
//=============================================================================
CFly_UI::~CFly_UI()
{
}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CFly_UI * CFly_UI::Create(void)
{
    CFly_UI *FlyUI = nullptr;
    if (FlyUI == nullptr)
    {
        // �������̊m�ۂƏ�����
        FlyUI = new CFly_UI;
        FlyUI->Init();
    }
    return FlyUI;
}

//=============================================================================
// [Init] ����������
//=============================================================================
HRESULT CFly_UI::Init(void)
{
    return S_OK;
}

//=============================================================================
// [Init] ����������
// ����
// nPlayerNum�@:�@�v���C���[�̔ԍ�
//=============================================================================
void CFly_UI::Init(int nPlayerNum)
{
    // �e�N�X�`���̃|�C���^�擾
    CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

    // �v���C���[�ԍ���ۑ�
    m_nPkayerNum = nPlayerNum;

    m_pUI = CUi::Create(m_UIPos[m_nPkayerNum], { FLY_UI_SIZE_X ,FLY_UI_SIZE_Y ,FLY_UI_SIZE_Z });
    m_pUI->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLY_FRAME));

    m_pGauge = CPolygon::Create(m_UIPos[m_nPkayerNum], { FLY_UI_SIZE_X ,FLY_UI_SIZE_Y ,FLY_UI_SIZE_Z });
    m_pGauge->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLY_GAUGE));

}

//=============================================================================
// [Uninit]�I������
//=============================================================================
void CFly_UI::Uninit(void)
{
        //// !nullcheck
        //if (m_pUI != nullptr)
        //{
        //    // UI�̏I������
        //    m_pUI->Uninit();
        //    m_pUI = NULL;
        //}

        // !nullcheck
        if (m_pGauge != nullptr)
        {
            // �Q�[�W�̏I������
            m_pGauge->Uninit();
            delete m_pGauge;
            m_pGauge = NULL;
        }

    Release();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CFly_UI::Update(void)
{
    SetFly();
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CFly_UI::Draw(void)
{
    m_pGauge->Draw();
}

//=============================================================================
// [SetFly] ��s�̐ݒ�
//=============================================================================
void CFly_UI::SetFly(void)
{
    // ��s���Ԃ̎擾
   int FliTime = CGame::GetPlayer(m_nPkayerNum)->GetFlyTime();

   // �ʒu�ƃT�C�Y�𔽉f
   m_pGauge->UpdateVertex(FliTime, MAX_FLY_TIME);

}

