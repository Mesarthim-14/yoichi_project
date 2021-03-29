//=============================================================================
//
// ��sUI�w�b�_[Fly.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _FLY_UI_H_
#define  _FLY_UI_H_
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUi;
class CPolygon;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFly_UI : public CScene
{

public:
    CFly_UI();
    ~CFly_UI();

    static CFly_UI* Create(void);

    HRESULT Init(void);
    void Init(int nPlayerNum);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void SetFly(void);                          // ��s
private:
    CUi *m_pUI;      // UI�ւ̃|�C���^
    CPolygon *m_pGauge;   // �Q�[�W�����̃|�C���^

    //static const GEME_UI_DATA m_UI_DATA;// UI�̏��
    int m_nPkayerNum;       // �v���C���[�ԍ�
    static const D3DXVECTOR3 m_UIPos[MAX_PLAYER_NUM];// �v���C���[���Ƃ�UI�̈ʒu
};
#endif // ! _FLY_UI_H_