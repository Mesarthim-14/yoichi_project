#ifndef _STAR_FACTORY_H_
#define _STAR_FACTORY_H_
//=============================================================================
//
// ���̐����N���X�w�b�_�[ [star_factory.h]
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
// �X�^�[�����N���X
//=============================================================================
class CStarFactory
{
public:
	// �A�C�e���̎�ނ̗񋓌^
	enum STAR_COLOR
	{
		ITEM_TYPE_NONE = -1,	// �����l
		ITEM_TYPE_BLUE_WING,	// ���H��
		ITEM_TYPE_MAX			// �ő�l
	};

	CStarFactory();													// �R���X�g���N�^
	~CStarFactory();												// �f�X�g���N�^

	void Init(void);												// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void CreateStar(void);											// �A�C�e���N���X�̐���

	static CStarFactory *Create(void);								// �C���X�^���X����
	void SubStarNum(int nCount, CStar::POS_NUMBER posNum);

private:
	std::vector<CStar*> m_pStar;											// �A�C�e���{�b�N�X�̃|�C���^
	bool m_bMapFlag[STAR_CREATE_SIZE][STAR_CREATE_SIZE][STAR_CREATE_SIZE];	// ���W�̃t���O�t���O
};
#endif
