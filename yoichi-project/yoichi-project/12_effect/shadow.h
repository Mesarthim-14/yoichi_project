#ifndef _SHADOW_H_
#define _SHADOW_H_
//=====================================================
//
// �V���h�E�N���X�w�b�_�[ [shadow.h]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"

//=====================================================
// �p�[�e�B�N���N���X
//=====================================================
class CShadow : public CBillboard
{
public:
	CShadow(PRIORITY Priority = PRIORITY_PARTICLE);		// �R���X�g���N�^
	~CShadow();											// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	static CShadow*Create(int nTexInfo, int nPlayerNum);	// �C���X�^���X����

private:
	int m_nPlayerNum;		// �Ǐ]������v���C���[�̔ԍ�
};

#endif