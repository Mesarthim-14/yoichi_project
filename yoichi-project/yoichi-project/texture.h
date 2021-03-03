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
	typedef enum
	{
		TEXTURE_NUM_NONE = -1,		// �����l
		TEXTURE_NUM_EFFECT,			// ��
		TEXTURE_NUM_FLOOR,			// ���e�N�X�`��
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	// �A�j���[�V�������s���e�N�X�`���̗񋓌^
	typedef enum
	{
		SEPARATE_TEX_NONE = -1,			// �����l
		SEPARATE_TEX_NUMBER,		// �R���{�̃i���o�[
		SEPARATE_TEX_MAX				// �ő�l
	}SEPARATE_TEX_TYPE;

	// �A�j���[�V�������s���e�N�X�`���̍\���̏��
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pSeparateTexture;		// �����e�N�X�`���ւ̃|�C���^
		SEPARATE_TEX_TYPE type;						// �e�N�X�`���̎��
		D3DXVECTOR2 m_TexInfo;						// �e�N�X�`���̕������A����
		bool bLoop;									// ���[�v���邩
	}SEPARATE_TEX_INFO;

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static CTexture *Create(void);												// �C���X�^���X����

	 HRESULT Load(void);														// �e�N�X�`�����[�h
	 void UnLoad(void);															// �e�N�X�`���A�����[�h
	 HRESULT SeparateTexLoad(void);												// �����e�N�X�`�����[�h
	 void SeparateTexUnLoad(void);												// �����e�N�X�`���A�����[�h

	 LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);						// �e�N�X�`���̏��

	 LPDIRECT3DTEXTURE9 GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type);		// �����e�N�X�`�����
	 D3DXVECTOR2 GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type);				// �����e�N�X�`���@UV�̖����擾
	 bool GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type);					// ���[�v���邩
private:
	LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];							// �e�N�X�`���̃|�C���^

	// �����e�N�X�`���̍\����
	SEPARATE_TEX_INFO m_apSeparateTexture[SEPARATE_TEX_MAX] =
	{
		nullptr, CTexture::SEPARATE_TEX_NUMBER, D3DXVECTOR2(5, 5), false,
	};
	// �����e�N�X�`���̃|�C���^
};
#endif
