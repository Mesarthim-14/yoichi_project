//=================================================================================
//
// �o���A�G�t�F�N�g�N���X�w�b�_�[ [barrier_effect.cpp]
// Author : Ito Yogo
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "barrier_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "xfile.h"
#include "resource_manager.h"

//=================================================================================
// �C���X�^���X����
//=================================================================================
CBARRIEREFFECT * CBARRIEREFFECT::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fAngle)
{
	// �������m��
	CBARRIEREFFECT *pBarriereffect = new CBARRIEREFFECT;

	// !nullcheck
	if (pBarriereffect != NULL)
	{
		// �ړ��ʂ����ȏ�Ȃ�
		if (move.x >= 1.0f || move.x <= -1.0f &&
			move.y >= 1.0f || move.y <= -1.0f &&
			move.z >= 1.0f || move.z <= -1.0f)
		{
			// �ړ���
			move = D3DXVECTOR3((float)(rand() % (int)move.x - ((int)move.x / 2)),
				(float)(rand() % (int)move.y - ((int)move.y / 2)),
				(float)(rand() % (int)move.z - ((int)move.z / 2)));
		}

		// ��]�ʂ����ȏ�Ȃ�
		if (fAngle >= 1.0f || fAngle <= -1.0f)
		{
			// ��]��
			pBarriereffect->m_RotQuantity =
				D3DXVECTOR3(D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))));
		}

		// ����������
		pBarriereffect->Init(pos, size, move);
	}

	return pBarriereffect;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CBARRIEREFFECT::CBARRIEREFFECT()
{
	m_RotQuantity = ZeroVector3;	// ��]�ʂ̏�����
	m_Scale = ZeroVector3;			// �g�嗦�̏�����
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CBARRIEREFFECT::~CBARRIEREFFECT()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CBARRIEREFFECT::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	// X�t�@�C���̃|�C���^
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	//���f������ݒ�
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_BARRIER_EFFECT));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_BARRIER_EFFECT));

	// ����������
	CModel::Init();

	// ���W����^����
	CModel::SetPos(pos);
	CModel::SetMove(move);

	// �̗͐ݒ�
	CModel::SetLife(BARRIEREFFECT_LIFE);
	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CBARRIEREFFECT::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CBARRIEREFFECT::Update(void)
{
	// �X�V����
	CModel::Update();

	// ��]�̍X�V
	D3DXVECTOR3 rot = CModel::GetRot();
	rot += m_RotQuantity;
	CModel::SetRot(rot);
}

//=================================================================================
// �`�揈��
//=================================================================================
void CBARRIEREFFECT::Draw(void)
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