#ifndef _MODEL_H_
#define _MODEL_H_
//=============================================================================
//
// ���f������ [model.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MODEL_TEXTURE	(256)		// �e�N�X�`���̍ő吔

//=============================================================================
// ���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
	typedef enum
	{
		MODEL_TYPE_NONE = 0,	// �����l
		MODEL_TYPE_PLAYER1,		// �v���C���[
		MODEL_TYPE_PLAYER2,		// �v���C���[
		MODEL_TYPE_BEAM,		// �r�[��
		MODEL_TYPE_OBJECT,		// ����
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CModel(PRIORITY Priority = PRIORITY_EFFECT);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// �C���X�^���X����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	void BindModel(CXfile::MODEL model);						// ���f���̐ݒ�
	void BindTexture(LPDIRECT3DTEXTURE9 *pTexture);				// �e�N�X�`���̐ݒ�
	void SubAlpha(float fAlpha);								// �����x�̌��Z
	
	// Set�֐�
	void SetPos(const D3DXVECTOR3 pos);		// ���W�̐ݒ�
	void SetMove(const D3DXVECTOR3 move);	// �ړ��ʂ̐ݒ�
	void SetRot(const D3DXVECTOR3 rot);		// ���W�̏��
	void SetType(MODEL_TYPE Mtype);			// ���f���̎�ސݒ�
	void SetSize(D3DXVECTOR3 size);			// �T�C�Y�̐ݒ�
	void SetTexPattern(int TexPattern);		// �e�N�X�`���̃p�^�[��
	void SetLife(int nLife);				// ���C�t�̐ݒ�
	void SetColor(D3DXCOLOR color);			// �F�̐ݒ�
	void SetAlphaNum(float fAlphaNum);		// �����x�̐ݒ�

	// Get�֐�
	D3DXVECTOR3 GetPos(void)const;						// ���W�̏��
	D3DXVECTOR3 GetMove(void);							// �ړ��ʂ̏��
	D3DXVECTOR3 GetSize(void);							// �T�C�Y�̐ݒ�
	D3DXVECTOR3 GetRot(void);							// �p�x�̐ݒ�
	MODEL_TYPE GetType(void);							// ��ނ̏��
	D3DXCOLOR GetColor(void);							// �F�̏��
	D3DXMATRIX GetMtxWorld(void);						// ��0���h�}�g���N�X
	LPD3DXMESH GetMesh(void)const;						// ���b�V�����
	LPD3DXBUFFER GetBuffMat(void);						// �o�b�t�@���
	DWORD GetNumMat(void);								// �}�g���N�X�̐�
	int GetTexPattern(void);							// �e�N�X�`��
	int GetLife(void);									// ���C�t�̐ݒ�
	float GetAlphaNum(void) { return m_fAlphaNum; }		// �����x�̒l
private:
	LPDIRECT3DTEXTURE9 *m_apTexture;	// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_move;					// �ړ���
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	MODEL_TYPE m_type;					// ���
	D3DXCOLOR m_Color;					// �F
	CXfile::MODEL m_Model;				// ���f���̍\����
	int m_nTexPattern;					// �e�N�X�`���̃p�^�[����
	int m_nLife;						// ���C�t
	float m_fAlphaNum;					// �����x�̒l
};
#endif 