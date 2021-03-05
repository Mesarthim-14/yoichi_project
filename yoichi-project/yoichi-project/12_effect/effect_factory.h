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
	// �p�[�e�B�N���̍\����
	typedef struct
	{
		D3DXVECTOR3 size;		// �T�C�Y
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 Distance;	// ����
		int nLife;				// ���C�t
		int nNum;				// ��
		D3DXCOLOR color;		// �F
		bool bGravity;			// �d��
		bool bAlpha;			// �A���t�@�e�X�g
		int nAlphaNum;			// �A���t�@�e�X�g�̒l
		bool bAnimation;		// �A�j���[�V���������邩�ǂ���
		bool bBlend;			// ���Z����
		int nPriority;			// �`��D�揇��
	}EFFECT;

	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		EFFECT_NUM_NONE = -1,			// �����l
		EFFECT_NUM_EXPLOSION,			// �_���[�W���󂯂��Ƃ�
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
