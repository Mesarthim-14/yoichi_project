#ifndef _TITLET_H_
#define _TITLET_H_
//=============================================================================
//
// �^�C�g������ [title.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gamemode.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLE_UI_SIZE			(700.0f)	// UI�T�C�Y
#define TITLE_UI_POS_X			(640.0f)	// UI��X���W
#define TITLE_UI_POS_Y			(360.0f)	// UI��Y���W

#define TITLE_SIZE_X			(500.0f)	// �^�C�g����X�T�C�Y
#define TITLE_SIZE_Y			(200.0f)	// �^�C�g����Y�T�C�Y
#define TITLE_POS_X				(640.0f)	// �^�C�g����X���W
#define TITLE_POS_Y				(350.0f)	// �^�C�g����Y���W

#define TITLE_PRESS_SIZE_X		(400.0f)	// PRESS�T�C�Y
#define TITLE_PRESS_SIZE_Y		(30.0f)		// PRESS�T�C�Y
#define TITLE_PRESS_POS_X		(640.0f)	// PRESS��X���W
#define TITLE_PRESS_POS_Y		(260.0f)	// PRESS��Y���W

#define MAX_TITLE_UI_NUM		(3)			// UI�̐�

//=============================================================================
//�O���錾
//=============================================================================
class CScene2D;
class CPlayerSelectButton;
//=============================================================================
//���U���g�N���X
//=============================================================================
class CTitle : public ICGameMode
{
public:
	CTitle();					// �R���X�g���N�^
	~CTitle();												// �f�X�g���N�^

	static CTitle* Create(void);							// �C���X�^���X����

	HRESULT Init(void);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	void SetPlayerNum(void);								// �v���C���[���̐ݒ�
private:

	void SelectButton(void);

	CScene2D* m_pScene2D;									// �V�[��2D�̃|�C���^
	bool m_bDisplayButton;
	CPlayerSelectButton* m_apPlayerSelectButton[MAX_PLAYER_NUM - MIN_PLAYER_NUM + 1];
	int m_nSelectButton;
};
#endif