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
#include "xfile.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_CHARACTER_PARTS (22)	// �L�����N�^�[�̃p�[�c��
#define MAX_KEYFRAME		(10)	// �L�[�t���[���̍ő吔

//=============================================================================
// �O���錾
//=============================================================================
class CLifeBar;
class CLifeFrame;
class CMotion;

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

	CCharacter(PRIORITY Priority = PRIORITY_CHARACTER);				// �R���X�g���N�^
	virtual ~CCharacter();											// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			// ����������
	virtual void Uninit();											// �I������
	virtual void Update();											// �X�V����
	virtual void Draw();											// �`�揈��

	bool Gravity(void);												// �n�ʂ̐���
	void BodyCollision(void);										// �����蔻��
	void ModelCreate(CXfile::HIERARCHY_XFILE_NUM FileNum);			// ���f���̐���
	void ModelAnimeUpdate(void);									// ���f���A�j���[�V����
	void Landing(float fPosY);										// ���n����

	// �������z�֐�
	virtual void UpdateState(void) = 0;								// �L�����N�^�[���
	virtual void UpdateMotionState(void) = 0;						// ���[�V�����̏��
	virtual void Death(void) = 0;									// ���񂾂Ƃ��̏���

	// Set�֐�
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 posOld);								// ���W�̐ݒ�
	void SetMove(D3DXVECTOR3 move);									// �ړ��ʂ̐ݒ�
	void SetRot(D3DXVECTOR3 rot);									// �p�x�̐ݒ�
	void SetLife(int nLife);										// ���C�t�̐ݒ�
	void SetJump(bool bJump);										// �W�����v�̃t���O
	void SetLanding(bool bLanding);									// ���n�̐ݒ�
	void SetRadius(float fRadius);									// ���a�̐ݒ�
	void SetSpeed(float fSpeed);									// ���x�̐ݒ�
	void SetStateCounter(int nStateCounter);						// ��ԃJ�E���^�[�̐ݒ�
	void SetMotion(int nMotionState);								// ���[�V�����̐ݒ�
	void SetUseGravity(bool bUseGravity);

	// Get�֐�
	D3DXVECTOR3 GetPos(void) { return m_pos; }									// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }							// �Â����W���
	D3DXVECTOR3 GetRot(void) { return m_rot; }									// �p�x���
	D3DXVECTOR3 GetMove(void) { return m_move; }								// �ړ��ʂ̏��
	int GetLife(void) { return m_nLife; }										// ���C�t�̏��
	int GetStateCounter(void) { return m_nStateCounter; }						// ��ԃJ�E���^�[�̏��
	float GetSpeed(void) { return m_fSpeed; }									// �X�s�[�h�̏��
	float GetRadius(void) { return m_fRadius; }									// ���a�̏��
	CModelAnime *GetModelAnime(int nCount) { return m_apModelAnime[nCount]; }	// ���[�V�����̃J�E���g���
	bool GetJump(void) { return m_bJump; }										// �W�����v
	bool GetLanding(void) { return m_bLanding; }								// ���n�̃t���O
	bool GetUseGravity(void) { return m_bUseGravity; }
	STATE GetState(void) { return m_State; }									// �X�e�[�g���
	CMotion *GetMotion(void) { return m_pMotion; }								// ���[�V�����̃|�C���^���

private:
	// ���f���p�ϐ�
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// ���f���p�[�c�p�̃|�C���^
	CMotion *m_pMotion;								// ���[�V�����N���X�̃|�C���^
	STATE m_State;									// �X�e�[�g
	D3DXVECTOR3 m_pos;								// ���W
	D3DXVECTOR3 m_posOld;							// �Â����W
	D3DXVECTOR3 m_move;								// �ړ���
	D3DXVECTOR3 m_rot;								// ���݂̉�]
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	int m_nLife;									// �̗�
	int m_nMaxLife;									// ���C�t�̍ő��
	int m_nCharaNum;								// �L�����N�^�[�̃i���o�[
	int m_nStateCounter;							// ��Ԃ̃J�E���^�[
	int m_nParts;									// �p�[�c��
	float m_fSpeed;									// �ړ���
	float m_fAngle;									// �p�x
	float m_fRadius;								// ���a
	bool m_bJump;									// �W�����v���Ă���t���O
	bool m_bLanding;								// ���n�̃t���O
	bool m_bUseGravity;								// �d�͂�K�p���邩
	// �ÓI�����o�ϐ�
	static int m_nAllNum;							// �L�����N�^�[�̑���
};
#endif