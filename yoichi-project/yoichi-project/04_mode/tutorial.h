//=============================================================================
//
//  [tutorial.h]
// Author : �����D�I
//
//=============================================================================

#ifndef  _TUTORIAL_H_
#define  _TUTORIAL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"

//=============================================================================
//�O���錾
//=============================================================================
class CScene2D;

//=============================================================================
//�}�N����`
//=============================================================================

//=============================================================================
//�N���X�錾
//=============================================================================
class CTutorial : public CScene
{
public:
	CTutorial(PRIORITY Priority = PRIORITY_0);
	~CTutorial();
	static CTutorial* Create(void);
	static HRESULT Load(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[1];	//�e�N�X�`���ւ̃|�C���^
	CScene2D* m_pScene;	//�|�C���^
};

#endif // ! _TUTORIAL_H_
