#ifndef _BARRIEREFFECT_H_
#define _BARRIEREFFECT_H_
//=============================================================================
//
// �o���A�G�t�F�N�g�N���X�w�b�_�[ [barrier_effect.h]
// Author : Ito Yogo
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define BARRIEREFFECT_MAX_SIZE_X	(300.0f)	// X�̃T�C�Y�̍ő�l
#define BARRIEREFFECT_MAX_SIZE_Y	(300.0f)	// Y�̃T�C�Y�̍ő�l
#define BARRIEREFFECT_MAX_SIZE_Z	(300.0f)	// Z�̃T�C�Y�̍ő�l
#define BARRIEREFFECT_MAX_SIZE		(D3DXVECTOR3(BARRIEREFFECT_MAX_SIZE_X, BARRIEREFFECT_MAX_SIZE_Y, BARRIEREFFECT_MAX_SIZE_Z))	// �T�C�Y�̍ő�l
#define BARRIEREFFECT_LIFE			(180)	// ���C�t

//=============================================================================
// �w�i�N���X
//=============================================================================
class CBARRIEREFFECT: public CModel
{
public:
	CBARRIEREFFECT();		// �R���X�g���N�^
	~CBARRIEREFFECT();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	static CBARRIEREFFECT *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fAngle);	// �C���X�^���X����

private:
	D3DXVECTOR3 m_RotQuantity;	// ��]��
	D3DXVECTOR3 m_Scale;		// �g�嗦
};

#endif
