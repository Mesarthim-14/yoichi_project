#ifndef _GAMEMODE_H_
#define _GAMEMODE_H_
//=============================================================================
//
// ゲームモードのインターフェースクラス [gamemode.h]
// Author : Yuuki Ikeda
//
//=============================================================================

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "main.h"

//***************************************************************************************
// ゲームクラス
//***************************************************************************************
class ICGameMode
{
public:
	virtual ~ICGameMode() {};										// デストラクタ

	virtual HRESULT Init(void) = 0;										// 初期化処理
	virtual void Uninit(void) = 0;									// 終了処理
	virtual void Update(void) = 0;									// 更新処理
	virtual void Draw(void) = 0;									// 描画処理
};
#endif