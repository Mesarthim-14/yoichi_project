#ifndef _BARRIER_H_
#define _BARRIER_H_
//=============================================================================
//
// �o���A�N���X�w�b�_�[ [barrier.h]
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
#define BARRIER_MAX_SIZE_X	(500.0f)	// X�̃T�C�Y�̍ő�l
#define BARRIER_MAX_SIZE_Y	(500.0f)	// Y�̃T�C�Y�̍ő�l
#define BARRIER_MAX_SIZE_Z	(500.0f)	// Z�̃T�C�Y�̍ő�l
#define BARRIER_MAX_SIZE	(D3DXVECTOR3(BARRIER_MAX_SIZE_X, BARRIER_MAX_SIZE_Y, BARRIER_MAX_SIZE_Z))	// �T�C�Y�̍ő�l
#define BARRIER_LIFE		(300)	// ���C�t

//=============================================================================
// �w�i�N���X
//=============================================================================
class CBARRIER : public CModel
{
public:
	CBARRIER();		// �R���X�g���N�^
	~CBARRIER();	// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	static CBARRIER *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum);	// �C���X�^���X����

private:
	D3DXVECTOR3 m_RotQuantity;	// ��]��
	D3DXVECTOR3 m_Scale;		// �g�嗦
	int m_nPlayerNum;			// �v���C���[�̔ԍ�
};

#endif
