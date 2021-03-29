//=============================================================================
//
// ゲーム画面のUIヘッダ[game.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _GAME_UI_H_
#define  _GAME_UI_H_
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUi;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame_UI : public CScene
{
    // UIの種類列挙
    typedef enum
    {
        GAME_UI_FREAM=0,    // 枠
        GAME_UI_STAR,       // 現在ポイントアップ中の色
        GAME_UI_POINT_UP,
        GAME_UI_MAX
    }GAME_UI;
    // UIの情報構造体
    typedef struct
    {
        D3DXVECTOR3 pos;                    // 位置
        D3DXVECTOR3 size;                   // 大きさ
        CTexture::TEXTURE_TYPE FileName;     // ファイル名
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
    CUi *m_pUI[GAME_UI_MAX];      // UIへのポインタ
    static const GEME_UI_DATA m_UI_DATA[GAME_UI_MAX];// UIの情報

};
#endif // ! _GAME_UI_H_