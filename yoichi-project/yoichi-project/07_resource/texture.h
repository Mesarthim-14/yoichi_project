#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:
	// �e�N�X�`���̔ԍ��̗񋓌^
	enum TEXTURE_TYPE
	{
		TEXTURE_NUM_NONE = -1,			// �����l
		TEXTURE_NUM_EFFECT,				// ��
		TEXTURE_NUM_FLOOR,				// ���e�N�X�`��
		TEXTURE_NUM_TITLE_LOGO,			// �^�C�g�����S
		TEXTURE_NUM_ITEM_BLUE_WING,		// �A�C�e�����H��
		TEXTURE_NUM_ITEM_RED_WING,		// �A�C�e���Ԃ��H
		TEXTURE_NUM_ITEM_BOMB,			// �A�C�e�����e
		TEXTURE_NUM_ITEM_BARRIER,		// �A�C�e���o���A
		TEXTURE_NUM_ITEM_THUNDER,		// �A�C�e����
		TEXTURE_NUM_ITEM_MHAND,			// �A�C�e��M�n���h
		TEXTURE_NUM_ITEM_VORTEX,		// �A�C�e���Q
		TEXTURE_NUM_SEA,				// �C
		TEXTURE_NUM_RESULT_1ST,			// ���U���g1��
		TEXTURE_NUM_RESULT_2ND,			// ���U���g1��
		TEXTURE_NUM_RESULT_3RD,			// ���U���g1��
		TEXTURE_NUM_RESULT_4TH,			// ���U���g1��
		TEXTURE_NUM_STAR,			// ��
		TEXTURE_NUM_RING,			// ��
		TEXTURE_NUM_LACKRING,		// ��������
		TEXTURE_NUM_SMOKE,			// ��
		TEXTURE_NUM_KIRAKIRA,		// �L���L��
		TEXTURE_NUM_MAX
	};

	// �A�j���[�V�������s���e�N�X�`���̗񋓌^
	enum SEPARATE_TEX_TYPE
	{
		SEPARATE_TEX_NONE = -1,			// �����l
		SEPARATE_TEX_NUMBER,			// �R���{�̃i���o�[
		SEPARATE_TEX_LIGHTNINGSTRIKE,	// �����̃e�N�X�`��
		SEPARATE_TEX_THUNDER,			// ���̃e�N�X�`��
		SEPARATE_TEX_SHOCKWAVE,			// �Ռ��g�̃e�N�X�`��
		SEPARATE_TEX_WIND,				// ���̃e�N�X�`��
		SEPARATE_TEX_EXPLOSION,			// �����̃e�N�X�`��
		SEPARATE_TEX_MAGICHANDLEFT,		// �}�W�b�N�n���h�̍��̃e�N�X�`��
		SEPARATE_TEX_MAGICHANDRIGHT,	// �}�W�b�N�n���h�̉E�̃e�N�X�`��
		SEPARATE_TEX_MAX				// �ő�l
	};

	// �A�j���[�V�������s���e�N�X�`���̍\���̏��
	struct SEPARATE_TEX_INFO
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// �����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						// �e�N�X�`���̎��
		D3DXVECTOR2 m_TexInfo;						// �e�N�X�`���̕������A����
		bool bLoop;									// ���[�v���邩
	};

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static CTexture *Create(void);												// �C���X�^���X����

	 HRESULT Load(void);														// �e�N�X�`�����[�h
	 void Unload(void);															// �e�N�X�`���A�����[�h
	 HRESULT SeparateTexLoad(void);												// �����e�N�X�`�����[�h
	 void SeparateTexUnload(void);												// �����e�N�X�`���A�����[�h

	 LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);						// �e�N�X�`���̏��

	 LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);		// �����e�N�X�`�����
	 D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);				// �����e�N�X�`���@UV�̖����擾
	 bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ���[�v���邩
private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];							// �e�N�X�`���̃|�C���^

	// �����e�N�X�`���̍\����
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, CTexture::SEPARATE_TEX_NUMBER, D3DXVECTOR2(5, 4), false,
		nullptr, CTexture::SEPARATE_TEX_LIGHTNINGSTRIKE, D3DXVECTOR2(6, 5), false,
		nullptr, CTexture::SEPARATE_TEX_THUNDER, D3DXVECTOR2(10, 5), false,
		nullptr, CTexture::SEPARATE_TEX_SHOCKWAVE, D3DXVECTOR2(5, 3), false,
		nullptr, CTexture::SEPARATE_TEX_WIND, D3DXVECTOR2(30, 1), false,
		nullptr, CTexture::SEPARATE_TEX_WIND, D3DXVECTOR2(8, 5), false,
		nullptr, CTexture::SEPARATE_TEX_MAGICHANDLEFT, D3DXVECTOR2(2, 5), true,
		nullptr, CTexture::SEPARATE_TEX_MAGICHANDRIGHT, D3DXVECTOR2(2, 5), true,
	};
	// �����e�N�X�`���̃|�C���^
};
#endif
