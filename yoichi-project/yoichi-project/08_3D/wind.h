#ifndef _WIND_H_
#define _WIND_H_
//=============================================================================
//
// ���N���X�w�b�_�[ [wind.h]
// Author : Ito Yogo
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WIND_MAX_SIZE_X		(300.0f)	// X�̃T�C�Y�̍ő�l
#define WIND_MAX_SIZE_Y		(300.0f)	// Y�̃T�C�Y�̍ő�l
#define WIND_MAX_SIZE_Z		(300.0f)	// Z�̃T�C�Y�̍ő�l
#define WIND_MAX_SIZE		(D3DXVECTOR3(WIND_MAX_SIZE_X, WIND_MAX_SIZE_Y, WIND_MAX_SIZE_Z))	// �T�C�Y�̍ő�l

//=============================================================================
// �w�i�N���X
//=============================================================================
class CWind : public CModel
{
public:
	CWind();		// �R���X�g���N�^
	~CWind();		// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	static CWind *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fAngle, D3DXVECTOR3 scale, int nPlayerNum);	// �C���X�^���X����

private:
	D3DXVECTOR3 m_RotQuantity;	// ��]��
	D3DXVECTOR3 m_Scale;		// �g�嗦
};

#endif
