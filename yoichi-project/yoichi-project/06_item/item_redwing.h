#ifndef _ITEM_REDWING_H_
#define _ITEM_REDWING_H_
//=============================================================================
//
// �A�C�e���Ԃ��H���N���X�w�b�_�[	[item_redwing.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item.h"

//=============================================================================
// �A�C�e���Ԃ��H���N���X
//=============================================================================
class CItemRedWing : public CItem
{
public:
	CItemRedWing(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemRedWing();									// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Update(void);		// �X�V����

	void SetItem(void);									// �A�C�e���̌��ʐݒ�
	void UndoItem(void);								// �A�C�e���̌��ʂ�߂�
	static CItemRedWing *Create(const int nNumber);		// �C���X�^���X����

private:
	int m_nCounter;					// �t���[���J�E���^�[
	bool m_bValid[MAX_PLAYER_NUM];	// �A�C�e���̌��ʗL���t���O
};

#endif