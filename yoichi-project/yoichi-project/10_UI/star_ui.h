//=============================================================================
//
// 星の取得数UIヘッダ[star_ui.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _STAR_UI_H_
#define _STAR_UI_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAR_NUM (2) // 桁数
#define MAX_PLAYER (4) // プレイヤーの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber2d;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStar_UI : public CScene
{
public:
    CStar_UI();
    ~CStar_UI();

    static CStar_UI* Create(void);

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void SetPosition(int nPlayerNum);
    void SetStarNum(void);

private:
    static const D3DXVECTOR3 m_posUI[MAX_PLAYER_NUM];
    // 2Dポリゴンへのポインタ
    CNumber2d *m_apNumber[STAR_NUM];  // 星の取得数
    int        m_nPlayerNum;          // プレイヤーの番号
};

#endif // ! _STAR_UI_H_
