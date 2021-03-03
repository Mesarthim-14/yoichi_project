#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
//=============================================================================
//
// ���\�[�X�}�l�[�W���[���� [resource_manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;
class CXfile;

//=============================================================================
// ���\�[�X�}�l�[�W���[�N���X
//=============================================================================
class CResourceManager
{
public:
	~CResourceManager();						// �f�X�g���N�^

	HRESULT Init(void);							// ����������
	void LoadAll(void);							// �S�Ẵ��[�h����
	void UnLoadAll(void);						// �S�ẴA�����[�h

	static CResourceManager *GetInstance(void);	// �C���X�^���X�擾�֐�

	// Get�֐�
	CTexture *GetTextureClass(void) { return m_pTexture; }	// �e�N�X�`���̏��
	CXfile *GetXfileClass(void) { return m_pXFile; }	// �e�N�X�`���̏��

private:
	CResourceManager();								// �R���X�g���N�^
	static CResourceManager *m_pResourceManager;	// ���g�̃|�C���^
	CTexture *m_pTexture;					// �e�N�X�`���̃|�C���^
	CXfile *m_pXFile;						// X�t�@�C���̃|�C���^
};

#endif