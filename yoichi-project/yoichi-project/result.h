#ifndef _RESULT_H_
#define _RESULT_H_
//=============================================================================
//
// ���U���g���� [result.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CScene2D;

//=============================================================================
//���U���g�N���X
//=============================================================================
class CResult : public CScene
{
public:
	CResult(PRIORITY Priority = PRIORITY_0);			// �R���X�g���N�^
	~CResult();											// �f�X�g���N�^

	static CResult* Create(void);						// �C���X�^���X����
	static HRESULT Load(void);							// �e�N�X�`���̃��[�h	
	static void UnLoad(void);							// �e�N�X�`���A�����[�h
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];			// �e�N�X�`���p�|�C���^
	CScene2D* m_pScene2D;								// �V�[��2D
};
#endif