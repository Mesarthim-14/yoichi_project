#ifndef _ITEM_MANAGER_H_
#define _ITEM_MANAGER_H_
//=============================================================================
//
// �A�C�e���Ǘ��N���X�w�b�_�[ [item_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CItemBox;

//=============================================================================
// �G�t�F�N�g����
//=============================================================================
class CItemBoxManager
{
public:
	// �A�C�e���̎�ނ̗񋓌^
	enum ITEM_TYPE
	{
		ITEM_TYPE_NONE = -1,	// �����l
		ITEM_TYPE_BLUE_WING,	// ���H��
		ITEM_TYPE_MAX			// �ő�l
	};

	~CItemBoxManager();								// �f�X�g���N�^

	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void CreateItemBox(void);						// �A�C�e���{�b�N�X�N���X�̐���
	void CreateItem(void);							// �A�C�e���N���X�̐���
	static CItemBoxManager *GetInstance(void);		// �C���X�^���X�擾�֐�

private:
	CItemBoxManager();								// �R���X�g���N�^
	static CItemBoxManager *m_pItemManager;			// ���g�̃N���X�̃|�C���^
	std::vector<CItemBox*> m_pItemBox;				// �A�C�e���{�b�N�X�̃|�C���^
};
#endif
