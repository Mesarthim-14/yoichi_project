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

#define ITEM_UI_POS_PLAYER_1		{SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4-130.0f,0.0f}      // UI�̈ʒu(1P)
#define ITEM_UI_POS_PLAYER_2		{SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4-130.0f,0.0f}      // UI�̈ʒu(2P)
#define ITEM_UI_POS_PLAYER_3		{SCREEN_WIDTH/4-150.0f,SCREEN_HEIGHT/4+(SCREEN_HEIGHT/2)-130.0f,0.0f}      // UI�̈ʒu(3P)
#define ITEM_UI_POS_PLAYER_4		{SCREEN_WIDTH/4+(SCREEN_WIDTH/2)+100.0f,SCREEN_HEIGHT/4-(SCREEN_HEIGHT/2)+130.0f,0.0f}      // UI�̈ʒu(4P)

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

	virtual HRESULT Init(void);	// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��

	virtual void SetItem(void) = 0;								// �A�C�e���̐ݒ�
	virtual void UndoItem(void) = 0;							// �A�C�e���̌��ʂ�߂�

	void UiUninit(void);										// UI�̏I������

    D3DXVECTOR3 SetPosition(int nPlayer);                                   // UI�̈ʒu�̐ݒ�

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
    static const D3DXVECTOR3 m_position[MAX_PLAYER_NUM];// �A�C�e����UI�̈ʒu

	CUi *m_pUi;				// UI�̃|�C���^
	int m_nPlayerNumber;	// �u���C���[�̔ԍ�
	bool m_bEnd;			// �A�C�e���̍폜�t���O
	bool m_bUse;
};

#endif