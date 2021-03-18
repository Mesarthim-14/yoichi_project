#ifndef _ITEM_H_
#define _ITEM_H_
//=============================================================================
//
// �A�C�e���N���X�w�b�_�[	[item.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ITEM_UI_POS_X	(100.0f)			// �A�C�e���̍��W
#define ITEM_UI_POS_Y	(100.0f)			// �A�C�e���̍��W
#define ITEM_UI_POS_Z	(0.0f)				// �A�C�e���̍��W
#define ITEM_UI_SIZE_X	(70.0f)				// �A�C�e���̃T�C�Y
#define ITEM_UI_SIZE_Y	(70.0f)				// �A�C�e���̃T�C�Y
#define ITEM_UI_SIZE_Z	(0.0f)				// �A�C�e���̃T�C�Y

#define ITEM_UI_POS		(D3DXVECTOR3(ITEM_UI_POS_X, ITEM_UI_POS_Y, ITEM_UI_POS_Z))      // UI�̈ʒu

#define ITEM_UI_SIZE	(D3DXVECTOR3(ITEM_UI_SIZE_X, ITEM_UI_SIZE_Y, ITEM_UI_SIZE_Z))   // UI�̑傫��

//=============================================================================
// �O���錾
//=============================================================================
class CUi;

//=============================================================================
// �A�C�e���{�b�N�X�N���X
//=============================================================================
class CItem : public CScene
{
public:
	CItem(PRIORITY Priority = PRIORITY_1);				// �R���X�g���N�^
	~CItem();											// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��

	virtual void SetItem(void) = 0;								// �A�C�e���̐ݒ�
	virtual void UndoItem(void) = 0;							// �A�C�e���̌��ʂ�߂�

	void UiUninit(void);											// UI�̏I������

	// Set�֐�
	void SetUi(CUi *pUi)		{ m_pUi = pUi; }							// Ui�̐ݒ�
	void SetNumber(int nNumber)	{ m_nPlayerNumber = nNumber; }				// �v���C���[�̔ԍ��ݒ�
	void SetEnd(bool bEnd)		{ m_bEnd = bEnd; }							// �G���h�t���O�̐ݒ�
	void SetUse(bool bUse)		{ m_bUse = bUse; }							// �g�p�t���O

	// Get�֐�
	CUi *GetUi(void)		{ return m_pUi; }				// UI�̃|�C���^
	int GetPlayerNum(void)	{ return m_nPlayerNumber; }		// �v���C���[�̔ԍ�
	bool GetEnd(void)		{ return m_bEnd; }				// �폜�t���O
	bool GetUse(void)		{ return m_bUse; }				// �g�p�t���O

private:
	CUi *m_pUi;				// UI�̃|�C���^
	int m_nPlayerNumber;	// �u���C���[�̔ԍ�
	bool m_bEnd;			// �A�C�e���̍폜�t���O
	bool m_bUse;
};

#endif