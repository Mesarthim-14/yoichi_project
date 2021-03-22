#ifndef _MESH_PILLAR_H_
#define _MESH_PILLAR_H_
//=====================================================
//
// ���̐����N���X�w�b�_�[ [mesh_pillar.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "mesh_3d.h"

//=============================================================================
// �����b�V���N���X
//=============================================================================
class CMeshPillar : public CMesh3d
{
public:
	CMeshPillar(PRIORITY Priority = PRIORITY_0);						// �R���X�g���N�^
	~CMeshPillar();													// �f�X�g���N�^

	HRESULT Init(void);												// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);													// �`�揈��

	static CMeshPillar*Create(D3DXVECTOR3 pos,MESH_TYPE MeshNum);	// �C���X�^���X����

	// Get�֐�
	D3DXVECTOR3 GetPos(void) { return CSceneBase::GetPos(); }		// ���W���
private:
};

#endif