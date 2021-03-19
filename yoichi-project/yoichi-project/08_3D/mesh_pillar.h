#ifndef _MESH_PILLAR_H_
#define _MESH_PILLAR_H_
//=====================================================
//
// 柱の生成クラスヘッダー [mesh_pillar.h]
// Author : Konishi Yuuto
//
//=====================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "mesh_3d.h"

//=============================================================================
// 柱メッシュクラス
//=============================================================================
class CMeshPillar : public CMesh3d
{
public:
	CMeshPillar(PRIORITY Priority = PRIORITY_0);				// コンストラクタ
	~CMeshPillar();												// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	static CMeshPillar*Create(D3DXVECTOR3 pos,
		MESH_TYPE MeshNum);										// インスタンス生成

	// Get関数
	D3DXVECTOR3 GetPos(void) { return CSceneBase::GetPos(); }	// 座標情報
private:
};

#endif