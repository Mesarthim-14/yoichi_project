#ifndef _MAGICHAND_H_
#define _MAGICHAND_H_
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
class CMagichand : public CBillboard
{
public:
	CMagichand(PRIORITY Priority = PRIORITY_PARTICLE);		// �R���X�g���N�^
	~CMagichand();											// �f�X�g���N�^

	HRESULT Init();	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CMagichand*Create(D3DXVECTOR3 Distance, int nTexInfo, int nPlayerNum);	// �C���X�^���X����

private:
	int m_nPlayerNum;		// �Ǐ]������v���C���[�̔ԍ�
	D3DXVECTOR3 m_Distance; // ����
};

#endif