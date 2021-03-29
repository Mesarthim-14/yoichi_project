#ifndef _POLYGON_H_
#define _POLYGON_H_
//=============================================================================
//
// �|���S�������N���X���� [polygon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�|���S���N���X
//=============================================================================
class CPolygon
{
public:

	CPolygon();			// �R���X�g���N�^
	virtual ~CPolygon();		// �f�X�g���N�^

	static CPolygon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);	// �C���X�^���X����

	virtual HRESULT Init(void);				// ����������
	virtual void Uninit(void);															// �I������
	virtual void Update(void);															// �X�V����
	virtual void Draw(void);															// �`�揈��
	virtual void BindTexture(LPDIRECT3DTEXTURE9 pTexture);								// �e�N�X�`������
	virtual void SetColor(const D3DXCOLOR color);										// �F�̐ݒ�
	
    void UpdateVertex(D3DXVECTOR3 pos, D3DXVECTOR3 size);       // ���_�̍X�V
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_size;						// �|���S���̃T�C�Y
	D3DXVECTOR3 m_pos;						// ���C�t�̈ʒu
};
#endif 