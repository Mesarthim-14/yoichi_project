//=============================================================================
//
// �V�[��3D�N���X [scene3D.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CSceneBase(Priority)
{
	m_nCountAnim = 0;								// �A�j���[�V�����e�N�X�`��
	m_nCountAnimPattern = 0;						// �A�j���[�V�����̃p�^�[��
	m_nCounterAnim = 0;								// �A�j���[�V�����̃J�E���^�[
	m_nPatternAnim = 0;								// �A�j���[�V�����̃p�^�[����
	m_nLoop = -1;									// ���[�v���邩�ǂ���
	m_nLife = 0;
	m_fScaleNum = 0.0f;								// �X�P�[��
	m_nAlphaNum = 0;								// �A���t�@�e�X�g�̒l
	m_bAlpha = false;								// �A���t�@�e�X�g�̃t���O
	m_bInverse = false;
	m_fAlphaNum = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�ϐ��̐錾
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	// �ϐ����
	SetPos(pos);
	SetSize(size);

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[1].pos = D3DXVECTOR3(+(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(GetSize().x / 2), -(GetSize().y / 2), -(GetSize().z / 2));
	pVtx[3].pos = D3DXVECTOR3(+(GetSize().x / 2), -(GetSize().y / 2), -(GetSize().z / 2));

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();

	// �o�b�t�@�̐ݒ�
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	//�I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	// �A�j���[�V�����̐ݒ肪���ꂽ�Ƃ�
	if (m_nPatternAnim != 0)
	{
		// �A�j���[�V�������X�V����
		UpdateAnimation();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�̃}�g���N�X

	// �F�̐ݒ�
	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = GetColor();
	material.Diffuse = GetColor();
	material.Ambient.a =  GetColor().a - m_fAlphaNum;
	material.Diffuse.a =  GetColor().a - m_fAlphaNum;

	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// �A���t�@�e�X�g��L�͉�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// �A���t�@�e�X�g���L���Ȃ�
	if (m_bAlpha == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0xC0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	else
	{
		// �A���t�@�e�X�g��l�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaNum);
	}

	// ���Z����
	if (m_bBlend == true)
	{
		// ���Z�������s��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[
	}

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bInverse == false)
	{
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	else
	{
		// ��]�̋t�s��̐���
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&m_mtxWorld, NULL,
			&mtxRot);

		m_mtxWorld._41 = 0;
		m_mtxWorld._42 = 0;
		m_mtxWorld._43 = 0;
	}

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// �A���t�@�e�X�g���L���łȂ�������
	if (m_bAlpha != true)
	{
		// �A���t�@�e�X�g��l�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	// ���Z�������L���Ȃ�
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[
	}

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// �ړ���
//=============================================================================
void CScene3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// ���W�ݒ�(���W�X�V�p)
//=============================================================================
void CScene3D::SetPosision(D3DXVECTOR3 pos)
{
	// ���W�ݒ�
	SetPos(pos);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[1].pos = D3DXVECTOR3(+(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(GetSize().x / 2), -(GetSize().y / 2), -(GetSize().z / 2));
	pVtx[3].pos = D3DXVECTOR3(+(GetSize().x / 2), -(GetSize().y / 2), - (GetSize().z / 2));

	// ���_�o�b�t�@���A�����b�N����
	GetVtxBuff()->Unlock();
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
		pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	}

	//���_�o�b�t�@�̃A�����b�N
	GetVtxBuff()->Unlock();
}

//=============================================
// �A�j���[�V�������擾
//=============================================
void CScene3D::InitAnimation(D3DXVECTOR2 TexInfo, int nLoop)
{
	// �l�̑��
	m_nPatternAnim = (int)TexInfo.x;
	m_nCounterAnim = (int)TexInfo.y;
	m_nLoop = nLoop;

	// ���_����ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	GetVtxBuff()->Unlock();
}

//=============================================
// �A�j���[�V�����X�V�֐�
//=============================================
void CScene3D::UpdateAnimation(void)
{
	// �����̃A�j���[�V�����J�E���g��i�߂āA�p�^�[����؂�ւ���
	m_nCountAnim++;

	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCountAnim >= m_nCounterAnim)	// �����̑���
	{
		// �A�j���[�V�����̃J�E���g��0�ɂ���
		m_nCountAnim = 0;

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_nCountAnimPattern++;
	}

	// �A�j���[�V�������I�������
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// ���l��߂��Ă���
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// �I������
			Uninit();
		}
	}
	else
	{
		// ���_����ݒ�
		VERTEX_3D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		GetVtxBuff()->Unlock();
	}
}

//======================================================
// �g��֐�
//======================================================
void CScene3D::ScaleUp(float fScaleUp)
{
	m_fScaleNum += fScaleUp;

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(GetSize().x * m_fScaleNum), +(GetSize().y * m_fScaleNum), +(GetSize().z * m_fScaleNum));
	pVtx[1].pos = D3DXVECTOR3(+(GetSize().x * m_fScaleNum), +(GetSize().y * m_fScaleNum), +(GetSize().z * m_fScaleNum));
	pVtx[2].pos = D3DXVECTOR3(-(GetSize().x * m_fScaleNum), -(GetSize().y * m_fScaleNum), -(GetSize().z * m_fScaleNum));
	pVtx[3].pos = D3DXVECTOR3(+(GetSize().x * m_fScaleNum), -(GetSize().y * m_fScaleNum), -(GetSize().z * m_fScaleNum));

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}

//=============================================================================
// �����x�̌��Z
//=============================================================================
void CScene3D::SubAlpha(float fAlphaNum)
{
	m_fAlphaNum += fAlphaNum;

	VERTEX_3D*pVtx;	//���_���ւ̃|�C���^

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
		pVtx[nCount].col = D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b, GetColor().a - m_fAlphaNum);
	}

	//���_�f�[�^���A�����b�N
	GetVtxBuff()->Unlock();
}

//=============================================================================
// ���C�t�̐ݒ�
//=============================================================================
void CScene3D::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// ����
//=============================================================================
void CScene3D::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

//=============================================================================
// �A���t�@�e�X�g�̒l
//=============================================================================
void CScene3D::SetAlphaNum(int nAlphaNum)
{
	m_nAlphaNum = nAlphaNum;
}

//=============================================================================
// ���Z�����̐ݒ�
//=============================================================================
void CScene3D::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

//=============================================================================
// �t�s��̐ݒ�
//=============================================================================
void CScene3D::SetInverse(bool bInverse)
{
	m_bInverse = bInverse;
}