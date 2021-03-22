//=================================================================================
//
// ���N���X�w�b�_�[ [wind.cpp]
// Author : Ito Yogo
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "wind.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "xfile.h"
#include "resource_manager.h"

//=================================================================================
// �C���X�^���X����
//=================================================================================
CWind * CWind::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum)
{
	// �������m��
	CWind *pWind = new CWind;

	// !nullcheck
	if (pWind != NULL)
	{
		// ��]�ʂ����ȏ�Ȃ�
		if (fAngle >= 1.0f || fAngle <= -1.0f)
		{
			// ��]��
			pWind->m_RotQuantity =
				D3DXVECTOR3(D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))),
					D3DXToRadian((float)(rand() % (int)fAngle - ((int)fAngle / 2))));
		}

		pWind->m_Scale = scale;	// �g�嗦

		// ����������
		pWind->Init(pos, size);
	}

	return pWind;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CWind::CWind()
{
	m_RotQuantity = ZeroVector3;	// ��]�ʂ̏�����
	m_Scale = ZeroVector3;			// �g�嗦�̏�����
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CWind::~CWind()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CWind::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// X�t�@�C���̃|�C���^
	CXfile *pXFile = CManager::GetResourceManager()->GetXfileClass();

	//���f������ݒ�
	BindModel(pXFile->GetXfile(CXfile::XFILE_NUM_WINDSPHERE));
	BindTexture(pXFile->GetXfileTexture(CXfile::XFILE_NUM_WINDSPHERE));

	// ����������
	CModel::Init(pos, size);

	// �̗͐ݒ�
	CModel::SetLife(WIND_LIFE);
	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CWind::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CWind::Update(void)
{
	// �X�V����
	CModel::Update();

	// �T�C�Y�̍X�V
	D3DXVECTOR3 size = CModel::GetSize();
	size += m_Scale;
	CModel::SetSize(size);

	// ��]�̍X�V
	D3DXVECTOR3 rot = CModel::GetRot();
	rot += m_RotQuantity;
	CModel::SetRot(rot);
}

//=================================================================================
// �`�揈��
//=================================================================================
void CWind::Draw(void)
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

		CModel::SubAlpha(0.00001f);

		// �`�揈��
		CModel::Draw();

		// ���C�g�̌��ʂ�t���Ȃ���
		pDevice->LightEnable(0, true);
	}
}