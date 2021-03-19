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
#define XFILE_NAME_BG						("data/model/bg_dome001.x")		// �w�i
#define XFILE_NAME_ITEM_BOX					("data/model/item_box.x")		// �A�C�e���{�b�N�X
#define XFILE_NAME_BOMB_BOX					("data/model/item_bombbox.x")		// �U�{�b�N�X
#define XFILE_NAME_BG				("data/model/bg_dome001.x")	// �w�i
#define XFILE_NAME_WINDSPHERE		("data/model/windsphere.x")	// ���̋�
#define XFILE_NAME_BARRIER			("data/model/barrier.x")	// �o���A
#define XFILE_NAME_BARRIER_EFFECT	("data/model/barrier_effect.x")	// �o���A�G�t�F�N�g

// �K�w�\�����f���̃t�@�C��
#define HIERARCHY_FILENAME_PLAYER			("data/Text/motion_PLAYER.txt")	// �v���C���[�̃t�@�C���l�[��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
	memset(m_aModelFile, 0, sizeof(m_aModelFile));
	memset(m_pFileName, 0, sizeof(m_pFileName));
	memset(m_nMaxParts, 0, sizeof(m_nMaxParts));
	memset(m_aHierarchyModel, 0, sizeof(m_aHierarchyModel));
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
	D3DXLoadMeshFromX(XFILE_NAME_ITEM_BOX,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_ITEM_BOX].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_ITEM_BOX].dwNumMat,
		&m_aXfile[XFILE_NUM_ITEM_BOX].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_BOMB_BOX,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_BOMB_BOX].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_BOMB_BOX].dwNumMat,
		&m_aXfile[XFILE_NUM_BOMB_BOX].pMesh);

	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_aXfile[nCount].xFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_aXfile[nCount].pBuffMat,
			NULL,
			&m_aXfile[nCount].dwNumMat,
			&m_aXfile[nCount].pMesh);

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
// �K�w�\���̃��f���t�@�C���ǂݍ���
//=============================================================================
HRESULT CXfile::HierarchyReadFile(void)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	// ���f���̃C���f�b�N�X
	int nMotionType = 0;	// ���[�V�����̃^�C�v
	int nKeyNum = 0;		// �L�[�ԍ�
	int nMotionNum = 0;		// ���[�V�����ԍ�

	// �t�@�C���̖��O��ݒ�
	SetFileName();

	for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
	{
		// �t�@�C���I�[�v��
		pFile = fopen(m_pFileName[nModelCnt], "r");

		if (pFile != NULL)
		{
			do
			{
				//���ǂݍ���Ń��[�h���𒊏o
				fgets(aHeadData, sizeof(aHeadData), pFile);
				sscanf(aHeadData, "%s", aModeName);

				if (strcmp(aModeName, "MODEL_FILENAME") == 0)
				{
					//X�t�@�C���̖��O
					sscanf(aHeadData, "%*s %*s %s %*s %*s", m_aModelFile[nModelIndex][nModelCnt].xFileName);

					//�C���f�b�N�X���P�i�߂�
					nModelIndex++;
				}

				if (strcmp(aModeName, "CHARACTERSET") == 0)
				{
					//�C���f�b�N�X���ŏ��ɖ߂�
					nModelIndex = 0;

					//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
					while (strcmp(aModeName, "END_CHARACTERSET") != 0)
					{
						//���ǂݍ���Ń��[�h���𒊏o
						fgets(aHeadData, sizeof(aHeadData), pFile);
						sscanf(aHeadData, "%s", aModeName);

						if (strcmp(aModeName, "PARTSSET") == 0)
						{
							//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
							while (strcmp(aModeName, "END_PARTSSET") != 0)
							{
								//���ǂݍ���Ń��[�h���𒊏o
								fgets(aHeadData, sizeof(aHeadData), pFile);
								sscanf(aHeadData, "%s", aModeName);

								if (strcmp(aModeName, "PARENT") == 0)
								{
									//�e�q���̐ݒ�
									sscanf(aHeadData, "%*s %*s %d", &m_aModelFile[nModelIndex][nModelCnt].nParent);
								}
								if (strcmp(aModeName, "POS") == 0)
								{
									//�ʒu�̐ݒ�
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetPos.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetPos.y, &m_aModelFile[nModelIndex][nModelCnt].offsetPos.z);
								}
								if (strcmp(aModeName, "ROT") == 0)
								{
									//�����̐ݒ�
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetRot.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetRot.y, &m_aModelFile[nModelIndex][nModelCnt].offsetRot.z);
								}
							}

							//�C���f�b�N�X���P�i�߂�
							nModelIndex++;

							// �p�[�c���𐔂���
							m_nMaxParts[nModelCnt]++;

						}
					}
				}

			} while (strcmp(aModeName, "END_SCRIPT") != 0);

			//�t�@�C���N���[�Y
			fclose(pFile);

			return S_OK;
		}
		else
		{
			//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
			MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

			return	E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// �K�w�\���̃��f�����[�h
//=============================================================================
HRESULT CXfile::HierarchyModelLoad(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
		{
			//���f���̓ǂݍ���
			D3DXLoadMeshFromX(m_aModelFile[nCount][nXFileNumCnt].xFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat,
				NULL,
				&m_aHierarchyModel[nCount][nXFileNumCnt].dwNumMat,
				&m_aHierarchyModel[nCount][nXFileNumCnt].pMesh);

			//�}�e���A�����̉��
			D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)m_aHierarchyModel[nCount][nXFileNumCnt].dwNumMat; nCntMat++)
			{
				if (materials[nCntMat].pTextureFilename != NULL)
				{
					// �t�@�C���l�[���̎擾
					char cData[256] = {};

					sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice, cData, &m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntMat]);
				}
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �K�w�\���̃A�����f�����[�h
//=============================================================================
void CXfile::HierarchyModelUnLoad(void)
{
	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nCount]; nCount++)
		{
			//�}�e���A�����̔j��
			if (m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat != NULL)
			{
				m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat->Release();
				m_aHierarchyModel[nCount][nXFileNumCnt].pBuffMat = nullptr;
			}

			//���b�V�����̔j��
			if (m_aHierarchyModel[nCount][nXFileNumCnt].pMesh != NULL)
			{
				m_aHierarchyModel[nCount][nXFileNumCnt].pMesh->Release();
				m_aHierarchyModel[nCount][nXFileNumCnt].pMesh = nullptr;
			}

			// �e�N�X�`���̊J��
			for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
			{
				if (m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntTexture] != NULL)
				{
					m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntTexture]->Release();
					m_aHierarchyModel[nCount][nXFileNumCnt].apTexture[nCntTexture] = NULL;
				}
			}
		}
	}
}

//=============================================================================
// �t�@�C���̖��O��ݒ�
//=============================================================================
void CXfile::SetFileName(void)
{
	m_pFileName[HIERARCHY_XFILE_NUM_PLAYER] = HIERARCHY_FILENAME_PLAYER;
	m_aXfile[XFILE_NUM_BG].xFileName = XFILE_NAME_BG;
	m_aXfile[XFILE_NUM_WINDSPHERE].xFileName = XFILE_NAME_WINDSPHERE;
	m_aXfile[XFILE_NUM_BARRIER].xFileName = XFILE_NAME_BARRIER;
	m_aXfile[XFILE_NUM_BARRIER_EFFECT].xFileName = XFILE_NAME_BARRIER_EFFECT;
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