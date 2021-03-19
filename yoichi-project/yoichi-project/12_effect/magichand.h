#ifndef _MAGICHAND_H_
#define _MAGICHAND_H_
//=====================================================
//
// マジックハンドクラスヘッダー [magichand.h]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"

//=====================================================
// マクロ定義
//=====================================================
#define MAGICHAND_DISTANCE	(D3DXVECTOR3(150.0f ,0.0f, 0.0f))	// プレイヤーとの距離

//=====================================================
// パーティクルクラス
//=====================================================
class CMagichand : public CBillboard
{
public:
	CMagichand(PRIORITY Priority = PRIORITY_PARTICLE);		// コンストラクタ
	~CMagichand();											// デストラクタ

	HRESULT Init();	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CMagichand*Create(D3DXVECTOR3 Distance, int nTexInfo, int nPlayerNum);	// インスタンス生成

private:
	int m_nPlayerNum;		// 追従させるプレイヤーの番号
	D3DXVECTOR3 m_Distance; // 距離
};

#endif