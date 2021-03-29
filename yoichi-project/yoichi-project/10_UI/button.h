//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	button.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _BUTTON_H_
#define _BUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "ui.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CButton : public CUi
{
public:

	typedef enum
	{
		BUTTON_TYPE_NONE = 0,
		BUTTON_TYPE_2P,
		BUTTON_TYPE_3P,
		BUTTON_TYPE_4P,
		BUTTON_TYPE_MAX
	}BUTTON_TYPE;

    CButton();	
    virtual ~CButton();

    HRESULT Init(void);	//初期化処理
    void Uninit(void);	//終了処理
    void Update(void);	//更新処理
    void Draw(void);	//描画処理

    virtual void Push(void)     = 0;	//押されたときの処理
    virtual void Select(void)   = 0;	//選択されたときの処理
    virtual void Unselect(void) = 0;	//選択されていないときの処理

	void SetButtonType(BUTTON_TYPE eButtonType) { m_eButtonType = eButtonType; }
	void SetSelect(bool bSelect) { m_bSelect = bSelect; }

private:
	
	static BUTTON_TYPE m_eSelectingButton;
	BUTTON_TYPE m_eButtonType;
	bool m_bSelect;	//選択されているかどうか
	bool m_bSelectOld;
	
};
#endif
