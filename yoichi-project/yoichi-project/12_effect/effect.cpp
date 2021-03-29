//=====================================================
//
// �p�[�e�B�N���N���X [particle.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "effect.h"
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
		// �͈͂̐ݒ�
		D3DXVECTOR3 Range = D3DXVECTOR3(
			(Particle.Range.x),
			(Particle.Range.y),
			(Particle.Range.z));

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			(float)(rand() % (int)(Range.x)) + pos.x - (Range.x / 2),
			(float)(rand() % (int)(Range.y)) + pos.y - (Range.y / 2),
			(float)(rand() % (int)(Range.z)) + pos.z - (Range.z / 2));

		pEffect->SetPos(TargetPos);
		pEffect->SetSize(Particle.size);

		// ����������
		pEffect->Init();
		pEffect->SetPos(TargetPos);		// ��]�̐ݒ�
		pEffect->SetSizeBase(Particle.size);					// �F�̐ݒ�

		CTexture *pTexture = GET_TEXTURE_PTR;

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
		if (Particle.move.x >= 1.0f || Particle.move.x <= -1.0f &&
			Particle.move.y >= 1.0f || Particle.move.y <= -1.0f &&
			Particle.move.z >= 1.0f || Particle.move.z <= -1.0f)
		{
			// �ړ��ʐݒ�
			D3DXVECTOR3 move;
			switch (Particle.movetype)
			{
				// ���S�����_��
			case CEffectFactory::MOVE_TYPE_ALLRANDOM:
				switch (Particle.bGravity)
				{
					// �d�͖���
				case false:
					// �ړ���
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							(float)(rand() % (int)Particle.move.y - ((int)Particle.move.y / 2)),
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;

					// �d�͂���
				case true:
					// �ړ���
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;
				}
				break;

				// �c�Ɖ��̃����_��
			case CEffectFactory::MOVE_TYPE_XZRANDOM:
				switch (Particle.bGravity)
				{
					// �d�͖���
				case false:
					// �ړ���
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							Particle.move.y,
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;

					// �d�͂���
				case true:
					// �ړ���
					move =
						D3DXVECTOR3(
						(float)(rand() % (int)Particle.move.x - ((int)Particle.move.x / 2)),
							Particle.move.y,
							(float)(rand() % (int)Particle.move.z - ((int)Particle.move.z / 2)));
					break;
				}
				break;

			default:
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

		pEffect->SetRot(D3DXToRadian(Particle.rot));		// ��]�̐ݒ�
		pEffect->SetColor(Particle.color);					// �F�̐ݒ�
		pEffect->SetLife(Particle.nLife);					// �̗͂̐ݒ�
		pEffect->SetAlpha(Particle.bAlpha);					// �A���t�@�e�X�g�̐ݒ�
		pEffect->SetAlphaNum(Particle.nAlphaNum);			// �A���t�@�̒l�̐ݒ�
		pEffect->SetBlend(Particle.bBlend);					// ���Z�����̐ݒ�
		pEffect->SetGravity(Particle.GravityNum);			// �d�͂̐ݒ�
		pEffect->SetTransparency(Particle.fTransparency);	// �����x�����炷�ʂ̐ݒ�
		pEffect->SetScale(Particle.Scale);					// �g�嗦�̐ݒ�
		pEffect->SetUseZBuf(Particle.bUseZbuf);				// Z�o�b�t�@�̐ݒ�
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