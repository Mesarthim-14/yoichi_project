//=============================================================================
//
// ナンバー3Dクラス [number_3d.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "number_3d.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DAMAGE_HEIGHT				(1)			// 高さ
#define DAMAGE_LIFE_NUM				(100)		// ライフ
#define DAMAGE_NUM_GRAVITY			(1.4f)		// 重力
#define DAMAGE_NUM_REFLECT_POWER	(2)			// バウンドの割合
#define DAMAGE_NUM_REFLECT_POWER_Y	(20)		// バウンドの移動量
#define DAMAGE_RAND_MOVE_X			(4)			// 移動量
#define DAMAGE_RAND_MOVE_Y			(30)		// 移動量
#define DAMAGE_RAND_MOVE_Z			(4)			// 移動量

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber3d::CNumber3d(PRIORITY Priority) : CMesh3d(Priority)
{
	D3DXMatrixIdentity(&m_mtxWorld);
	m_bInverse = true;
	m_nLife = 0;
	m_move = ZeroVector3;
	m_nBoundCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber3d::~CNumber3d()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CNumber3d * CNumber3d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNum)
{
	// インスタンス生成
	CNumber3d *pNumber3d = new CNumber3d;
	CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

	// nullcheck
	if (pNumber3d != NULL)
	{		
		// 初期化情報
		pNumber3d->m_nNumber = nNum;																	// 値の代入
		pNumber3d->Init(pos, size);																		// 初期化処理
	//	pNumber3d->BindTexture(pTexture->GetSeparateTexture(CTexture::SEPARATE_TEX_DAMAGE_NUMBER));		// テクスチャの設定
		pNumber3d->m_nLife = DAMAGE_LIFE_NUM;															// ライフの設定
		pNumber3d->RandSetMove();																		// 移動量の設定
	}

	return pNumber3d;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber3d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// Rendererクラスからデバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_3D *pVtx;

	// ローカル変数/
	int nCount = 0;				// for分用
	int nCntIndex = 0;			// 頂点番号設定用
	int nCntH= 0;				// 高さのカウンタ
	int nCntV= 0;				// 横幅のカウンタ
	int nWidth = 0;				// 数字の数
	int nNum[3]{ 0, 0, 0 };		// 桁が入る配列
	int nIndex = 0;				// 桁合わせ用
	int nDigit = 0;				// 桁数を取得
	int nNumber = m_nNumber;	// 現在の値を保持

	// 桁数を求める
	while (nNumber != 0)
	{
		nNumber /= 10;
		nDigit++;
	}

	// 横幅取得
	nWidth = nDigit;

	// 桁の値取得
	for (int nCount = 0, nIndex = nWidth - 1; nCount < nWidth; nCount++, nIndex--)
	{
		nNum[nIndex] = (m_nNumber / (int)(pow(10, nCount))) % 10;
	}

	// ポリゴンの高さ
	int nHeight = DAMAGE_HEIGHT;

	// 値の初期化
	SetNumVertex(((nWidth + 1) * (nHeight + 1)) + (nWidth - 1) * (nHeight + 1));	// 頂点の数
	SetNumIndex(((nWidth + 1)*(nHeight + 1)) + (nWidth - 1) * (nHeight + 1));		// インデックスの数
	SetNumPolygon((nWidth * 2)+ ((nWidth-1) * 2));									// ポリゴン数設定

	// 1ブロックのサイズ
	SetOneSize(D3DXVECTOR2(size.x * 2 / nWidth, size.y * 2 / nHeight));	// 24000/4

	// バッファの宣言
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;
	LPDIRECT3DINDEXBUFFER9 pIdxBuff = NULL;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GetNumVertex(),
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

	// 座標の設定
	SetPos(pos);
	SetSize(size);

	int nWidthNum = (nWidth + 1) + nWidth - 1;	// 横幅の値
	int nOdd = 0;								// 奇数のカウント
	
	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nNumCount = 0, nCntV = 0; nCntV < nHeight + 1; nCntV++)
	{
		for (nCntH = 0; nCntH < nWidthNum; nCntH++)
		{
			if (((nCntV * (nWidthNum)) + nCntH) % 2 == 0 && nCntH != 0)
			{// 0以外の偶数の時、前回と同じ座標に設定する

				// 頂点の設定
				pVtx[(nCntV * (nWidthNum)) + nCntH].pos = pVtx[((nCntV * (nWidthNum)) + nCntH) - 1].pos;

				// テクスチャ座標の設定
				pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10)), float(nCntV * 1.0f));
			}
			else
			{
				// 頂点の設定
				pVtx[(nCntV * (nWidthNum)) + nCntH].pos = D3DXVECTOR3(
					(- (size.x / 2)) + (nOdd * (size.x / nWidth)), ( + size.y / 2) - nCntV*size.y, 0.0f);

				if (nCntH == 0)
				{// 一番左端だった時

					// テクスチャ座標の設定
					pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10)), float(nCntV * 1.0f));
				}
				else if (nCntH == 1)
				{// 1だったとき
					nOdd++;

					// 頂点の設定
					pVtx[(nCntV * (nWidthNum)) + nCntH].pos = D3DXVECTOR3(
						(- (size.x / 2)) + (nOdd * (size.x / nWidth)), (+ size.y / 2) - nCntV*size.y, 0.0f);

					// テクスチャ座標の設定
					pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10) + 0.1f), float(nCntV * 1.0f));

					nNumCount++;

				}
				else
				{
					// 頂点の距離を進める
					nOdd++;

					// 頂点の設定
					pVtx[(nCntV * (nWidthNum)) + nCntH].pos = D3DXVECTOR3(
						(- (size.x / 2)) + (nOdd * (size.x / nWidth)), ( + size.y / 2) - nCntV*size.y, 0.0f);

					// テクスチャ座標の設定
					pVtx[(nCntV * (nWidthNum)) + nCntH].tex = D3DXVECTOR2(float(((float)nNum[nNumCount] / 10)+0.1f), float(nCntV * 1.0f));

					nNumCount++;
				}
			}

			// 法線ベクトルの設定
			pVtx[(nCntV * (nWidthNum)) + nCntH].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 色の設定
			pVtx[(nCntV * (nWidthNum)) + nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		}

		// 左にシフト
		nNumCount = 0;
		nOdd = 0;
	}

	// 頂点データをアンロックする
	pVtxBuff->Unlock();

	// バッファ情報を渡す
	BindVtxBuff(pVtxBuff);

	// インデックスバッファの設定
	WORD *pIdx;

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCount = 0, nCntIndex = 0; nCount < GetNumIndex(); nCount += 2)
	{
		// インデックスの設定
		pIdx[nCount] = nWidthNum - 1 + nCntIndex + 1;

		// インデックスの設定
		pIdx[nCount + 1] = nCntIndex;

		nCntIndex++;
	}

	// 頂点データをアンロックする
	pIdxBuff->Unlock();

	// インデックスバッファを渡す
	BindIdxBuff(pIdxBuff);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNumber3d::Uninit(void)
{
	// リリース
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CNumber3d::Update(void)
{
	// 重力
	Gravity();

	// 座標の設定
	SetPos(D3DXVECTOR3(GetPos().x + m_move.x, GetPos().y + m_move.y, GetPos().z + m_move.z));

	// ライフ
	m_nLife--;

	// 0以下になったら
	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CNumber3d::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用のマトリクス

	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// かぶさらないようにする　(Zバッファ)
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 逆行列
	if (m_bInverse == true)
	{
		// 回転の逆行列の生成
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&m_mtxWorld, NULL,
			&mtxRot);

		m_mtxWorld._41 = 0;
		m_mtxWorld._42 = 0;
		m_mtxWorld._43 = 0;

	}
	else
	{
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	BindMtxWorld(m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームにバインド
	pDevice->SetIndices(GetIdxBuff());

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, GetNumVertex(), 0, GetNumPolygon());

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// かぶさらないようにする　(Zバッファ)
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

//=============================================================================
// 移動量の設定
//=============================================================================
void CNumber3d::RandSetMove(void)
{
	// 乱数
	D3DXVECTOR3 move = D3DXVECTOR3(
		(float)(-rand() % DAMAGE_RAND_MOVE_X - rand() % DAMAGE_RAND_MOVE_X - rand() % DAMAGE_RAND_MOVE_X),
		DAMAGE_RAND_MOVE_Y,
		(float)(-rand() % DAMAGE_RAND_MOVE_Z - rand() % DAMAGE_RAND_MOVE_Z - rand() % DAMAGE_RAND_MOVE_Z));

	// 移動量の設定
	m_move = D3DXVECTOR3(move);
}

//=============================================================================
// 重力
//=============================================================================
void CNumber3d::Gravity(void)
{
	if (GetPos().y > 0.0f)
	{
		// 重力をかける
		m_move.y -= DAMAGE_NUM_GRAVITY;
	}
	else
	{// 地面に付いたときの処理
		m_move.y = 0.0f;
		m_nBoundCounter++;
		m_move.y = (float)DAMAGE_NUM_REFLECT_POWER_Y - m_nBoundCounter*DAMAGE_NUM_REFLECT_POWER;

		// 座標の設定
		SetPos(D3DXVECTOR3(GetPos().x, 0.0f, GetPos().z));
	}

}