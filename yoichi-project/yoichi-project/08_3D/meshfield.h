#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
//=====================================================
//
// ���b�V���t�B�[���h�̃N���X [meshfield.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "mesh_3d.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FIELD_WIDTH					(3)				// ������
#define FIELD_HEIGHT				(3)				// ������
#define FIELD_WIDTH_SIZE			(25000.0f)		// �T�C�Y
#define FIELD_HEIGHT_SIZE			(25000.0f)		// �T�C�Y

//=============================================================================
// ���b�V���t�B�[���h�N���X
//=============================================================================
class CMeshField : public CMesh3d
{
public:
	CMeshField(PRIORITY = PRIORITY_UI);	// �R���X�g���N�^
	~CMeshField();						// �f�X�g���N�^

	HRESULT Init(void);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CMeshField*Create(void);		// ���b�V���t�B�[���h
private:
};

#endif