#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�O���錾
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CFade;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CInputJoypad;
class CScene;
class CResourceManager;

//=============================================================================
//�}�l�[�W���[�N���X
//=============================================================================
class CManager
{
public:
	//=========================================================================
	//�񋓌^��`
	//=========================================================================
	typedef enum
	{
		MODE_TYPE_NONE = 0, 
		MODE_TYPE_TITLE,		// �^�C�g�����[�h
		MODE_TYPE_TUTORIAL,		// �`���[�g���A��
		MODE_TYPE_GAME,			// �Q�[�����[�h
		MODE_TYPE_RESULT,		// ���U���g���[�h
		MODE_TYPE_MAX,
	}MODE_TYPE;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	void LoadAll(void);												// �S�Ẵ��[�h����
	void UnLoadAll(void);											// �S�ẴA�����[�h

	// Set�֐�
	static void SetMode(MODE_TYPE mode);							// ���[�h�̐ݒ�
	
	// Get�֐�
	static MODE_TYPE GetMode(void);														// ���[�h�̏��
	static CRenderer *GetRenderer(void);												// �����_���[���
	static CInputKeyboard *GetKeyboard(void);											// �L�[�{�[�h���
	static CFade *GetFade(void);														// �t�F�[�h���
	static CInputJoypad *GetJoypad(void);												// �W���C�p�b�h�R���g���[���̏��
	static CScene *GetScene(void) { return m_pScene; }									// �V�[�����
	static CResourceManager *GetResourceManager (void) { return m_pResourceManager; }	// ���\�[�X�}�l�[�W���̃|�C���^
	static CGame *GetGame(void) { return m_pGame; }										// �Q�[���N���X�̃|�C���^���
private:
	static MODE_TYPE m_mode;						// ���[�h
	static CRenderer *m_pRenderer;					// �����_���[�N���X�̃|�C���^
	static CInputKeyboard *m_pInput;				// �C���v�b�g�N���X�̃|�C���^
	static CFade *m_pFade;							// �t�F�[�h�N���X�̃|�C���^
	static CTitle *m_pTitle;						// �^�C�g���N���X�̃|�C���^
	static CTutorial *m_pTutorial;					// �`���[�g���A���̃|�C���^
	static CGame *m_pGame;							// �Q�[���̃|�C���^
	static CResult *m_pResult;						// ���U���g�̃|�C���^
	static CInputJoypad *m_pJoypad;					// �W���C�p�b�h�R���g���[r�̃|�C���^
	static CScene *m_pScene;						// �V�[���̃|�C���^
	static CResourceManager *m_pResourceManager;	// ���\�[�X�}�l�[�W���̃|�C���^
};

#endif