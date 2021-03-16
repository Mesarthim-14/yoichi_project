#ifndef _STAR_H_
#define _STAR_H_
//=====================================================
//
// ���N���X�w�b�_�[ [star.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"

//=====================================================
// �O���錾
//=====================================================
class CStarManager;

//=====================================================
// �X�^�[�N���X
//=====================================================
class CStar : public CBillboard
{
public:
	// ���̐F
	enum STAR_COLOR_TYPE
	{
		STAR_COLOR_TYPE_NONE = -1,	// �����l
		STAR_COLOR_TYPE_RED,		// ��
		STAR_COLOR_TYPE_BLUE,		// ��
		STAR_COLOR_TYPE_YELLOW,		// ��
		STAR_COLOR_TYPE_GREEN,		// ��
		STAR_COLOR_TYPE_MAX,
	};

	// ���W�ԍ��ێ�
	struct POS_NUMBER
	{
		int nNumX;
		int nNumY;
		int nNumZ;
	};

	CStar(PRIORITY Priority = PRIORITY_PARTICLE);				// �R���X�g���N�^
	~CStar();													// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos);								// ����������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	bool Collision(void);										// �����蔻��

	static CStar *Create(D3DXVECTOR3 pos, POS_NUMBER posNum);				// ���̐���

	void SetColorType(void);	// �F�̎�ސݒ�

	POS_NUMBER GetPosNumber(void) { return m_PosNumber; }		// ���W�ԍ��̏��

private:
	POS_NUMBER m_PosNumber;										// ���W�ԍ�
	STAR_COLOR_TYPE m_ColorType;					// �F�̐ݒ�
};

#endif