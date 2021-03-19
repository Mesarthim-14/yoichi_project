#ifndef _ITEM_VORTEX_H_
#define _ITEM_VORTEX_H_
//=============================================================================
//
// �A�C�e���Q�N���X�w�b�_�[	[item_vortex.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "item.h"

//=============================================================================
// �A�C�e���Q�N���X
//=============================================================================
class CItemVortex : public CItem
{
public:
	CItemVortex(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemVortex();										// �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Update(void);		// �X�V����

	void SetItem(void);									// �A�C�e���̌��ʐݒ�
	void UndoItem(void);								// �A�C�e���̌��ʂ�߂�
	static CItemVortex *Create(const int nNumber);		// �C���X�^���X����
	void RadiusUp(void);								// ���a�̊g��

private:
	int m_nCounter;			// �t���[���J�E���^�[
	float m_fRadiusNum;		// �v���C���[�̔��a�ێ�
};

#endif