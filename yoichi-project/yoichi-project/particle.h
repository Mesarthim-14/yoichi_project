#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//=====================================================
//
// �p�[�e�B�N���w�b�_�[ [particle.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"
#include "effect_factory.h"

//=====================================================
// �}�N����`
//=====================================================

//=====================================================
// �O���錾
//=====================================================
CEffectFactory;

//=====================================================
// �p�[�e�B�N���N���X
//=====================================================
class CEffect : public CBillboard
{
public:
	CEffect(PRIORITY Priority = PRIORITY_PARTICLE);		// �R���X�g���N�^
	~CEffect();											// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CEffect*Create(D3DXVECTOR3 pos,				// �C���X�^���X����
		CEffectFactory::EFFECT Particle,
		 int nTexInfo);

private:
};

#endif