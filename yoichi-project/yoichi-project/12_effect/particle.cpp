//=====================================================
//
// �p�[�e�B�N���N���X [particle.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "particle.h"
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
CEffect::CEffect(PRIORITY Priority) : CBillboard(Priority)
{
	
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CEffect::~CEffect()
{

}

//=====================================================
// �C���X�^���X����
//=====================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, CEffectFactory::EFFECT Particle,
	 int nTexInfo)
{
	// �������m��
	CEffect *pEffect = new CEffect;

	if (pEffect != NULL)
	{
		// �����̐ݒ�
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x),
			(float)(rand() % (int)Particle.Distance.y + rand() % (int)Particle.Distance.y),
			(float)(rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z));

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y,
			pos.z + Distance.z);

		pEffect->SetPos(TargetPos);
		pEffect->SetSize(Particle.size);
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
			pEffect->BindTexture(pTexture->GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
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
		pEffect->SetAlphaNum(Particle.nAlphaNum);	// �A���t�@�̒l�̐ݒ�
		pEffect->SetBlend(Particle.bBlend);			// ���Z�����̐ݒ�
	}

	return pEffect;
}

//=====================================================
// ����������
//=====================================================
HRESULT CEffect::Init(void)
{
	// ����������
	CBillboard::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CEffect::Uninit(void)
{
	// �I������
	CBillboard::Uninit();

	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CEffect::Update(void)
{
	// �X�V����
	CBillboard::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CEffect::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}