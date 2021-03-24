//=============================================================================
//
// �����b�V���N���X [mesh_pillar.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mesh_pillar.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshPillar::CMeshPillar(PRIORITY Priority) :CMesh3d(Priority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshPillar::~CMeshPillar()
{

}

//=============================================================================
// �|���S������
//=============================================================================
CMeshPillar * CMeshPillar::Create(D3DXVECTOR3 pos, MESH_TYPE MeshNum)
{
	// �������m��
	CMeshPillar *pMeshPillar = new CMeshPillar;
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// ����������
	if (pMeshPillar != nullptr)
	{
		pMeshPillar->SetMeshNum(MeshNum);											// ���b�V�������p
		pMeshPillar->SetPos(pos);													// ���W�ݒ�
		pMeshPillar->Init();															// ������
		pMeshPillar->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));	// �e�N�X�`���̐ݒ�
	}

	return pMeshPillar;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshPillar::Init(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	// ���[�J���ϐ�/
	int nCount;
	int nCntIndex;
	int nCntIndex01 = 0;
	int nCntH;
	int nCntV;
	D3DXVECTOR3 pos = GetPos();
	// ���_�̐�
	int nWidth = GetMesh3D(GetMeshNum()).CylinderNum.nNumX;
	int nHeight = GetMesh3D(GetMeshNum()).CylinderNum.nNumY;

	// ���b�V���̃T�C�Y�ݒ�
	D3DXVECTOR2 MeshSize = D3DXVECTOR2(GetMesh3D(GetMeshNum()).size.x, GetMesh3D(GetMeshNum()).size.y);

	SetSize(D3DXVECTOR3(MeshSize.x, MeshSize.y, MeshSize.x));	// �T�C�Y
	SetRot(ZeroVector3);										// �p�x

	int VertexNum = (nWidth + 1) * (nHeight + 1);

	// �l�̏�����
	SetNumVertex(VertexNum);															// ���_�̐�

	int nTubeIndexNum = (nWidth + 1) * nHeight * 2 + (nHeight - 1) * 2;				// �������̃C���f�b�N�X
	int nIndexNum = nTubeIndexNum + (nWidth + 2);									// �C���f�b�N�X�̐�
	SetNumIndex(nIndexNum);															// �C���f�b�N�X�̐�

	int nPolygonNum = (nWidth * nHeight * 2 + (nHeight - 1) * 4) +4 + nWidth-2;		// �|���S�����ݒ�
	SetNumPolygon(nPolygonNum); 														// �|���S�����ݒ�

	// �o�b�t�@�ϐ�
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = NULL;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VertexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * GetNumIndex(),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIdxBuff,
		NULL);

	D3DXVECTOR3 pos = GetPos();
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < nHeight + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < nWidth + 1; nCntH++)
		{
			// ���_�̐ݒ�
			pVtx[(nCntV * (nWidth + 1)) + nCntH].pos = D3DXVECTOR3(
				pos.x + MeshSize.x*cosf(D3DXToRadian((360 / (nWidth ))*nCntH)),
				pos.y - (nCntV * MeshSize.y),
				pos.z + MeshSize.x*sinf(D3DXToRadian((360 / (nWidth ))*nCntH)));

			// �@���x�N�g���̐ݒ�
			pVtx[(nCntV * (nWidth + 1)) + nCntH].nor = D3DXVECTOR3(cosf(D3DXToRadian((360 / (nWidth))*nCntH)), 1.0f, sinf(D3DXToRadian((360 / (nWidth))*nCntH)));

			// �F�̐ݒ�
			pVtx[(nCntV * (nWidth + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntV * (nWidth + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
		}
	}

	// ���_�f�[�^���A�����b�N����
	pVtxBuff->Unlock();

	// �o�b�t�@����n��
	BindVtxBuff(pVtxBuff);

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCount = 0, nCntIndex = 0; nCount < nTubeIndexNum; nCount += 2)
	{
		if (((nCount + 2) % (((nWidth + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = nCntIndex - 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = nWidth + nCntIndex + 1;
		}
		else
		{
			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount] = nWidth + nCntIndex + 1;

			// �C���f�b�N�X�̐ݒ�
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}
	}

	VertexNum;

	int nTopNum = nWidth - 1;
	int VertexCount = 0;
	int nNumber = 0;

		// ���_�̃J�E���g�����ȉ��̏ꍇ
		while (VertexCount <= nWidth - 1)
		{
			// ��ԍŏ��̏k�ރ|���S������
			if (nCount == nTubeIndexNum)
			{
				// �C���f�b�N�X�̐ݒ�
				pIdx[nCount] = nCntIndex;
	
				// �C���f�b�N�X�̐ݒ�
				pIdx[nCount + 1] = nNumber;
	
				nCount += 2;
			}
			else
			{
				if (VertexCount % 2 == 0)
				{
					// �C���f�b�N�X�̐ݒ�
					pIdx[nCount] = nNumber;
	
					// �����琔�����グ��
					nNumber++;
				}
				else
				{
					// �C���f�b�N�X�̐ݒ�
					pIdx[nCount] = nTopNum;
	
					// �����璸�_�ԍ����グ��
					nTopNum--;
				}
	
				// ���_�����グ��
				VertexCount++;
				nCount++;
			}
		}

	nCount;

	// ���_�f�[�^���A�����b�N����
	pIdxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@��n��
	BindIdxBuff(pIdxBuff);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshPillar::Uninit(void)
{
	// �����[�X�̏���
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshPillar::Update(void)
{
	// �����蔻��
	Collision();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshPillar::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �F�̐ݒ�
	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
	material.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pDevice->GetMaterial(&OldMaterial);		// �Â��}�e���A���擾
	pDevice->SetMaterial(&material);		// �}�e���A���ݒ�
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// �e�N���X�`�揈��
	CMesh3d::Draw();

	// �Â��}�e���A���ɖ߂�
	pDevice->SetMaterial(&OldMaterial);
}