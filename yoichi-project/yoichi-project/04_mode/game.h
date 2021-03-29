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
#include "manager.h"
#include "gamemode.h"
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
class CTime_UI;
class CResult;
class CGame_UI;

//***************************************************************************************
// �Q�[���N���X
//***************************************************************************************
class CGame : public ICGameMode
{
public:
	CGame();											// �R���X�g���N�^
	~CGame();											// �f�X�g���N�^

	HRESULT Init();										// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

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

    void GameEnd(void) { m_bGameEnd = true; }  // �Q�[���I��
private:
	static CCamera *m_pCamera[MAX_PLAYER_NUM];	// �J�����̃|�C���^	
	static CLight *m_pLight;					// ���C�g�̃|�C���^
	static CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// �v���C���[�̃|�C���^
	static CItemBoxManager *m_pItemManager;		// �A�C�e���}�l�[�W���̃|�C���^
	static CResult *m_apResult[MAX_PLAYER_NUM];	// ���U���g�̃|�C���^
	CStarManager *m_pStarManager;				// �������N���X�̃|�C���^
	CStageMap *m_pStageMap;						// �}�b�v�̐���
	static CPause *m_pPause;					// �|�[�Y�̃|�C���^
    static CTime_UI *m_pTimeUI;                 // �^�C�}�[�ւ̃|�C���^
    static CGame_UI *m_pGameUI;                 // �Q�[��UI


	LPD3DXFONT m_pFont;							// �f�o�b�N�p�t�H���g
	int m_nTimeCounter;							// �Q�[���̃J�E���^�[
	bool m_bGameEnd;							// �Q�[���̃G���h�t���O
	static int m_nPlayerNum;					// �v���C���[�̐l��

};
#endif