#ifndef _MOTION_H_
#define _MOTION_H_
//=============================================================================
//
// ���[�V�����N���X�w�b�_�[ [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xfile.h"
#include "modelanime.h"

//=============================================================================
// ���[�V�����N���X
//=============================================================================
class CMotion
{
public:
	//=============================================================================
	//�@�e�v�f�̃L�[���
	//=============================================================================
	struct KEY
	{
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	};

	//=============================================================================
	//	�L�[���̍\����
	//=============================================================================
	struct KEY_INFO
	{
		int nFrame;						// �t���[����
		KEY aKey[MAX_MODEL_PARTS];		// �e�p�[�c�̃L�[���
	};

	//=============================================================================
	//�@���[�V�������̍\����
	//=============================================================================
	struct Motion_Info
	{
		bool bLoop;				// ���[�v���邩�ǂ���
		int nNumKey;			// �L�[��
		KEY_INFO aKeyInfo[20];	// �L�[���
	};

	CMotion();		// �R���X�g���N�^
	~CMotion();		// �f�X�g���N�^

	static CMotion *Create(char *pFileName);

	HRESULT Init(void);															// ����������
	void Uninit(void);															// �I������
	void Update(void);															// �X�V����

	void SetMotion(int nMotion, int nMaxParts, CModelAnime **pModelAnime);		// ���[�V�����̐ݒ�
	void UpdateMotion(int nMaxParts, CModelAnime **pModelAnime);				// ���[�V�����̍X�V
	HRESULT ReadMotionFile(char *pFileName);									// ���[�V�����f�[�^��ǂݍ���

	// Get�֐�
	int GetMotionState(void) { return m_nMotionState; }		// ���[�V�������

private:
	// ���[�V�����p�ϐ�
	Motion_Info m_Motion[30];		// ���[�V�������
	KEY_INFO *m_apKeyInfo;			// �L�[���̃|�C���^
	int m_nMotionState;				// ���[�V�����̏��
	int m_nNumKey;					// �L�[�̑���
	int m_nCountMotion;				// ���[�V�����J�E���^�[
	int m_nMotionInterval;			// ���[�V�����̃C���^�[�o��
	int m_nKey;						// ���݃L�[��No
	bool m_bMotionPlaing;			// ���[�V�����̍Đ�

	D3DXVECTOR3 m_diffPos;			// �ύX���W
	D3DXVECTOR3 m_diffRot;			// �ύX�p�x
};

#endif 