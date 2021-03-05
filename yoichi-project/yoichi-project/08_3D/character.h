#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// �L�����N�^�[����  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CHARACTER_PARTS (22)	// �L�����N�^�[�̃p�[�c��
#define MAX_KEYFRAME		(10)	// �L�[�t���[���̍ő吔

//=============================================================================
//�@���f���t�@�C�����̍\����
//=============================================================================
typedef struct
{
	char xFileName[1024];	// �t�@�C���l�[��
	D3DXVECTOR3 offsetPos;	// �ʒu�̃I�t�Z�b�g���
	D3DXVECTOR3 offsetRot;	// �����̃I�t�Z�b�g���
	int nParent;			// �e���
}MODELFILE;

//=============================================================================
//�@�e�v�f�̃L�[���
//=============================================================================
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//=============================================================================
//	�L�[���̍\����
//=============================================================================
typedef struct
{
	int nFrame;						// �t���[����
	KEY aKey[MAX_CHARACTER_PARTS];	// �e�p�[�c�̃L�[���
}KEY_INFO;

//=============================================================================
//�@���[�V�������̍\����
//=============================================================================
typedef struct
{
	bool bLoop;				// ���[�v���邩�ǂ���
	int nNumKey;			// �L�[��
	KEY_INFO aKeyInfo[20];	// �L�[���
}Motion_Info;

//=============================================================================
// �O���錾
//=============================================================================
class CLifeBar;
class CLifeFrame;

//=============================================================================
// �L�����N�^�[�̃N���X
//=============================================================================
class CCharacter : public CScene
{
public:
	typedef enum
	{
		STATE_NONE = 0,		// �����l
		STATE_APPEAR,		// �o��
		STATE_NO_ACTIVE,	// ��퓬���
		STATE_NORMAL,		// �ʏ���
		STATE_DAMAGE,		// �_���[�W���
		STATE_MAX,			// �ő�l
	}STATE;

	typedef enum
	{
		CHARACTER_TYPE_NONE = 0,	// �����l
		CHARACTER_TYPE_PLAYER,		// �v���C���[
		CHARACTER_TYPE_ENEMY,		// �G�l�~�[
		CHARACTER_TYPE_MAX,			// �ő吔
	}CHARACTER_TYPE;

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	virtual ~CCharacter();											// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	virtual void Uninit();											// �I������
	virtual void Update();											// �X�V����
	virtual void Draw();											// �`�揈��

	virtual void UpdateMotion(void);								// ���[�V�����̍X�V�̏������z�֐�
	bool Gravity(void);												// �n�ʂ̐���
	HRESULT ReadFile(void);											// �t�@�C���̓ǂݍ���
	void BodyCollision(void);										// �����蔻��

	// �������z�֐�
	virtual void UpdateState(void) = 0;								// �L�����N�^�[���
	virtual void UpdateMotionState(void) = 0;						// ���[�V�����̏��
	virtual void Death(void) = 0;									// ���񂾂Ƃ��̏���

	// Set�֐�
	void SetCharaModel(char *xfilename, int nPart, int nMotion);	// ���f�����ǂݍ���
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 posOld);								// ���W�̐ݒ�
	void SetMove(D3DXVECTOR3 move);									// �ړ��ʂ̐ݒ�
	void SetRot(D3DXVECTOR3 rot);									// �p�x�̐ݒ�
	void SetLife(int nLife);										// ���C�t�̐ݒ�
	void SetCountMotion(int CountMotion);							// ���[�V�����̃J�E���g�ݒ�
	void SetMotionState(int nMotionState);							// ���[�V�����̏�Ԑݒ�
	void SetMotion(int nMotion);									// ���[�V�����̐ݒ� 
	void SetKey(int nKey);											// �L�[�ݒ�
	void SetJump(bool bJump);										// �W�����v�̃t���O
	void SetLanding(bool bLanding);									// ���n�̐ݒ�
	void SetRadius(float fRadius);									// ���a�̐ݒ�
	void SetSpeed(float fSpeed);									// ���x�̐ݒ�
	void SetWeaponTipNum(int nWeaponTipNum);						// ����̃p�[�c�ԍ�
	void SetWeaponRootNum(int nWeaponRootNum);						// ���̍��{�̃p�[�c�ԍ�
	void SetStateCounter(int nStateCounter);						// ��ԃJ�E���^�[�̐ݒ�
	void SetCType(CHARACTER_TYPE Ctype);							// �^�C�v�̐ݒ�

	// Get�֐�
	D3DXVECTOR3 GetPos(void) { return m_pos; }									// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }							// �Â����W���
	D3DXVECTOR3 GetRot(void) { return m_rot; }									// �p�x���
	D3DXVECTOR3 GetMove(void) { return m_move; }								// �ړ��ʂ̏��
	KEY_INFO *GetKeyInfo(void) { return m_apKeyInfo; }							// �L�[���
	Motion_Info GetMotion(int nCount) { return m_Motion[nCount]; }				// ���[�V�������
	int GetLife(void) { return m_nLife; }										// ���C�t�̏��
	int GetCountMotion(void) { return m_nCountMotion; }							// ���[�V�����̃J�E���g
	int GetMotionState(void) { return m_nMotionState; }							// ���[�V�����̏�ԏ��
	int GetKey(void) { return m_nKey; }											// �L�[���
	int GetWeaponPartsNum(void) { return m_nWeaponTipNum; }						// ����̃p�[�c�ԍ��̏��
	int GetWeaponRootNum(void) { return m_nWeaponTipNum; }						// ����̃p�[�c�ԍ��̏��
	int GetStateCounter(void) { return m_nStateCounter; }						// ��ԃJ�E���^�[�̏��
	float GetSpeed(void) { return m_fSpeed; }									// �X�s�[�h�̏��
	float GetRadius(void) { return m_fRadius; }									// ���a�̏��
	CModelAnime *GetModelAnime(int nCount) { return m_apModelAnime[nCount]; }	// ���[�V�����̃J�E���g���
	MODELFILE GetModelFile(int nPartsNum) { return m_modelfile[nPartsNum]; }	// ���f���p�[�c�̏��
	bool GetJump(void) { return m_bJump; }										// �W�����v
	bool GetLanding(void) { return m_bLanding; }								// ���n�̃t���O
	STATE GetState(void) { return m_State; }									// �X�e�[�g���
private:
	STATE m_State;					// �X�e�[�g
	CHARACTER_TYPE m_Ctype;			// �L�����N�^�[�̃^�C�v
	D3DXVECTOR3 m_pos;				// ���W
	D3DXVECTOR3 m_posOld;			// �Â����W
	D3DXVECTOR3 m_move;				// �ړ���
	D3DXVECTOR3 m_rot;				// ���݂̉�]
	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	int m_nLife;					// �̗�
	int m_nMaxLife;					// ���C�t�̍ő��
	int m_nPart;					// �p�[�c
	int m_nCharaNum;				// �L�����N�^�[�̃i���o�[
	int m_nWeaponTipNum;			// ����̃p�[�c�ԍ�
	int m_nWeaponRootNum;			// ���̍��{�̃p�[�c
	int m_nStateCounter;			// ��Ԃ̃J�E���^�[
	float m_fSpeed;					// �ړ���
	float m_fAngle;					// �p�x
	float m_fRadius;				// ���a
	bool m_bJump;					// �W�����v���Ă���t���O
	bool m_bLanding;				// ���n�̃t���O

	// ���f���p�ϐ�
	CModelAnime *m_apModelAnime[MAX_CHARACTER_PARTS];	// ���f���p�[�c�p�̃|�C���^
	MODELFILE m_modelfile[MAX_CHARACTER_PARTS];			// ���f���p�[�c���
	char *m_pFileName;									// �t�@�C���̖��O

	// ���[�V�����p�ϐ�
	Motion_Info m_Motion[30];		// ���[�V�������
	KEY_INFO *m_apKeyInfo;			// �L�[���̃|�C���^
	int m_nMotionState;				// ���[�V�����̏��
	int m_nNumKey;					// �L�[�̑���
	int m_nCountMotion;				// ���[�V�����J�E���^�[
	int m_nMotionInterval;			// ���[�V�����̃C���^�[�o��
	int m_nKey;						// ���݃L�[��No
	bool m_bMotionPlaing;			// ���[�V�����̍Đ�

	D3DXVECTOR3 m_diffPos;			// �ύX���W
	D3DXVECTOR3 m_diffRot;			// �ύX�p�x

	// �ÓI�����o�ϐ�
	static int m_nAllNum;			// �L�����N�^�[�̑���
};
#endif