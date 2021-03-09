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
// �O���錾
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CPause;
class CTimer;

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
	static CGame* Create(void);							// �Q�[���������

	// Set�֐�
	static void SetPlayerNum(int nPlayerNum) { m_nPlayerNum = nPlayerNum; }	// �v���C���[�̐��̐ݒ�

	// Get�֐�
	static CCamera *GetCamera(int nCount);										// �J�����̃|�C���^���
	static CLight *GetLight(void);											// ���C�g�̃|�C���^���
	static CPlayer *GetPlayer(int nCount);										// �v���C���[�̃|�C���^���
	static CPause *GetPause(void);											// �|�[�Y��ʂ̃|�C���^���
	static int GetPlayerNum(void) { return m_nPlayerNum; }					// �v���C���[�̐�

    void GameEnd(void) { m_IsGameEnd = true; }
private:	
	static CCamera *m_pCamera[MAX_PLAYER_NUM];	// �J�����̃|�C���^	
	static CLight *m_pLight;					// ���C�g�̃|�C���^
	static CMeshField *m_pMeshField;			// ���b�V���t�B�[���h�̃|�C���^
	static CBg *m_pBg;							// �w�i�̃|�C���^
	static CPlayer *m_pPlayer[MAX_PLAYER_NUM];	// �v���C���[�̃|�C���^
	static CPause *m_pPause;					// �|�[�Y�̃|�C���^
    static CTimer *m_Timer;                     // �^�C�}�[�̃|�C���^

	LPD3DXFONT m_pFont;							// �f�o�b�N�p�t�H���g
	bool m_IsGameEnd;							// �Q�[���̃G���h�t���O
	static int m_nPlayerNum;					// �v���C���[�̐l��
};
#endif