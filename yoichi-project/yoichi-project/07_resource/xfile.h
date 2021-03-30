#ifndef _XFILE_H_
#define _XFILE_H_
//=============================================================================
//
// X�t�@�C���Ǘ��w�b�_�[ [xfile.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_XFILE_TEXTURE	(256)		// �e�N�X�`���̍ő�
#define MAX_NAME_NUM		(1024)		// ���O�̍ő�
#define MAX_MODEL_PARTS		(22)		// ���f���̍ő吔


//=============================================================================
//�N���X�錾
//=============================================================================
class CXfile
{
public:
	//=============================================================================
	//�@���f���t�@�C�����̍\����
	//=============================================================================
	struct MODELFILE
	{
		char xFileName[MAX_NAME_NUM];	// �t�@�C���l�[��
		D3DXVECTOR3 offsetPos;			// �ʒu�̃I�t�Z�b�g���
		D3DXVECTOR3 offsetRot;			// �����̃I�t�Z�b�g���
		int nParent;					// �e���
	};

	// ���f���̔ԍ��̗񋓌^
	enum XFILE_NUM
	{
		XFILE_NUM_NONE = -1,			// �����l
		XFILE_NUM_BG,					// �w�i
		XFILE_NUM_ITEM_BOX,				// �A�C�e���{�b�N�X
		XFILE_NUM_BOMB_BOX,				// �{���̃{�b�N�X
		XFILE_NUM_WINDSPHERE,			// ���̋��̃��f��
		XFILE_NUM_BARRIER,				// �o���A�̃��f��
		XFILE_NUM_BARRIER_EFFECT,		// �o���A�G�t�F�N�g�p�̃��f��
		XFILE_NUM_MAX
	};

	enum HIERARCHY_XFILE_NUM
	{
		HIERARCHY_XFILE_NUM_NONE = -1,			// �����l
		HIERARCHY_XFILE_NUM_PLAYER,				// �w�v���C���[���f��
		HIERARCHY_XFILE_NUM_MAX					// �ő吔
	};

	typedef struct
	{
		char *xFileName;									// �t�@�C���l�[��
		LPD3DXMESH pMesh;									// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;								// �}�e���A�����ւ̃|�C���^
		DWORD dwNumMat;										// �}�e���A�����̐�
		LPDIRECT3DTEXTURE9 apTexture[MAX_XFILE_TEXTURE];	// �e�N�X�`���̐�
	}MODEL;

	CXfile();		// �R���X�g���N�^
	~CXfile();		// �f�X�g���N�^

	static CXfile *Create(void);					// �C���X�^���X����

	// �P�̂̃��f��
	HRESULT ModelLoad(void);						// ���f�����[�h
	void ModelUnLoad(void);							// ���f���A�����[�h

	// �K�w�\�����f��
	HRESULT HierarchyReadFile(void);				// �K�w�\���̂��郂�f���ǂݍ���
	HRESULT HierarchyModelLoad(void);				// �K�w�\���̃��f�����[�h
	void HierarchyModelUnLoad(void);				// �K�w�\���̃��f���A�����[�h
	void SetFileName(void);				// �t�@�C���̖��O��ݒ�

	// Get�֐�
	MODEL GetXfile(XFILE_NUM Tex_Num);																		// ���f���̏��
	LPDIRECT3DTEXTURE9 *GetXfileTexture(XFILE_NUM TexNum);													// ���f���Ɏg�p����e�N�X�`�����
	
	// �K�w�\���p
	MODELFILE GetModelFile(int nCount, HIERARCHY_XFILE_NUM FileNum)			{ return m_aModelFile[nCount][FileNum]; }			// ���f���p�[�c�̏��
	int GetModelParts(HIERARCHY_XFILE_NUM FileNum)							{ return m_nMaxParts[FileNum]; }					// ���f���̃p�[�c��
	char *GetFileName(int nParts, HIERARCHY_XFILE_NUM FileNum)				{ return m_aModelFile[nParts][FileNum].xFileName; }	// �t�@�C���̖��O
	D3DXVECTOR3 GetFileOffsetPos(int nParts, HIERARCHY_XFILE_NUM FileNum)	{ return m_aModelFile[nParts][FileNum].offsetPos; }	// ���W
	D3DXVECTOR3 GetFileOffsetRot(int nParts, HIERARCHY_XFILE_NUM FileNum)	{ return m_aModelFile[nParts][FileNum].offsetRot; }	// �p�x
	char *GetModelFileName(HIERARCHY_XFILE_NUM FileNum)						{ return m_pFileName[FileNum]; }					// ���f���t�@�C���̖��O
	MODEL GetHierarchyXfile(int nParts, HIERARCHY_XFILE_NUM FileNum)		{ return m_aHierarchyModel[nParts][FileNum]; }

private:
	// �P�̂̃��f��
	MODEL m_aXfile[XFILE_NUM_MAX];										// X�t�@�C�����̍\����

	// �K�w�\���̃��f���p
	MODEL m_aHierarchyModel[MAX_MODEL_PARTS][HIERARCHY_XFILE_NUM_MAX];	// �K�w�\�����f���̍\����
	MODELFILE m_aModelFile[MAX_MODEL_PARTS][HIERARCHY_XFILE_NUM_MAX];	// ���f���̐��Ǝ��
	char *m_pFileName[HIERARCHY_XFILE_NUM_MAX];							// �t�@�C���̖��O
	int m_nMaxParts[HIERARCHY_XFILE_NUM_MAX];							// �t�@�C�����Ƃ̃p�[�c��
};
#endif
