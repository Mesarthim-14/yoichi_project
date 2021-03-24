//=================================================================================
//
// �o���A�G�t�F�N�g�N���X�w�b�_�[ [barrier_effect.cpp]
// Author : Ito Yogo
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "barrier.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "xfile.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"

//=================================================================================
// �C���X�^���X����
//=================================================================================
CBARRIER * CBARRIER::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum)
{
	// �������m��
	CBARRIER *pBarriereffect = new CBARRIER;

	// !nullcheck
	if (pBarriereffect != NULL)
	{
		pBarriereffect->m_RotQuantity.y = fAngle;	// ��]��
		pBarriereffect->m_Scale = scale;			// �g�嗦
		pBarriereffect->m_nPlayerNum = nPlayerNum;	// �v���C���[�̔ԍ�

		// ����������
		pBarriereffect->Init(pos, size);
	}

	return pBarriereffect;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CBARRIER::CBARRIER()
{
	m_RotQuantity = ZeroVector3;	// ��]�ʂ̏�����
	m_Scale = ZeroVector3;			// �g�嗦�̏�����
	m_nPlayerNum = 0;				// �v���C���[�̔ԍ��̏�����
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CBARRIER::~CBARRIER()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CBARRIER::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// X�t�@�C���̃|�C���^
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	//���f������ݒ�
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_BARRIER));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_BARRIER));

	// ����������
	CModel::Init();

	// �̗͐ݒ�
	CModel::SetLife(BARRIER_LIFE);
	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CBARRIER::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CBARRIER::Update(void)
{
	// �X�V����
	CModel::Update();

	// ���W�̍X�V
	D3DXVECTOR3 pos = CModel::GetPos();
	pos = CGame::GetPlayer(m_nPlayerNum)->GetPos();
	CModel::SetPos(pos);

	// �T�C�Y�̍X�V
	D3DXVECTOR3 size = CModel::GetSize();
	size += m_Scale;
	if (size.x >= BARRIER_MAX_SIZE.x)
	{
		size = BARRIER_MAX_SIZE;
	}
	else
	{
		// ��]�̍X�V
		D3DXVECTOR3 rot = CModel::GetRot();
		rot += m_RotQuantity;
		CModel::SetRot(rot);
	}
	CModel::SetSize(size);
}

//=================================================================================
// �`�揈��
//=================================================================================
void CBARRIER::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL*pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// ���C�g�̌��ʂ���������
		pDevice->LightEnable(0, false);

		// �`�揈��
		CModel::Draw();

		// ���C�g�̌��ʂ�t���Ȃ���
		pDevice->LightEnable(0, true);
	}
}