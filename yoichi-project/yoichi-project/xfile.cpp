//=============================================================================
//
// X�t�@�C���̊Ǘ��N���X [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
// ���f���l�[��
#define XFILE_NAME_BG						("data/model/bg_dome001.x")					// �w�i

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXfile::~CXfile()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CXfile * CXfile::Create(void)
{
	// �������m��
	CXfile *pXfile = new CXfile;

	return pXfile;
}

//=============================================================================
// X�t�@�C�����[�h
//=============================================================================
HRESULT CXfile::ModelLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_BG,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_BG].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_BG].dwNumMat,
		&m_aXfile[XFILE_NUM_BG].pMesh);

	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//�}�e���A�����̉��
		D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
		{
			// �t�@�C���l�[���̎擾
			char cData[128] = {};

			sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[nCount].apTexture[nCntMat]);
		}
	}

	return S_OK;
}

//=============================================================================
// X�t�@�C���A�����[�h
//=============================================================================
void CXfile::ModelUnLoad(void)
{
	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//���b�V���̔j��
		if (m_aXfile[nCount].pMesh != NULL)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = NULL;
		}
		//�}�e���A���̔j��
		if (m_aXfile[nCount].pBuffMat != NULL)
		{
			m_aXfile[nCount].pBuffMat->Release();
			m_aXfile[nCount].pBuffMat = NULL;
		}

		for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
		{
			if (m_aXfile[nCount].apTexture[nCntTexture] != NULL)
			{
				m_aXfile[nCount].apTexture[nCntTexture]->Release();
				m_aXfile[nCount].apTexture[nCntTexture] = NULL;
			}
		}
	}
}

//=============================================================================
// ���f���̏��
//=============================================================================
CXfile::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}

//=============================================================================
// ���f���Ɏg�p����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(XFILE_NUM TexNum)
{
	if (TexNum < XFILE_NUM_MAX)
	{
		if (m_aXfile[TexNum].apTexture != NULL)
		{
			return m_aXfile[TexNum].apTexture;
		}
	}

	return nullptr;
}
