//=============================================================================================
//
// ���N���X [star.cpp]
// Author : Konishi Yuuto
//
//=============================================================================================

//=============================================================================================
// �C���N���[�h
//=============================================================================================
#include "star.h"
#include "manager.h"
#include "resource_manager.h"
#include "texture.h"
#include "player.h"
#include "game.h"
#include "collision.h"
#include "star_factory.h"

//=============================================================================================
// �}�N����`
//=============================================================================================
#define STAR_COLOR_RED		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))						// ��
#define STAR_COLOR_BLUE		(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))						// ��
#define STAR_COLOR_YELLOW	(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))						// ��
#define STAR_COLOR_GREEN	(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))						// ��

#define STAR_SIZE_X			(100.0f)												// ����
#define STAR_SIZE_Y			(100.0f)												// �c��
#define STAR_SIZE_Z			(0.0f)													// ���s
#define STAR_SIZE			(D3DXVECTOR3(STAR_SIZE_X, STAR_SIZE_Y, STAR_SIZE_Z))	// �T�C�Y

#define STAR_RADIUS			(STAR_SIZE_X)											// ���̔��a

//=============================================================================================
// �R���X�g���N�^
//=============================================================================================
CStar::CStar(PRIORITY Priority)
{
	m_PosNumber = { 0,0,0 };
	m_ColorType = STAR_COLOR_TYPE_NONE;
}

//=============================================================================================
// �f�X�g���N�^
//=============================================================================================
CStar::~CStar()
{
}

//=============================================================================================
// ���̐���
//=============================================================================================
CStar * CStar::Create(D3DXVECTOR3 pos, POS_NUMBER posNum)
{
	// �������m��
	CStar *pStar = new CStar;

	// !nullcheck
	if (pStar != nullptr)
	{
		// ����������
		pStar->Init(pos);
		pStar->m_PosNumber = posNum;
	}

	return pStar;
}

//=============================================================================================
// ����������
//=============================================================================================
HRESULT CStar::Init(D3DXVECTOR3 pos)
{
	// �r���{�[�h�̏���������
	CBillboard::Init(pos, STAR_SIZE);

	// �e�N�X�`���̃|�C���^
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// nullcheck
	if (pTexture != nullptr)
	{
		// �e�N�X�`���̐ݒ�
		BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_EFFECT));
	}

	// �F�̎�ސݒ�
	SetColorType();

	return S_OK;
}

//=============================================================================================
// �X�V����
//=============================================================================================
void CStar::Update(void)
{
}

//=============================================================================================
// �`�揈��
//=============================================================================================
void CStar::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}

//=============================================================================
// �����蔻��̏���
//=============================================================================
bool CStar::Collision(void)
{
	// �v���C���[�̐�
	int nPlayerNum = CGame::GetPlayerNum();

	for (int nCount = 0; nCount < nPlayerNum; nCount++)
	{
		// �v���C���[�̊֐�
		CPlayer *pPlayer = CGame::GetPlayer(nCount);

		// �����蔻��
		if (CCollision::CollisionCircularAndCircular(
			GetPos(), pPlayer->GetPos(),
			STAR_RADIUS, pPlayer->GetRadius()) == true)
		{
			return true;
		}
	}

	return false;
}

//=============================================================================
// �F�̎�ސݒ�
//=============================================================================
void CStar::SetColorType(void)
{
	int nColorType = rand() % (int)STAR_COLOR_TYPE_MAX;

	m_ColorType = (STAR_COLOR_TYPE)nColorType;
	// �F�̐ݒ�
	switch (m_ColorType)
	{
	case STAR_COLOR_TYPE_RED:
		// �ԐF
		SetColor(STAR_COLOR_RED);
		break;

	case STAR_COLOR_TYPE_BLUE:
		// �F
		SetColor(STAR_COLOR_BLUE);
		break;

	case STAR_COLOR_TYPE_GREEN:
		// �ΐF
		SetColor(STAR_COLOR_GREEN);
		break;

	case STAR_COLOR_TYPE_YELLOW:
		// ���F
		SetColor(STAR_COLOR_YELLOW);
		break;
	}
}