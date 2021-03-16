//=============================================================================
//
// タイマーヘッダ [timer.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _TIMER_H_
#define _TIMER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTimer
{
public:
    CTimer();
    ~CTimer();

    static CTimer* Create(void);

    void Init(void);
    void Uninit(void);
    void Updete(void);

    //タイマーのセット
    void SetTimer(int nMin) { m_nTimeCount = (nMin * 60); }// 秒数の設定

    // タイマーのゲッタ
    int GetTimer(void) { return m_nTimeCount; }

    // 時間切れかどうか
    bool IsTimeOver(void) { return m_nTimeCount <= 0 ? true : false; }
private:
    int m_nTimeCount;

};
#endif // ! _TIMER_H_
