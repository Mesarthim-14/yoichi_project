#ifndef _NUMBER_3D_H_
#define _NUMBER_3D_H_
//=============================================================================
//
// �i���o�[3D�N���X�w�b�_�[ [number_3d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "mesh_3d.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DAMAGE_NUM_SIZE_X		(250.0f)	// ���̃T�C�Y
#define DAMAGE_NUM_SIZE_Y		(150.0f)	// �c�̃T�C�Y
#define DAMAGE_NUM_SIZE_Z		(0.0f)		// ���s�̃T�C�Y

#define DAMAGE_NUM_SIZE			(D3DXVECTOR3(DAMAGE_NUM_SIZE_X, DAMAGE_NUM_SIZE_Y, DAMAGE_NUM_SIZE_Z))

//=============================================================================
// �i���o�[3D�N���X
//=============================================================================
class CNumber3d : public CMesh3d
{
public:
	CNumber3d(PRIORITY Priority = PRIORITY_EFFECT);							// �R���X�g���N�^
	virtual ~CNumber3d();													// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);						// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��
	void Gravity(void);														// �d��

	static CNumber3d *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum);	// �C���X�^���X����

	// Set�֐�
	void SetInverse(bool bInverse) { m_bInverse = bInverse; }				// �t�s��̐ݒ�
	void BindMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }		// �}�g���N�X���
	void RandSetMove(void);													// �ړ��ʂ̐ݒ�

	// Get�֐�
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }						// ���[���h�}�g���b�N�X

private:
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	bool m_bInverse;			// �t�s��
	int m_nNumber;				// �i���o�[�̒l
	int m_nLife;				// �̗�
	int m_nBoundCounter;		// �o�E���h�J�E���g
	D3DXVECTOR3 m_move;			// �ړ�
};

#endif