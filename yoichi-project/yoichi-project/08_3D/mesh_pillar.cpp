//=============================================================================
//
// 柱メッシュクラス [mesh_pillar.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "mesh_pillar.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshPillar::CMeshPillar(PRIORITY Priority) :CMesh3d(Priority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshPillar::~CMeshPillar()
{

}

//=============================================================================
// ポリゴン生成
//=============================================================================
CMeshPillar * CMeshPillar::Create(D3DXVECTOR3 pos, MESH_TYPE MeshNum)
{
	// メモリ確保
	CMeshPillar *pMeshPillar = new CMeshPillar;
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// 初期化処理
	if (pMeshPillar != nullptr)
	{
		pMeshPillar->SetMeshNum(MeshNum);											// メッシュが何角
		pMeshPillar->SetPos(pos);													// 座標設定
		pMeshPillar->Init();															// 初期化
		pMeshPillar->BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));	// テクスチャの設定
	}

	return pMeshPillar;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshPillar::Init(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	// ローカル変数/
	int nCount;
	int nCntIndex;
	int nCntIndex01 = 0;
	int nCntH;
	int nCntV;
	D3DXVECTOR3 pos = GetPos();
	// 頂点の数
	int nWidth = GetMesh3D(GetMeshNum()).CylinderNum.nNumX;
	int nHeight = GetMesh3D(GetMeshNum()).CylinderNum.nNumY;

	// メッシュのサイズ設定
	D3DXVECTOR2 MeshSize = D3DXVECTOR2(GetMesh3D(GetMeshNum()).size.x, GetMesh3D(GetMeshNum()).size.y);

	SetSize(D3DXVECTOR3(MeshSize.x, MeshSize.y, MeshSize.x));	// サイズ
	SetRot(ZeroVector3);										// 角度

	int VertexNum = (nWidth + 1) * (nHeight + 1);

	// 値の初期化
	SetNumVertex(VertexNum);															// 頂点の数

	int nTubeIndexNum = (nWidth + 1) * nHeight * 2 + (nHeight - 1) * 2;				// 筒だけのインデックス
	int nIndexNum = nTubeIndexNum + (nWidth + 2);									// インデックスの数
	SetNumIndex(nIndexNum);															// インデックスの数

	int nPolygonNum = (nWidth * nHeight * 2 + (nHeight - 1) * 4) +4 + nWidth-2;		// ポリゴン数設定
	SetNumPolygon(nPolygonNum); 														// ポリゴン数設定

	// バッファ変数
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = NULL;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VertexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * GetNumIndex(),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIdxBuff,
		NULL);

	D3DXVECTOR3 pos = GetPos();
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < nHeight + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < nWidth + 1; nCntH++)
		{
			// 頂点の設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].pos = D3DXVECTOR3(
				pos.x + MeshSize.x*cosf(D3DXToRadian((360 / (nWidth ))*nCntH)),
				pos.y - (nCntV * MeshSize.y),
				pos.z + MeshSize.x*sinf(D3DXToRadian((360 / (nWidth ))*nCntH)));

			// 法線ベクトルの設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].nor = D3DXVECTOR3(cosf(D3DXToRadian((360 / (nWidth))*nCntH)), 1.0f, sinf(D3DXToRadian((360 / (nWidth))*nCntH)));

			// 色の設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


			// テクスチャ座標の設定
			pVtx[(nCntV * (nWidth + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
		}
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// バッファ情報を渡す
	BindVtxBuff(pVtxBuff);

	// インデックスバッファの設定
	WORD *pIdx;

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCount = 0, nCntIndex = 0; nCount < nTubeIndexNum; nCount += 2)
	{
		if (((nCount + 2) % (((nWidth + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// インデックスの設定
			pIdx[nCount] = nCntIndex - 1;

			// インデックスの設定
			pIdx[nCount + 1] = nWidth + nCntIndex + 1;
		}
		else
		{
			// インデックスの設定
			pIdx[nCount] = nWidth + nCntIndex + 1;

			// インデックスの設定
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}
	}

	VertexNum;

	int nTopNum = nWidth - 1;
	int VertexCount = 0;
	int nNumber = 0;

		// 頂点のカウントが一定以下の場合
		while (VertexCount <= nWidth - 1)
		{
			// 一番最初の縮退ポリゴン生成
			if (nCount == nTubeIndexNum)
			{
				// インデックスの設定
				pIdx[nCount] = nCntIndex;
	
				// インデックスの設定
				pIdx[nCount + 1] = nNumber;
	
				nCount += 2;
			}
			else
			{
				if (VertexCount % 2 == 0)
				{
					// インデックスの設定
					pIdx[nCount] = nNumber;
	
					// 下から数字を上げる
					nNumber++;
				}
				else
				{
					// インデックスの設定
					pIdx[nCount] = nTopNum;
	
					// 下から頂点番号を上げる
					nTopNum--;
				}
	
				// 頂点数を上げる
				VertexCount++;
				nCount++;
			}
		}

	nCount;

	// 頂点データをアンロックする
	pIdxBuff->Unlock();

	// インデックスバッファを渡す
	BindIdxBuff(pIdxBuff);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshPillar::Uninit(void)
{
	// リリースの処理
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshPillar::Update(void)
{
	// 当たり判定
	Collision();
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshPillar::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 色の設定
	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
	material.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pDevice->GetMaterial(&OldMaterial);		// 古いマテリアル取得
	pDevice->SetMaterial(&material);		// マテリアル設定
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// 親クラス描画処理
	CMesh3d::Draw();

	// 古いマテリアルに戻す
	pDevice->SetMaterial(&OldMaterial);
}