#ifndef _EFFECT_3D_H_
#define _EFFECT_3D_H_
//=====================================================
//
// 3D�G�t�F�N�g�w�b�_�[ [effect_3d.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "scene3D.h"
#include "effect_factory.h"

//=====================================================
// �}�N����`
//=====================================================

//=====================================================
// �O���錾
//=====================================================
CEffectFactory;

//=====================================================
// 3D�G�t�F�N�g�̃N���X
//=====================================================
class CEffect3D : public CScene3D
{
public:
	CEffect3D(PRIORITY Priority = PRIORITY_PARTICLE);	// �R���X�g���N�^
	~CEffect3D();										// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CEffect3D*Create(D3DXVECTOR3 pos,			// �C���X�^���X����
		CEffectFactory::EFFECT Particle, int nTexInfo);

	// Set�֐�
	void SetLife(int nLife);							// ���C�t�̐ݒ�

	// Get�֐�
	int GetLife(void) { return m_nLife; }				// ���C�t�̏��
private:
	int m_nLife;			// ���C�t
};

#endif