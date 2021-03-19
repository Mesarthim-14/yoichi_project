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
#include "scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAR_NUM (2) // 星の取得数
#define MAX_PLAYER (4) // プレイヤーの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber2d;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CStar_UI : public CScene2D
{
public:
    CStar_UI();
    ~CStar_UI();

    static CStar_UI* Create(void);

    void Init(void);
    void Uninit(void);
    void Update(void);

    void SetPosition(int nPlayerNum);
private:
    static const D3DXVECTOR3 m_pos[MAX_PLAYER];

    // 2Dポリゴンへのポインタ
    CNumber2d *m_apNumber[STAR_NUM];  // 星の取得数
};

#endif // ! _STAR_UI_H_
