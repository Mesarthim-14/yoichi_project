//=============================================================================
//
// �Q�[����ʂ�UI�w�b�_[game.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _GAME_UI_H_
#define  _GAME_UI_H_
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUi;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGame_UI : public CScene
{
    // UI�̎�ޗ�
    typedef enum
    {
        GAME_UI_FREAM=0,    // �g
        GAME_UI_STAR,       // ���݃|�C���g�A�b�v���̐F
        GAME_UI_POINT_UP,
        GAME_UI_MAX
    }GAME_UI;
    // UI�̏��\����
    typedef struct
    {
        D3DXVECTOR3 pos;                    // �ʒu
        D3DXVECTOR3 size;                   // �傫��
        CTexture::TEXTURE_TYPE FileName;     // �t�@�C����
    }GEME_UI_DATA;

public:
    CGame_UI();
    ~CGame_UI();

    static CGame_UI* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void SetColor(void);
private:
    CUi *m_pUI[GAME_UI_MAX];      // UI�ւ̃|�C���^
    static const GEME_UI_DATA m_UI_DATA[GAME_UI_MAX];// UI�̏��

};
#endif // ! _GAME_UI_H_