#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// �}�N����`
//***************************************************************************************
#define STAGE_LIMIT_Y		(-2000.0f)

//***************************************************************************************
// �O���錾
//***************************************************************************************
class CCamera;
class CLight;
class CPlayer;
class CPause;
class CItemBoxManager;
class CStarManager;
class CStageMap;

//***************************************************************************************
// �Q�[���N���X
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame(PRIORITY Priority = PRIORITY_0);				// �R���X�g���N�^
	~CGame();											// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	void SetGame(void);									// �Q�[���̐ݒ�

	static CGame* Create(void);							// �Q�[���������

	// Set�֐�
	static void SetPlayerNum(int nPlayerNum) { m_nPlayerNum = nPlayerNum; }	// �v���C���[�̐��̐ݒ�

	// Get�֐�
	static CCamera *GetCamera(int nCount);										// �J�����̃|�C���^���
	static CLight *GetLight(void);												// ���C�g�̃|�C���^���
	static CPlayer *GetPlayer(int nCount);										// �v���C���[�̃|�C���^���
	static CPause *GetPause(void);												// �|�[�Y��ʂ̃|�C���^���
	static int GetPlayerNum(void)					{ return m_nPlayerNum; }	// �v���C���[�̐�
	static CItemBoxManager *GetItemManager(void)	{ return m_pItemManager; }	// ���\�[�X�}�l�[�W���̃|�C���^
	CStageMap *GetStageMap(void)					{ return m_pStageMap; }		// �}�b�v�̏��

private:	
	static CCamera *m_pCamera[MAX_PLAYER_NUM];	// �J�����̃|�C���^	
	static CLight *m_pLight;					// ���C�g�̃|�C���^
	static CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// �v���C���[�̃|�C���^
	static CItemBoxManager *m_pItemManager;		// �A�C�e���}�l�[�W���̃|�C���^
	CStarManager *m_pStarManager;				// �������N���X�̃|�C���^
	CStageMap *m_pStageMap;						// �}�b�v�̐���
	static CPause *m_pPause;					// �|�[�Y�̃|�C���^
	LPD3DXFONT m_pFont;							// �f�o�b�N�p�t�H���g
	int m_nTimeCounter;							// �Q�[���̃J�E���^�[
	bool m_bGameEnd;							// �Q�[���̃G���h�t���O
	static int m_nPlayerNum;					// �v���C���[�̐l��
};
#endif