//=============================================================================
//
// �i���o�[3D�N���X [number_3d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "number_3d.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DAMAGE_HEIGHT				(1)			// ����
#define DAMAGE_LIFE_NUM				(100)		// ���C�t
#define DAMAGE_NUM_GRAVITY			(1.4f)		// �d��
#define DAMAGE_NUM_REFLECT_POWER	(2)			// �o�E���h�̊���
#define DAMAGE_NUM_REFLECT_POWER_Y	(20)		// �o�E���h�̈ړ���
#define DAMAGE_RAND_MOVE_X			(4)			// �ړ���
#define DAMAGE_RAND_MOVE_Y			(30)		// �ړ���
#define DAMAGE_RAND_MOVE_Z			(4)			// �ړ���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNumber3d::CNumber3d(PRIORITY Priority) : CMesh3d(Priority)
{
	D3DXMatrixIdentity(&m_mtxWorld);
	m_bInverse = true;
	m_nLife = 0;
	m_move = ZeroVector3;
	m_nBoundCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNumber3d::~CNumber3d()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CNumber3d * CNumber3d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum)
{
	// �C���X�^���X����
	CNumber3d *pNumber3d = new CNumber3d;
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// nullcheck
	if (pNumber3d != NULL)
	{		
		// ���������
		pNumber3d->m_nNumber = nNum;																	// �l�̑��
		pNumber3d->Init(pos, size);																		// ����������
	//	pNumber3d->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_DAMAGE_NUMBER));		// �e�N�X�`���̐ݒ�
		pNumber3d->m_nLife = DAMAGE_LIFE_NUM;															// ���C�t�̐ݒ�
		pNumber3d->RandSetMove();																		// �ړ��ʂ̐ݒ�
	}

	return pNumber3d;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNumber3d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	// ���[�J���ϐ�/
	int nCount = 0;				// for���p
	int nCntIndex = 0;			// ���_�ԍ��ݒ�p
	int nCntH= 0;				// �����̃J�E���^
	int nCntV= 0;				// �����̃J�E���^
	int nWidth = 0;				// �����̐�
	int nNum[3]{ 0, 0, 0 };		// ��������z��
	int nIndex = 0;				// �����킹�p
	int nDigit = 0;				// �������擾
	int nNumber = m_nNumber;	// ���݂̒l��ێ�

	// ���������߂�
	while (nNumber != 0)
	{
		nNumber /= 10;
		nDigit++;
	}

	// �����擾
	nWidth = nDigit;

	// ���̒l�擾
	for (int nCount = 0, nIndex = nWidth - 1; nCount < nWidth; nCount++, nIndex--)
	{
		nNum[nIndex] = (m_nNumber / (int)(pow(10, nCount))) % 10;
	}

	// �|���S���̍���
	int nHeight = DAMAGE_HEIGHT;

	// �l�̏�����
	SetNumVertex(((nWidth + 1) * (nHeight + 1)) + (nWidth - 1) * (nHeight + 1));	// ���_�̐�
	SetNumIndex(((nWidth + 1)*(nHeight + 1)) + (nWidth - 1) * (nHeight + 1));		// �C���f�b�N�X�̐�
	SetNumPolygon((nWidth * 2)+ ((nWidth-1) * 2));									// �|���S�����ݒ�

	// 1�u���b�N�̃T�C�Y
	SetOneSize(D3DXVECTOR2(size.x * 2 / nWidth, size.y * 2 / nHeight));	// 24000/4

	// �o�b�t�@�̐錾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = NULL;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GetNumVertex(),
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

	// ���W�̐ݒ�
	SetPos(pos);
	SetSize(size);

	int nWidthNum = (nWidth + 1) + nWidth - 1;	// �����̒l
	int nOdd = 0;								// ��̃J�E���g
	
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nNumCount = 0, nCntV = 0; nCntV < nHeight + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < nWidthNum; nCntH++)
		{
			if (((nCntV * (nWidthNum)) + nCntH) % 2 == 0 && nCntH != 0)
			{// 0�ȊO�̋����̎��A�O��Ɠ������W�ɐݒ肷��

				// ���_�̐ݒ�
				pVtx[(nCntV * (nWidthNum)) + nCntH].pos = pVtx[((nCntV * (nWidthNum)) + nCntH) - 1].pos;

				// �e�N�X�`�����W�̐ݒ�
				pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10)), float(nCntV * 1.0f));
			}
			else
			{
				// ���_�̐ݒ�
				pVtx[(nCntV * (nWidthNum)) + nCntH].pos = D3DXVECTOR3(
					(- (size.x / 2)) + (nOdd * (size.x / nWidth)), ( + size.y / 2) - nCntV*size.y, 0.0f);

				if (nCntH == 0)
				{// ��ԍ��[��������

					// �e�N�X�`�����W�̐ݒ�
					pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10)), float(nCntV * 1.0f));
				}
				else if (nCntH == 1)
				{// 1�������Ƃ�
					nOdd++;

					// ���_�̐ݒ�
					pVtx[(nCntV * (nWidthNum)) + nCntH].pos = D3DXVECTOR3(
						(- (size.x / 2)) + (nOdd * (size.x / nWidth)), (+ size.y / 2) - nCntV*size.y, 0.0f);

					// �e�N�X�`�����W�̐ݒ�
					pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10) + 0.1f), float(nCntV * 1.0f));

					nNumCount++;

				}
				else
				{
					// ���_�̋�����i�߂�
					nOdd++;

					// ���_�̐ݒ�
					pVtx[(nCntV * (nWidthNum)) + nCntH].pos = D3DXVECTOR3(
						(- (size.x / 2)) + (nOdd * (size.x / nWidth)), ( + size.y / 2) - nCntV*size.y, 0.0f);

					// �e�N�X�`�����W�̐ݒ�
					pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10)+0.1f), float(nCntV * 1.0f));

					nNumCount++;
				}
			}

			// �@���x�N�g���̐ݒ�
			pVtx[(nCntV * (nWidthNum)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �F�̐ݒ�
			pVtx[(nCntV * (nWidthNum)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		}

		// ���ɃV�t�g
		nNumCount = 0;
		nOdd = 0;
	}

	// ���_�f�[�^���A�����b�N����
	pVtxBuff->Unlock();

	// �o�b�t�@����n��
	BindVtxBuff(pVtxBuff);

	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCount = 0, nCntIndex = 0; nCount < GetNumIndex(); nCount += 2)
	{
		// �C���f�b�N�X�̐ݒ�
		pIdx[nCount] = nWidthNum - 1 + nCntIndex + 1;

		// �C���f�b�N�X�̐ݒ�
		pIdx[nCount + 1] = nCntIndex;

		nCntIndex++;
	}

	// ���_�f�[�^���A�����b�N����
	pIdxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@��n��
	BindIdxBuff(pIdxBuff);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNumber3d::Uninit(void)
{
	// �����[�X
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNumber3d::Update(void)
{
	// �d��
	Gravity();

	// ���W�̐ݒ�
	SetPos(D3DXVECTOR3(GetPos().x + m_move.x, GetPos().y + m_move.y, GetPos().z + m_move.z));

	// ���C�t
	m_nLife--;

	// 0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNumber3d::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�̃}�g���N�X

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �t�s��
	if (m_bInverse == true)
	{
		// ��]�̋t�s��̐���
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&m_mtxWorld, NULL,
			&mtxRot);

		m_mtxWorld._41 = 0;
		m_mtxWorld._42 = 0;
		m_mtxWorld._43 = 0;

	}
	else
	{
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	BindMtxWorld(m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetIndices(GetIdxBuff());

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, GetNumVertex(), 0, GetNumPolygon());

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// ���Ԃ���Ȃ��悤�ɂ���@(Z�o�b�t�@)
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
void CNumber3d::RandSetMove(void)
{
	// ����
	D3DXVECTOR3 move = D3DXVECTOR3(
		(float)(-rand() % DAMAGE_RAND_MOVE_X - rand() % DAMAGE_RAND_MOVE_X - rand() % DAMAGE_RAND_MOVE_X),
		DAMAGE_RAND_MOVE_Y,
		(float)(-rand() % DAMAGE_RAND_MOVE_Z - rand() % DAMAGE_RAND_MOVE_Z - rand() % DAMAGE_RAND_MOVE_Z));

	// �ړ��ʂ̐ݒ�
	m_move = D3DXVECTOR3(move);
}

//=============================================================================
// �d��
//=============================================================================
void CNumber3d::Gravity(void)
{
	if (GetPos().y > 0.0f)
	{
		// �d�͂�������
		m_move.y -= DAMAGE_NUM_GRAVITY;
	}
	else
	{// �n�ʂɕt�����Ƃ��̏���
		m_move.y = 0.0f;
		m_nBoundCounter++;
		m_move.y = (float)DAMAGE_NUM_REFLECT_POWER_Y - m_nBoundCounter*DAMAGE_NUM_REFLECT_POWER;

		// ���W�̐ݒ�
		SetPos(D3DXVECTOR3(GetPos().x, 0.0f, GetPos().z));
	}

}