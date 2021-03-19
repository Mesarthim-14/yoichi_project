#ifndef _ITEM_VBOMBBOX_H_
#define _ITEM_VBOMBBOX_H_
//=============================================================================
//
// �A�C�e���{�b�N�X�N���X�w�b�_�[	[item_bombbox.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "model.h"

//=============================================================================
// �A�C�e���{�b�N�X�N���X
//=============================================================================
class CItemBombBox : public CModel
{
public:
	CItemBombBox(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemBombBox();									// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	void UndoBox(void);									// �{�b�N�X���ʂ̏I��

	void Collision(void);								// �����蔻��̏���

	static CItemBombBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumber);		// �C���X�^���X����

private:
	int m_nPlayerNum;	// �v���C���[�̔ԍ�
	int m_nHitPlayer;	// ���������v���C���[
	int m_nCounter;		// �t���[���J�E���^�[
	bool m_bUse;		// �g�p��
};

#endif