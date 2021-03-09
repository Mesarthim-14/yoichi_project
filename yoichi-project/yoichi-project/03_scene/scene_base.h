#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_
//=============================================================================
//
// �V�[���x�[�X�N���X�w�b�_�[ [scene_base.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "scene.h"

//=============================================================================
// �V�[���x�[�X�N���X
//=============================================================================
class CSceneBase : public CScene
{
public:
	CSceneBase(PRIORITY Priority = PRIORITY_0);												// �R���X�g���N�^
	virtual ~CSceneBase();																	// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;							// ����������
	virtual void Uninit(void) = 0;															// �I������
	virtual void Update(void) = 0;															// �X�V����
	virtual void Draw(void) = 0;															// �`�揈��

	// Set�֐�
	virtual void SetPos(D3DXVECTOR3 pos)					{ m_pos = pos; }				// ���W
	virtual void SetSize(D3DXVECTOR3 size)					{ m_size = size; }				// �T�C�Y
	virtual void SetColor(D3DXCOLOR col)					{ m_col = col; }				// �F
	virtual void SetRot(D3DXVECTOR3 rot)					{ m_rot = rot; }				// �p�x		
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture)			{ m_pTexture = pTexture; }		// �e�N�X�`���̐ݒ�
	void BindVtxBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff)		{ m_pVtxBuff = pVtxBuff; }		// ���_�o�b�t�@

	// Get�֐�
	D3DXVECTOR3 GetPos(void)					{ return m_pos; }							// ���W
	D3DXVECTOR3 GetSize(void)					{ return m_size; }							// �T�C�Y
	D3DXCOLOR GetColor(void)					{ return m_col; };							// �F
	D3DXVECTOR3 GetRot(void)					{ return m_rot; };							// ��]��
	LPDIRECT3DTEXTURE9 GetTexture(void)			{ return m_pTexture; }						// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void)	{ return m_pVtxBuff; }						// �o�b�t�@���

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// �o�b�t�@
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_size;						// �T�C�Y
	D3DXCOLOR m_col;						// �F
	D3DXVECTOR3 m_rot;						// ��]��
};

#endif