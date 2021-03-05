//=============================================================================
//
// メッシュフィールドクラス [meshfield.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "meshfield.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMeshField::CMeshField(PRIORITY Priority) : CMesh3d(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// ポリゴン生成
//=============================================================================
CMeshField * CMeshField::Create(void)
{
	// メモリ確保
	CMeshField *pMeshField = new CMeshField;

	// nullchack
	if (pMeshField != NULL)
	{
		// 初期化処理
		pMeshField->Init(ZeroVector3, ZeroVector3);
	}

	return pMeshField;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	// ローカル変数
	int nCount = 0;			// for文用
	int nCntIndex = 0;		// 頂点の生成番号
	int nCntH = 0;			// 縦の頂点カウンタ
	int nCntV = 0;			// 横の頂点カウンタ

	// テクスチャの設定
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();
	BindTexture(pTexture->GetTexture(CTexture::TEXTURE_NUM_FLOOR));

	// 値の初期化
	SetNumVertex((FIELD_WIDTH + 1) * (FIELD_HEIGHT + 1));								// 25
	SetNumIndex((FIELD_WIDTH + 1) * FIELD_HEIGHT * 2 + (FIELD_HEIGHT - 1) * 2);			// 5*(4*2)+3*2	46
	
	SetNumPolygon(FIELD_WIDTH * FIELD_HEIGHT * 2 + (FIELD_HEIGHT - 1) * 4);				// 4*8+3*4	44

	SetOneSize(D3DXVECTOR2(FIELD_WIDTH_SIZE * 2 / FIELD_WIDTH, FIELD_HEIGHT_SIZE * 2 / FIELD_HEIGHT));

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		// バッファ
	LPDIRECT3DINDEXBUFFER9 pIdxBuff;		// バッファの番号

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GetNumVertex(),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	// インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * GetNumIndex(),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIdxBuff,
		NULL);

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntV = 0; nCntV < FIELD_HEIGHT + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < FIELD_WIDTH + 1; nCntH++)
		{
			// 頂点の設定
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].pos = D3DXVECTOR3(-FIELD_WIDTH_SIZE + (nCntH * GetOneSize().x), 0.0f, FIELD_HEIGHT_SIZE - (nCntV * GetOneSize().y));

			// 法線ベクトルの設定
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 色の設定
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[(nCntV * (FIELD_HEIGHT + 1)) + nCntH].tex = D3DXVECTOR2(float(nCntH), float(nCntV));
		}
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// 頂点バッファの設定
	BindVtxBuff(pVtxBuff);

	// インデックスバッファの設定
	WORD *pIdx;

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCount = 0, nCntIndex = 0; nCount < GetNumIndex(); nCount += 2)
	{
		if (((nCount + 2) % (((FIELD_WIDTH + 1) * 2) + 2)) == 0 && nCount != 0)
		{
			// インデックスの設定
			pIdx[nCount] = nCntIndex - 1;

			// インデックスの設定
			pIdx[nCount + 1] = FIELD_WIDTH + nCntIndex + 1;
		}
		else
		{
			// インデックスの設定
			pIdx[nCount] = FIELD_WIDTH + nCntIndex + 1;

			// インデックスの設定
			pIdx[nCount + 1] = nCntIndex;

			nCntIndex++;
		}
	}

	// 頂点データをアンロックする
	pIdxBuff->Unlock();

	BindIdxBuff(pIdxBuff);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshField::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(void)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	D3DXMATRIX mtxWorld;						// ワールドマトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld );

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(
		&mtxRot,
		GetRot().y,
		GetRot().x,
		GetRot().z);

	D3DXMatrixMultiply(
		&mtxWorld,
		&mtxWorld,
		&mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(
		&mtxTrans,
		GetPos().x,
		GetPos().y,
		GetPos().z);

	D3DXMatrixMultiply(
		&mtxWorld,
		&mtxWorld,
		&mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームにバインド
	pDevice->SetIndices(GetIdxBuff());

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// 頂点フォーマットの設定
	pDevice->SetTexture(0, GetTexture());

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, GetNumVertex(), 0, GetNumPolygon());

	// 頂点フォーマットの設定
	pDevice->SetTexture(0, NULL);
}