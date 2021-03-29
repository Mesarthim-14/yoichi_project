//=============================================================================
//
// 3D���b�V�������N���X [mesh_3d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mesh_3d.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MESH_3D_FILENAME		("data/Text/mesh_3d.txt")

//=============================================================================
// �O���錾
//=============================================================================
CMesh3d::MESH_3D CMesh3d::m_Mesh3D[MESH_TYPE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMesh3d::CMesh3d(PRIORITY Priority):CSceneBase(Priority)
{
	m_pIdxBuff = nullptr;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumVertex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_OneSize = ZeroVector2;
	m_MeshNum = MESH_TYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMesh3d::~CMesh3d()
{
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMesh3d::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �p�x
	D3DXVECTOR3 rot = GetRot();

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,
		rot.y,
		rot.x,
		rot.z);

	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// ���W
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�𔽉f
	D3DXMatrixTranslation(
		&mtxTrans,
		pos.x,
		pos.y,
		pos.z);

	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// �t�@�C���ǂݍ���
//=============================================================================
HRESULT CMesh3d::ReadFile(void)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// ���f���̃C���f�b�N�X

	// �t�@�C���I�[�v��
	pFile = fopen(MESH_3D_FILENAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "MESH3DSET") == 0)
			{
				//�C���f�b�N�X���ŏ��ɖ߂�
				nParticleIndex = 0;

				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aParticleName, "END_MESH3DSET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "MESHSET") == 0)
					{
						//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (strcmp(aParticleName, "END_MESHSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "WIDTH") == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData, "%*s %*s %d", &m_Mesh3D[nParticleIndex].CylinderNum.nNumX);
							}
							if (strcmp(aParticleName, "HEIGHT") == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData, "%*s %*s %d", &m_Mesh3D[nParticleIndex].CylinderNum.nNumY);
							}

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f",
									&m_Mesh3D[nParticleIndex].size.x,
									&m_Mesh3D[nParticleIndex].size.y);
							}
						}

						//�C���f�b�N�X���P�i�߂�
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

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

//=============================================================================
// �����蔻��
//=============================================================================
void CMesh3d::Collision(void)
{
	for (int nCount = 0; nCount < CGame::GetPlayerNum(); nCount++)
	{
		// �v���C���[�̃|�C���^
		CPlayer *pPlayer = CGame::GetPlayer(nCount);

		// nullcheak
		if (pPlayer != nullptr)
		{
			// ���b�V�����
			D3DXVECTOR3 pos = GetPos()*2;
			float fRadius = GetSize().x;

			// �v���C���[�̏��擾
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();		// ���W�擾
			float fPlayerRadius = pPlayer->GetRadius();		// ���a

			// ��_�̋����A��_�̊p�x�ݒ�
			float fLength = sqrtf(
				powf((PlayerPos.x - pos.x), 2) +
				powf((PlayerPos.z - pos.z), 2));

			// ��������
			float fDistance = fRadius + fPlayerRadius;

			// �����蔻��
			if (pos.y >= PlayerPos.y)
			{
				if (fLength <= fDistance)
				{
					// ��̔���
					if (pos.y <= pPlayer->GetOldPos().y)
					{
						// y���W
						pPlayer->Landing(pos.y);
					}
					else
					{
						// ���ɓ��������Ƃ������߂�����
						D3DXVECTOR3 vec = D3DXVECTOR3(PlayerPos.x - pos.x, 0.0f, PlayerPos.z - pos.z);
						D3DXVec3Normalize(&vec, &vec);
						vec *= fDistance;
						
						pPlayer->SetPos(D3DXVECTOR3(pos.x + vec.x, PlayerPos.y, pos.z + vec.z));
					}
				}
			}
		}
	}
}