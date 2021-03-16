#ifndef _ITEMBOX_H_
#define _ITEMBOX_H_
//=============================================================================
//
// �A�C�e���{�b�N�X�N���X�w�b�_�[	[itembox.h]
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
class CItemBox : public CModel
{
public:

	enum ITEM_TYPE
	{
		ITEM_TYPE_NONE = -1,	// �����l
		ITEM_TYPE_BLUE_WING,	// ���H��
		ITEM_TYPE_RED_WING,		// �Ԃ��H��
		ITEM_TYPE_BOMB,			// �{��
		ITEM_TYPE_BARRIER,		// �o���A
		ITEM_TYPE_THUNDER,		// �T���_�[
		ITEM_TYPE_VORTEX,		// �Q
		ITEM_TYPE_MHAND,		// M�n���h
		ITEM_TYPE_MAX			// �ő�l
	};

	CItemBox(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CItemBox();									// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��

	void Collision(void);											// �����蔻��̏���
	void ItemCreate(int nCount);											// �A�C�e���̐���

	static CItemBox *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �C���X�^���X����
private:
	bool m_bDraw;			// �`��̃t���O
	int m_nDrawCount;		// �`��̂��߂̃t���[���J�E���^
};

#endif