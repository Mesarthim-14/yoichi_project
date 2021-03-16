//=============================================================================
//
// シーン3Dクラス [scene3D.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D(PRIORITY Priority) : CSceneBase(Priority)
{
	m_nCountAnim = 0;								// アニメーションテクスチャ
	m_nCountAnimPattern = 0;						// アニメーションのパターン
	m_nCounterAnim = 0;								// アニメーションのカウンター
	m_nPatternAnim = 0;								// アニメーションのパターン数
	m_nLoop = -1;									// ループするかどうか
	m_nLife = 0;
	m_fScaleNum = 0.0f;								// スケール
	m_nAlphaNum = 0;								// アルファテストの値
	m_bAlpha = false;								// アルファテストのフラグ
	m_bInverse = false;
	m_fAlphaNum = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファ変数の宣言
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	// 変数代入
	SetPos(pos);
	SetSize(size);

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(-(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[1].pos = D3DXVECTOR3(+(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(GetSize().x / 2), -(GetSize().y / 2), -(GetSize().z / 2));
	pVtx[3].pos = D3DXVECTOR3(+(GetSize().x / 2), -(GetSize().y / 2), -(GetSize().z / 2));

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//頂点バッファのアンロック
	pVtxBuff->Unlock();

	// バッファの設定
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	//オブジェクト破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
	// アニメーションの設定がされたとき
	if (m_nPatternAnim != 0)
	{
		// アニメーションを更新する
		UpdateAnimation();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用のマトリクス

	// 色の設定
	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = GetColor();
	material.Diffuse = GetColor();
	material.Ambient.a =  GetColor().a - m_fAlphaNum;
	material.Diffuse.a =  GetColor().a - m_fAlphaNum;

	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// アルファテストを有力化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// アルファテストが有効なら
	if (m_bAlpha == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0xC0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	else
	{
		// アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, m_nAlphaNum);
	}

	// 加算合成
	if (m_bBlend == true)
	{
		// 加算合成を行う
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// aデスティネーションカラー
	}

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bInverse == false)
	{
		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	else
	{
		// 回転の逆行列の生成
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&m_mtxWorld, NULL,
			&mtxRot);

		m_mtxWorld._41 = 0;
		m_mtxWorld._42 = 0;
		m_mtxWorld._43 = 0;
	}

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	// アルファテストが有効でなかったら
	if (m_bAlpha != true)
	{
		// アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	// 加算合成が有効なら
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー
	}

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 移動量
//=============================================================================
void CScene3D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 座標設定(座標更新用)
//=============================================================================
void CScene3D::SetPosision(D3DXVECTOR3 pos)
{
	// 座標設定
	SetPos(pos);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(-(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[1].pos = D3DXVECTOR3(+(GetSize().x / 2), +(GetSize().y / 2), +(GetSize().z / 2));
	pVtx[2].pos = D3DXVECTOR3(-(GetSize().x / 2), -(GetSize().y / 2), -(GetSize().z / 2));
	pVtx[3].pos = D3DXVECTOR3(+(GetSize().x / 2), -(GetSize().y / 2), - (GetSize().z / 2));

	// 頂点バッファをアンロックする
	GetVtxBuff()->Unlock();
}

//=============================================================================
// 色の設定
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	CSceneBase::SetColor(col);

	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//頂点カラーの設定（0～255の数値で設定）
		pVtx[nCount].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	}

	//頂点バッファのアンロック
	GetVtxBuff()->Unlock();
}

//=============================================
// アニメーション情報取得
//=============================================
void CScene3D::InitAnimation(D3DXVECTOR2 TexInfo, int nLoop)
{
	// 値の代入
	m_nPatternAnim = (int)TexInfo.x;
	m_nCounterAnim = (int)TexInfo.y;
	m_nLoop = nLoop;

	// 頂点情報を設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// 頂点バッファをアンロックする
	GetVtxBuff()->Unlock();
}

//=============================================
// アニメーション更新関数
//=============================================
void CScene3D::UpdateAnimation(void)
{
	// 爆発のアニメーションカウントを進めて、パターンを切り替える
	m_nCountAnim++;

	// 頂点情報(テクスチャ座標)の更新
	if (m_nCountAnim >= m_nCounterAnim)	// 爆発の速さ
	{
		// アニメーションのカウントを0にする
		m_nCountAnim = 0;

		// アニメーションのパターンをカウントさせる
		m_nCountAnimPattern++;
	}

	// アニメーションが終わったら
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// 数値を戻しておく
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// 終了処理
			Uninit();
		}
	}
	else
	{
		// 頂点情報を設定
		VERTEX_3D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// 頂点バッファをアンロックする
		GetVtxBuff()->Unlock();
	}
}

//======================================================
// 拡大関数
//======================================================
void CScene3D::ScaleUp(float fScaleUp)
{
	m_fScaleNum += fScaleUp;

	VERTEX_3D*pVtx;	//頂点情報へのポインタ

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-(GetSize().x * m_fScaleNum), +(GetSize().y * m_fScaleNum), +(GetSize().z * m_fScaleNum));
	pVtx[1].pos = D3DXVECTOR3(+(GetSize().x * m_fScaleNum), +(GetSize().y * m_fScaleNum), +(GetSize().z * m_fScaleNum));
	pVtx[2].pos = D3DXVECTOR3(-(GetSize().x * m_fScaleNum), -(GetSize().y * m_fScaleNum), -(GetSize().z * m_fScaleNum));
	pVtx[3].pos = D3DXVECTOR3(+(GetSize().x * m_fScaleNum), -(GetSize().y * m_fScaleNum), -(GetSize().z * m_fScaleNum));

	//頂点データをアンロック
	GetVtxBuff()->Unlock();
}

//=============================================================================
// 透明度の減算
//=============================================================================
void CScene3D::SubAlpha(float fAlphaNum)
{
	m_fAlphaNum += fAlphaNum;

	VERTEX_3D*pVtx;	//頂点情報へのポインタ

	//頂点データ範囲をロックし、頂点バッファへのポインタを所得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		//頂点カラーの設定（0～255の数値で設定）
		pVtx[nCount].col = D3DXCOLOR(GetColor().r, GetColor().g, GetColor().b, GetColor().a - m_fAlphaNum);
	}

	//頂点データをアンロック
	GetVtxBuff()->Unlock();
}

//=============================================================================
// ライフの設定
//=============================================================================
void CScene3D::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=============================================================================
// 透明
//=============================================================================
void CScene3D::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

//=============================================================================
// アルファテストの値
//=============================================================================
void CScene3D::SetAlphaNum(int nAlphaNum)
{
	m_nAlphaNum = nAlphaNum;
}

//=============================================================================
// 加算合成の設定
//=============================================================================
void CScene3D::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

//=============================================================================
// 逆行列の設定
//=============================================================================
void CScene3D::SetInverse(bool bInverse)
{
	m_bInverse = bInverse;
}