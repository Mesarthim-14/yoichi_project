//=============================================================================
//
// 飛行UIヘッダ[Fly.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _FLY_UI_H_
#define  _FLY_UI_H_
#include "scene.h"
#include "texture.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUi;
class CPolygon;

//*****************************************************************************
// クラス定義
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

    void SetFly(void);                          // 飛行
private:
    CUi *m_pUI;      // UIへのポインタ
    CPolygon *m_pGauge;   // ゲージ部分のポインタ

    //static const GEME_UI_DATA m_UI_DATA;// UIの情報
    int m_nPkayerNum;       // プレイヤー番号
    static const D3DXVECTOR3 m_UIPos[MAX_PLAYER_NUM];// プレイヤーごとのUIの位置
};
#endif // ! _FLY_UI_H_