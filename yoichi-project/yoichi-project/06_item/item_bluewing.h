#ifndef _ITEM_BLUEWING_H_
#define _ITEM_BLUEWING_H_
//=============================================================================
//
// �A�C�e�����H���N���X�w�b�_�[	[item_bluewing.h]
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
class CItemBlueWing : public CItem
{
public:
	CItemBlueWing(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemBlueWing();									// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Update(void);		// �X�V����

	void SetItem(void);									// �A�C�e���̌��ʐݒ�
	void UndoItem(void);								// �A�C�e���̌��ʂ�߂�
	static CItemBlueWing *Create(const int nNumber);	// �C���X�^���X����

private:
	int m_nCounter;			// �t���[���J�E���^�[
};

#endif