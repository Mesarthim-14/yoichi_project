#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// �|���S�������N���X���� [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//���C�t�N���X
//=============================================================================
class CPolygon
{
public:
	//=========================================================================
	//�񋓌^��`
	//=========================================================================
	typedef enum
	{
		TEX_TYPE_NONE = 0,
		TEX_TYPE_TITLE,			//�^�C�g���e�N�X�`��
		TEX_TYPE_RESULET,		//���U���g�e�N�X�`��
		TEX_TYPE_LIFE_GAUGE,	//���C�t�e�N�X�`��
		TEX_TYPE_UNDERUI,		//�A���_�[UI�e�N�X�`��
		TEX_TYPE_CHEETAH,		//�`�[�^�[
		TEX_TYPE_GORILLA,		//�S����
		TEX_TYPE_TURTLE,		//�J��
		TEX_TYPE_PRESSENTER,	//PRESS ENTER�e�N�X�`��
		TEX_TYPE_MAX,			//�ő�e�N�X�`��
	}TEX_TYPE;

	CPolygon();			// �R���X�g���N�^
	~CPolygon();		// �f�X�g���N�^

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const TEX_TYPE type);	// �C���X�^���X����

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const TEX_TYPE type);				// ����������
	void Uninit(void);																				// �I������
	void Update(void);																				// �X�V����
	void Draw(void);																				// �`�揈��

	void SetType(const TEX_TYPE type);																// �e�N�X�`���^�C�v
	void SetColor(const D3DXCOLOR color);															// �F�̐ݒ�

private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_size;					// �|���S���̃T�C�Y
	D3DXVECTOR3 m_pos;					// ���C�t�̈ʒu
	TEX_TYPE m_Type;					// �^�C�v
};
#endif 