//=============================================================================
//
// �v���C���[UI�Ǘ��w�b�_[player_ui.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _PLAYER_UI_H_
#define _PLAYER_UI_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CItem;
class CStar_UI;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer_UI : public CScene
{
public:
    CPlayer_UI(PRIORITY Priority = PRIORITY_UI);
    ~CPlayer_UI();

    static CPlayer_UI* Create(void);

    HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
    void Init(int nPlayerNum);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void AcquiredItem(CItem *pItem);							// �A�C�e���l���֐�
    void UseItem(void);											// �A�C�e���̎g�p����

    // Set�֐�

    // Get�֐�

    int GetItemNum(void) { return m_apItem.size(); }			// �A�C�e���̃T�C�Y
    CItem *GetItem(void) { return m_apItem[0]; }				// �A�C�e���̃|�C���^
private:
    std::vector<CItem*> m_apItem;	// �A�C�e���{�b�N�X�̃|�C���^
    CStar_UI *m_pStarUI;     // ���̎擾���ւ̃|�C���^

};
#endif // ! _PLAYER_UI_H_