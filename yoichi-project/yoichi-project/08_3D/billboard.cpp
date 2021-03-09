//=====================================================
//
// �r���{�[�h�N���X [billboard.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// �R���X�g���N�^
//=====================================================
CBillboard::CBillboard(PRIORITY Priority) : CSceneBase(Priority)
{
	m_move = ZeroVector3;			// �ړ���
	m_sizeBase = ZeroVector3;		// �x�[�X�̃T�C�Y
	m_nLife = 0;									// ����
	m_bUse = false;									// �g�p����
	m_nCountAnim = 0;;								// �A�j���[�V�����e�N�X�`��
	m_nCountAnimPattern = 0;						// �A�j���[�V�����̃p�^�[��
	m_nCounterAnim = 0;								// �A�j���[�V�����̃J�E���^�[
	m_nPatternAnim = 0;								// �A�j���[�V�����̃p�^�[����
	m_nLoop = -1;									// ���[�v���邩
	m_nAlphaNum = 0;								// �A���t�@�e�X�g�̒l
	m_bAlpha = false;								// �A���t�@�e�X�g�̃t���O
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// ����������
//=====================================================
HRESULT CBillboard::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	// ���̑��
	SetPos(pos);
	SetSize(size);
	m_sizeBase = size;

	//���_�o�b�t�@�����b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- size.x / 2, + size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ size.x / 2, + size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- size.x / 2, - size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ size.x / 2, - size.y / 2, 0.0f);

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�i0�`255�̐��l�Őݒ�j
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();

	// �o�b�t�@�̎󂯓n��
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CBillboard::Uninit(void)
{	
	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CBillboard::Update(void)
{
	// �ړ��ʉ��Z
	D3DXVECTOR3 pos = GetPos();
	pos += m_move;

	// ���W�̐ݒ�
	SetPos(pos);

	// �A�j���[�V�����̐ݒ肪���ꂽ�Ƃ�
	if (m_nPatternAnim != 0)
	{
		// �A�j���[�V�������X�V����
		UpdateAnimation();
	}

	// �̗͂����炵�Ă���
	m_nLife--;

	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CBillboard::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���Z�������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[

	// �F�̐ݒ�
	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = GetColor();
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// ���̉e���𖳂���
	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	// �A���t�@�e�X�g��L�͉�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// ���Z����
	if (m_bBlend == true)
	{
		// ���Z�������s��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[
	}
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

	//�v�Z�p�̃}�g���N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �T�C�Y�𔽉f
	D3DXMatrixScaling(&mtxScale,
		GetSize().x / m_sizeBase.x,
		GetSize().y / m_sizeBase.y,
		0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�̋t�s��̐���
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL,
		&mtxRot);

	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// �ʒu�𔽉f�A���[���h�}�g���N�X�ݒ�A�|���S���`��
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���N�X�̐ݒ� �������A�����A�ʒu
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, GetTexture());

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`����NULL
	pDevice->SetTexture(0, NULL);

	// �A���t�@�e�X�g���L���łȂ�������
	if (m_bAlpha != true)
	{
		// �A���t�@�e�X�g��l�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	// ���Z�������s������
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[
	}

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	pDevice->SetMaterial(&OldMaterial);					// �}�e���A�������ɖ߂�

	pDevice->LightEnable(0, TRUE);
}

//=============================================
// �A�j���[�V�������擾
//=============================================
void CBillboard::InitAnimation(D3DXVECTOR2 TexInfo, int nLoop)
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
void CBillboard::UpdateAnimation(void)
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

//=====================================================
// �ړ��ʐݒ�
//=====================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=====================================================
// �x�[�X�T�C�Y�ݒ�
//=====================================================
void CBillboard::SetSizeBase(D3DXVECTOR3 sizeBase)
{
	m_sizeBase = sizeBase;
}

//=====================================================
// �̗͂̐ݒ�
//=====================================================
void CBillboard::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=====================================================
// �A���t�@�e�X�g�̐ݒ�
//=====================================================
void CBillboard::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

//=====================================================
// �A���t�@�e�X�g�̒l
//=====================================================
void CBillboard::SetAlphaNum(int nAlphaNum)
{
	m_nAlphaNum = nAlphaNum;
}

//=====================================================
// ���Z����
//=====================================================
void CBillboard::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

//=====================================================
// �ړ��ʏ��
//=====================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_move;
}

//=====================================================
// �̗͂̐ݒ�
//=====================================================
int CBillboard::GetLIfe(void)
{
	return m_nLife;
}