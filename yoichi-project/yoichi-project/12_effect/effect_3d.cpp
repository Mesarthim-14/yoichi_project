//=====================================================
//
// 3D�G�t�F�N�g�N���X [effect_3d.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "effect_3d.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"

//=====================================================
// �}�N����`
//=====================================================
#define DEFAULT_POS_Y		(200.0f)		// ���E�̍����̕W��

//=====================================================
// �R���X�g���N�^
//=====================================================
CEffect3D::CEffect3D(PRIORITY Priority) : CScene3D(Priority)
{
	m_nLife = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEffect3D::~CEffect3D()
{

}

//=====================================================
// �C���X�^���X����
//=====================================================
CEffect3D * CEffect3D::Create(D3DXVECTOR3 pos, CEffectFactory::EFFECT Particle,
	int nTexInfo)
{
	// �������m��
	CEffect3D *pEffect = new CEffect3D;

	// nullchack
	if (pEffect != NULL)
	{
		// �����̐ݒ�
		D3DXVECTOR3 Range;
		Range = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Range.x + rand() % (int)Particle.Range.x - rand() % (int)Particle.Range.x - rand() % (int)Particle.Range.x),
			(float)(rand() % (int)Particle.Range.y + rand() % (int)Particle.Range.y),
			(float)(rand() % (int)Particle.Range.z + rand() % (int)Particle.Range.z - rand() % (int)Particle.Range.z - rand() % (int)Particle.Range.z));

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Range.x,
			pos.y + Range.y,
			pos.z + Range.z);

		// ����������
		pEffect->Init();

		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// �A�j���[�V�������
		if (Particle.bAnimation == false)
		{
			// �e�N�X�`���ݒ�
			pEffect->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));
		}
		else
		{
			// �A�j���[�V�����e�N�X�`���ݒ�
			pEffect->BindTexture(pTexture-> GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));

			// �A�j���[�V�������ݒ�
			pEffect->InitAnimation(
				pTexture->GetSparateTexInfo((CTexture::SEPARATE_TEX_TYPE)nTexInfo),
				pTexture->GetSparateTexLoop((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
		}

		// �ړ��ʂ����ȏ�Ȃ�
		if (Particle.move.x >= 1.0f &&
			Particle.move.y >= 1.0f &&
			Particle.move.z >= 1.0f)
		{
			// �ړ��ʐݒ�
			D3DXVECTOR3 move;
			switch (Particle.bGravity)
			{
				// �d�͖���
			case false:
				// �ړ���
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;

				// �d�͂���
			case true:
				// �ړ���
				move =
					D3DXVECTOR3(
					(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
						(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
						(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
				break;
			}

			// �ړ���
			pEffect->SetMove(move);
		}
		else
		{
			// �ړ���
			pEffect->SetMove(Particle.move);
		}

		pEffect->SetColor(Particle.color);			// �F�̐ݒ�
		pEffect->SetLife(Particle.nLife);			// �̗͂̐ݒ�
		pEffect->SetAlpha(Particle.bAlpha);			// �A���t�@�e�X�g�̐ݒ�
		pEffect->SetAlphaNum(Particle.nAlphaNum);	// �A���t�@�e�X�g�̒l��ݒ�
		pEffect->SetBlend(Particle.bBlend);			// ���Z�����̐ݒ�
	}

	return pEffect;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEffect3D::Init(void)
{
	// ����������
	CScene3D::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEffect3D::Uninit(void)
{
	// �I������
	CScene3D::Uninit();

	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CEffect3D::Update(void)
{
	// �����̌��Z
	m_nLife--;

	// �X�V����
	CScene3D::Update();

	// ���C�t�̐ݒ�
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
	}
}

//=====================================================
// �`�揈��
//=====================================================
void CEffect3D::Draw(void)
{
	// �`�揈��
	CScene3D::Draw();
}

//=====================================================
// ���C�t�̐ݒ�
//=====================================================
void CEffect3D::SetLife(int nLife)
{
	m_nLife = nLife;
}