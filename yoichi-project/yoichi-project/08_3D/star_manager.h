#ifndef _STAR_FACTORY_H_
#define _STAR_FACTORY_H_
//=============================================================================
//
// ���̐����N���X�w�b�_�[ [star_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "star.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define STAR_CREATE_SIZE		(8)		// �X�^�[�z�u�̃T�C�Y

//=============================================================================
// �O���錾
//=============================================================================
class CStar;

//=============================================================================
// �X�^�[�Ǘ��N���X
//=============================================================================
class CStarManager
{
public:
	CStarManager();																	// �R���X�g���N�^
	~CStarManager();																// �f�X�g���N�^

	void Init(void);																// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void CreateStar(void);															// �A�C�e���N���X�̐���

	CStar::STAR_COLOR_TYPE SetColorType(void);										// �F�̐ݒ�
	void SetGameColor(void);														// �Q�[���̐F�̕ύX
	static CStarManager *Create(void);												// �C���X�^���X����
	void SubStarNum(int nCount, CStar::POS_NUMBER posNum);							// ���̑��������Z
	static CStar::STAR_COLOR_TYPE GetGameStarColor(void) { return m_GameColor; }	// �F�̏��

private:
	std::vector<CStar*> m_pStar;													// �A�C�e���{�b�N�X�̃|�C���^
	bool m_bMapFlag[STAR_CREATE_SIZE][STAR_CREATE_SIZE][STAR_CREATE_SIZE];			// ���W�̃t���O
	int m_nCounter;																	// �J�E���^�[

	static CStar::STAR_COLOR_TYPE m_GameColor;										// �Q�[���̐F

};
#endif
