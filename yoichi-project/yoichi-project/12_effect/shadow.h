#ifndef _SHADOW_H_
#define _SHADOW_H_
//=====================================================
//
// シャドウクラスヘッダー [shadow.h]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"

//=====================================================
// パーティクルクラス
//=====================================================
class CShadow : public CBillboard
{
public:
	CShadow(PRIORITY Priority = PRIORITY_PARTICLE);		// コンストラクタ
	~CShadow();											// デストラクタ

	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	static CShadow*Create(int nTexInfo, int nPlayerNum);	// インスタンス生成

private:
	int m_nPlayerNum;		// 追従させるプレイヤーの番号
};

#endif