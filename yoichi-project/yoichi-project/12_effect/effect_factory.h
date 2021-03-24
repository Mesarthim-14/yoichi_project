#ifndef _EFFECT_FACTORY_H_
#define _EFFECT_FACTORY_H_
//=============================================================================
//
// �p�[�e�B�N�������N���X�w�b�_�[ [effect_factory.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �G�t�F�N�g����
//=============================================================================
class CEffectFactory
{
public:
	// �����̎��
	typedef enum
	{
		MOVE_TYPE_NONE = -1,			// �����l
		MOVE_TYPE_ALLRANDOM,			// ���S�����_��
		MOVE_TYPE_XZRANDOM				// �c�Ɖ��̃����_��
	}MOVE_TYPE;

	// �p�[�e�B�N���̍\����
	typedef struct
	{
		D3DXVECTOR3 size;		// �T�C�Y
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 rot;		// �p�x
		D3DXVECTOR3 Range;		// �͈�
		D3DXVECTOR3 Scale;		// �g�嗦
		MOVE_TYPE movetype;		// �����̎��
		int nLife;				// ���C�t
		int nNum;				// ��
		D3DXCOLOR color;		// �F
		bool bGravity;			// �d�͂������邩
		D3DXVECTOR3 GravityNum;	// �d�͂̒l
		float fTransparency;	// �����x�����炷�l
		bool bAlpha;			// �A���t�@�e�X�g
		int nAlphaNum;			// �A���t�@�e�X�g�̒l
		bool bAnimation;		// �A�j���[�V���������邩�ǂ���
		bool bBlend;			// ���Z����
		bool bUseZbuf;			// Z�o�b�t�@
		int nPriority;			// �`��D�揇��
	}EFFECT;

	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		EFFECT_NUM_NONE = -1,			// �����l
		EFFECT_NUM_PARTICLE,			// �_���[�W���󂯂��Ƃ�
		EFFECT_NUM_LIGHTNINGSTRIKE,		// ���̃A�C�e�����g��ꂽ�Ƃ�
		EFFECT_NUM_THUNDER,				// �������������Ƃ�
		EFFECT_NUM_STAR,				// ��
		EFFECT_NUM_SHOCKWAVE,			// �Ռ��g
		EFFECT_NUM_WIND,				// ��
		EFFECT_NUM_STATUSUP,			// ��Ԃ��ǂ��Ȃ����Ƃ�
		EFFECT_NUM_STATUSDOWN,			// ��Ԃ������Ȃ����Ƃ�
		EFFECT_NUM_EXPLOSION,			// ����
		EFFECT_NUM_EXPLOSIONCIRCLE,		// �����̉~
		EFFECT_NUM_EXPLOSIONSPARK,		// �����̉Ή�
		EFFECT_NUM_SINKER,				// �d��
		EFFECT_NUM_STATESUPPARTICLE,	// ��Ԃ��ǂ��Ȃ����Ƃ��̗��q
		EFFECT_NUM_STATUSDOWNPARTICLE,	// ��Ԃ������Ȃ����Ƃ��̗��q
		EFFECT_NUM_KIRAKIRA,			// ���ł���Ƃ��̃L���L��
		EFFECT_NUM_MAX
	}EFFECT_TYPE;

	CEffectFactory();												// �R���X�g���N�^
	~CEffectFactory();												// �f�X�g���N�^

	static HRESULT ReadFile(void);									// �t�@�C���̓ǂݍ���
	static void CreateEffect(D3DXVECTOR3 pos, EFFECT_TYPE type);	// �p�[�e�B�N���̃N���X
private:
	static EFFECT m_Effect[EFFECT_NUM_MAX];							// �p�[�e�B�N��
};
#endif
