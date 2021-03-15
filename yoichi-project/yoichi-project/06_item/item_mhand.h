#ifndef _ITEM_MHAND_H_
#define _ITEM_MHAND_H_
//=============================================================================
//
// �A�C�e��M�n���h�N���X�w�b�_�[	[item_mhand.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item.h"

//=============================================================================
// �A�C�e�����H���N���X
//=============================================================================
class CItemMhand : public CItem
{
public:
	CItemMhand(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemMhand();									// �f�X�g���N�^

	HRESULT Init(void);								// ����������
	void Update(void);								// �X�V����

	void SetItem(void);									// �A�C�e���̌��ʐݒ�
	void UndoItem(void);								// �A�C�e���̌��ʂ�߂�

	static CItemMhand *Create(const int nNumber);		// �C���X�^���X����

private:
	int m_nCounter;			// �t���[���J�E���^�[
	float m_fPlayerRadius;	// �v���C���[�̔��a�ێ�
};

#endif