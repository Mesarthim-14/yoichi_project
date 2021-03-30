#ifndef _WIND_EFFECT_H_
#define _WIND_EFFECT_H_
//=====================================================
//
// �}�W�b�N�n���h�N���X�w�b�_�[ [magichand.h]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"

//=====================================================
// �}�N����`
//=====================================================
#define MAGICHAND_DISTANCE	(D3DXVECTOR3(150.0f ,0.0f, 0.0f))	// �v���C���[�Ƃ̋���

//=====================================================
// �p�[�e�B�N���N���X
//=====================================================
class CWindEffect : public CBillboard
{
public:
	CWindEffect(PRIORITY Priority = PRIORITY_PARTICLE);		// �R���X�g���N�^
	~CWindEffect();											// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CWindEffect*Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Distance, int nTexInfo);	// �C���X�^���X����

private:
};

#endif