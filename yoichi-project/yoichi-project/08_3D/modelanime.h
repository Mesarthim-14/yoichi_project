//=============================================================================
//
// �K�w�\���p�̃��f������ [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================
#ifndef _MODELANIME_H_
#define _MODELANIME_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xfile.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MODEL_TEXTURE		(256)		// �e�N�X�`���̍ő吔
#define MAX_OLD_MTX_WORLD		(5)			// ���[���h�}�g���N�X�̔z��
#define MAX_MODEL_PARTS			(22)		// �L�����N�^�[�̃p�[�c�ő吔

//=============================================================================
//�K�w���f���N���X
//=============================================================================
class CModelAnime
{
public:
	CModelAnime();		// �R���X�g���N�^
	~CModelAnime();		// �f�X�g���N�^

	static CModelAnime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// �C���X�^���X����

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						// ����������
	void Uninit(void);													// �I������
	void Update(void);													// �X�V����
	void Draw(void);													// �`�揈��

	// Set�֐�
	void SetParent(CModelAnime *pParent);								// �e�̐ݒ�
	void SetPosAnime(const D3DXVECTOR3 posAnime);						// �A�j���[�V�����p�[�c�̍��W
	void SetRotAnime(const D3DXVECTOR3 rotAnime);
	void SetModel(CXfile::MODEL model);											// ���f�����̐ݒ�

	// Get���
	D3DXVECTOR3 GetPos(void)const;										// ���W���
	D3DXVECTOR3 GetPosAnime(void)const;									// �A�j���[�V�������W���
	D3DXVECTOR3 GetRot(void)const;										// �p�x�̏��
	D3DXVECTOR3 GetRotAnime(void)const;									// �A�j���[�V�����p�x���
	D3DXMATRIX GetMtxWorld(void);										// ���[���h�}�g���N�X���
	D3DXMATRIX GetOldMtxWorld(void);									// �Â����[���h�}�g���N�X�̏��

private:
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_MODEL_TEXTURE];		// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3 m_rot;										// ����
	D3DXVECTOR3 m_posAnime;									// �A�j���[�V�����p�̈ʒu
	D3DXVECTOR3 m_rotAnime;									// �A�j���[�V�����p�̌���
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X
	CModelAnime *m_pParent;									// �e���̃|�C���^
	D3DXMATRIX m_OldMtxWorld;								// �Â����[���h���W
	D3DXMATRIX m_OldMtxWorld1[MAX_OLD_MTX_WORLD];			// 5�t���[���܂ł̌Â����W
	CXfile::MODEL m_model;									// ���f�����
};

#endif 