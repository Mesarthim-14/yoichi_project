#ifndef _ITEM_THUNDER_H_
#define _ITEM_THUNDER_H_
//=============================================================================
//
// �A�C�e�����N���X�w�b�_�[	[item_thunder.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item.h"

//=============================================================================
// �A�C�e�����N���X
//=============================================================================
class CItemThunder : public CItem
{
public:
	CItemThunder(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemThunder();									// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Update(void);		// �X�V����

	void SetItem(void);									// �A�C�e���̌��ʐݒ�
	void UndoItem(void);								// �A�C�e���̌��ʂ�߂�
	static CItemThunder *Create(const int nNumber);		// �C���X�^���X����

private:
	int m_nCounter;					// �t���[���J�E���^�[
	bool m_bValid[MAX_PLAYER_NUM];	// �A�C�e���̌��ʗL���t���O
};

#endif