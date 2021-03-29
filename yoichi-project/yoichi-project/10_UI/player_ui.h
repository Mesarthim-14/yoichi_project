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
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CItem;
class CStar_UI;
class CFly_UI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer_UI : public CScene
{
public:
    CPlayer_UI(PRIORITY Priority = PRIORITY_UI);
    ~CPlayer_UI();

    static CPlayer_UI* Create(void);

    HRESULT Init(void);
    void Init(int nPlayerNum);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    void AcquiredItem(CItem *pItem);							// アイテム獲得関数
    void UseItem(void);											// アイテムの使用処理
    void ItemErase(void);										// アイテムの削除

    // Set関数

    // Get関数

    int GetItemNum(void) { return m_apItem.size(); }			// アイテムのサイズ
    CItem *GetItem(void) { return m_apItem[0]; }				// アイテムのポインタ
private:
    std::vector<CItem*> m_apItem;	// アイテムボックスのポインタ
    CStar_UI *m_pStarUI;            // 星の取得数へのポインタ
    CFly_UI *m_pFlyUI;              // 飛行時間のUI
};
#endif // ! _PLAYER_UI_H_
