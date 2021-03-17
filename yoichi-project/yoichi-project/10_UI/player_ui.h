//=============================================================================
//
// プレイヤーUI管理ヘッダ[player_ui.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _PLAYER_UI_H_
#define _PLAYER_UI_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene2d.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CItem;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer_UI : public CScene2D
{
public:
    CPlayer_UI(PRIORITY Priority = PRIORITY_UI);
    ~CPlayer_UI();

    static CPlayer_UI* Create(void);

    void Init(void);
    void Uninit(void);
    void Update(void);

    void AcquiredItem(CItem *pItem);							// アイテム獲得関数
    void UseItem(void);											// アイテムの使用処理

    // Set関数

    // Get関数

    int GetItemNum(void) { return m_apItem.size(); }			// アイテムのサイズ
    CItem *GetItem(void) { return m_apItem[0]; }				// アイテムのポインタ
private:
    std::vector<CItem*> m_apItem;	// アイテムボックスのポインタ


};
#endif // ! _PLAYER_UI_H_
