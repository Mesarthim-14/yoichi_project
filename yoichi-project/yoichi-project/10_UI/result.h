//=============================================================================
//
// ���U���g [result.h]
// Author : Yuuki Ikeda
//
//=============================================================================

#ifndef _RESULT_H_
#define _RESULT_H_
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "polygon.h"
#include "player.h"
//=============================================================================
// ���U���g�N���X
//=============================================================================
class CResult : public CPolygon
{
public:
	CResult();     // �R���X�g���N�^
	~CResult();    // �f�X�g���N�^

	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CResult* Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,int nRank);    //�|���S����������

private:
	int m_nRank;										// ����
};

#endif
