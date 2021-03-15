#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_LIFE_NUM				(100)		// �\�����郉�C�t�̐�
#define MOTION_KEYSET_MAX			(32)		// �L�[�Z�b�g�ő吔
#define PLAYER2_POS_X				(0.0f)		// ���W
#define PLAYER2_POS_Y				(171.0f)	// ���W
#define PLAYER2_POS_Z				(500)		// ���W
#define PLAYER_SIZE_X				(1)			// �T�C�Y
#define PLAYER_SIZE_Y				(1)			// �T�C�Y
#define PLAYER_SIZE_Z				(1)			// �T�C�Y
#define PLAYER_BASE_POS_Y			(200.0f)	// �v���C���[�̍��W�̃x�[�X

#define PLAYER_COLLISION_X			(200)		// �����蔻��
#define PLAYER_COLLISION_Y			(175)		// �����蔻��
#define PLAYER_COLLISION_Z			(200)		// �����蔻��
#define WEAPON_COLLISION_X			(150)		// ����̓����蔻��
#define WEAPON_COLLISION_Y			(150)		// ����̓����蔻��
#define WEAPON_COLLISION_Z			(150)		// ����̓����蔻��
#define MAP_LIMIT					(11000)		// �}�b�v���

//=============================================================================
// �O���錾
//=============================================================================
class CItem;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{

public:
	//=============================================================================
	// �v���C���[�̃p�[�c�ԍ�
	//=============================================================================
	enum PARTS_NUM
	{
		PARTS_NUM_NONE = -1,
		PARTS_NUM_WAIST,			// [0]��
		PARTS_NUM_BODY,				// [1]��
		PARTS_NUM_HEAD,				// [2]��
		PARTS_NUM_RIGHT_SHOLDER,	// [3]�E��
		PARTS_NUM_RIGHT_UPPERARM,	// [4]�E��r
		PARTS_NUM_RIGHT_ARM,		// [5]�E�r
		PARTS_NUM_RIGHT_HAND,		// [6]�E��̂Ђ�
		PARTS_NUM_LEFT_SHOLDER,		// [7]����
		PARTS_NUM_LEFT_UPPERARM,	// [8]����r
		PARTS_NUM_LEFT_ARM,			// [9]���r
		PARTS_NUM_RIGHT_THIGHS,		// [10]�E��
		PARTS_NUM_RIGHT_SHIN,		// [11]�E��
		PARTS_NUM_RIGHT_SHOE,		// [12]�E��
		PARTS_NUM_LEFT_THIGHS,		// [13]����
		PARTS_NUM_LEFT_SHIN,		// [14]����
		PARTS_NUM_LEFT_SHOE,		// [15]����
		PARTS_NUM_BACKPACK,			// [16]�o�b�N�p�b�N
		PARTS_NUM_RIGHT_WING,		// [17]�E��
		PARTS_NUM_LEFT_WING,		// [18]����
		PARTS_NUM_WEAPON,			// [19]����
		PARTS_NUM_COLLISION,		// [20]�����蔻��
		PARTS_NUM_ROOT,				// [21]���̍��{
		PARTS_NUM_MAX,				// ���[�V�����ő吔
	};

	//=============================================================================
	// �v���C���[�̏��
	//=============================================================================
	enum PLAYER_STATE
	{
		PLAYER_STATE_NONE = 0,		// �����u
		PLAYER_STATE_NORMAL,		// �ʏ���
		PLAYER_STATE_DAMAGE,		// �_���[�W
		PLAYER_STATE_EXPLOSION,		// ����
		PLAYER_STATE_DRAW,			// ��������
		PLAYER_STATE_MAX			// �ő吔
	};

	//=============================================================================
	//�@���[�V������Ԃ̗񋓌^
	//=============================================================================
	enum MOTION_STATE
	{
		MOTION_NONE = -1,
		MOTION_IDOL,				// �A�C�h�����[�V����
		MOTION_WALK,				// ���s���[�V����
		MOTION_JUMP,				// �W�����v���[�V����
		MOTION_MAX,					// ���[�V�����ő吔
	};

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);			// �R���X�g���N�^
	~CPlayer();													// �f�X�g���N�^

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCount);	// �N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	void UpdateState(void);										// �v���C���[�̏��
	void UpdateMotionState(void);								// ���[�V�������
	void PlayerControl(void);									// �v���C���[�̐���
	void Walk(void);											// �v���C���[�̕�������
	void Jump(void);											// �W�����v�̏���
	void Death(void);											// ���񂾂Ƃ��̏���
	void MapLimit(void);										// �}�b�v�̐���
	void UseItem(void);											// �A�C�e���̎g�p����
	void AcquiredItem(CItem *pItem);							// �A�C�e���l���֐�

	// Set�֐�
	void SetArmor(bool bArmor) { m_bArmor = bArmor; }			// ���G��Ԃ̐ݒ�

	// Get�֐�
	CItem *GetItem(void)		{ return m_pItem; }				// �A�C�e���̃|�C���^
	bool HasItem(void)			{ return m_pItem != nullptr; }	// �|�C���^�������Ă��邩
	float GetBaseSpeed(void)	{ return m_fBaseSpeed; }		// ���̃X�s�[�h
	bool GetArmor(void)			{ return m_bArmor; }			// ���G���

private:
	D3DXVECTOR3 m_rotDest;		// ��](�ڕW�l)
	bool m_bWalk;				// �����Ă���t���O
	bool m_bDraw;				// �`��̃t���O
	bool m_bArmor;				// ���G���
	int m_nEndCounter;			// ���񂾌�̃J�E���^�[
	int m_nNumber;				// �v���C���[�̔ԍ�
	float m_fBaseSpeed;			// ���̃X�s�[�h
	CItem *m_pItem;				// �A�C�e���̃|�C���^
};
#endif

