#ifndef _ITEM_BARRIER_H_
#define _ITEM_BARRIER_H_
//=============================================================================
//
// �A�C�e���o���A�N���X�w�b�_�[	[item_barrier.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item.h"

//=============================================================================
// �A�C�e���o���A�N���X
//=============================================================================
class CItemBarrier : public CItem
{
public:
	CItemBarrier(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemBarrier();									// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Update(void);		// �X�V����

	void SetItem(void);									// �A�C�e���̌��ʐݒ�
	void UndoItem(void);								// �A�C�e���̌��ʂ�߂�
	static CItemBarrier *Create(const int nNumber);		// �C���X�^���X����

private:
	int m_nCounter;			// �t���[���J�E���^�[
};

#endif