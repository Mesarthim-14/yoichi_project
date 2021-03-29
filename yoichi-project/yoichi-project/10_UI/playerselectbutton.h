//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	playerselectbutton.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _PLAYER_SELECT_BUTTON_H_
#define _PLAYER_SELECT_BUTTON_H_

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "button.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//マクロ定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#define PLAYER_SELECT_BUTTON D3DXVECTOR3(150.0f,40.0f,0.0f)

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CPlayerSelectButton : public CButton
{
public:

	CPlayerSelectButton();
	~CPlayerSelectButton();

	HRESULT Init(void);

	static CPlayerSelectButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nPlayerNum);

	void Push(void);	//押されたときの処理
	void Select(void);	//選択されたときの処理
	void Unselect(void);	//選択されていないときの処理

private:
	int m_nPlayerNum;	//押された時に設定するプレイヤー人数

};
#endif
