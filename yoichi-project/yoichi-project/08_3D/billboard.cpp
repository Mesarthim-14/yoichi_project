//=====================================================
//
// ビルボードクラス [billboard.cpp]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// コンストラクタ
//=====================================================
CBillboard::CBillboard(PRIORITY Priority) : CSceneBase(Priority)
{
	m_move = ZeroVector3;		// 移動量
	m_sizeBase = ZeroVector3;	// ベースのサイズ
	m_nLife = 0;				// 寿命
	m_bUse = false;				// 使用判定
	m_nCountAnim = 0;;			// アニメーションテクスチャ
	m_nCountAnimPattern = 0;	// アニメーションのパターン
	m_nCounterAnim = 0;			// アニメーションのカウンター
	m_nPatternAnim = 0;			// アニメーションのパターン数
	m_nLoop = -1;				// ループするか
	m_nAlphaNum = 0;			// アルファテストの値
	m_bAlpha = false;			// アルファテストのフラグ
	m_bBlend = false;
	m_move = ZeroVector3;			// 移動量
	m_sizeBase = ZeroVector3;		// ベースのサイズ
	m_gravity = ZeroVector3;		// 重力
	m_scale = ZeroVector3;			// 拡大率
	m_Transparency = 0.0f;			// 透明度を減らす量
	m_nLife = 0;					// 寿命
	m_bUse = false;					// 使用判定
	m_nCountAnim = 0;;				// アニメーションテクスチャ
	m_nCountAnimPattern = 0;		// アニメーションのパターン
	m_nCounterAnim = 0;				// アニメーションのカウンター
	m_nPatternAnim = 0;				// アニメーションのパターン数
	m_nLoop = -1;					// ループするか
	m_nAlphaNum = 0;				// アルファテストの値
	m_bAlpha = false;				// アルファテストのフラグ
	m_bUseZbuf = false;				// Zバッファのフラグ
}

//=====================================================
// デストラクタ
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBillboard::Init(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = NULL;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	// 情報の代入
	D3DXVECTOR3 size = GetSize();
	m_sizeBase = size;

	//頂点バッファをロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(- size.x / 2, + size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ size.x / 2, + size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- size.x / 2, - size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ size.x / 2, - size.y / 2, 0.0f);

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	pVtxBuff->Unlock();

	// バッファの受け渡し
	BindVtxBuff(pVtxBuff);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBillboard::Uninit(void)
{	
	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CBillboard::Update(void)
{
	// 移動量加算
	D3DXVECTOR3 pos = GetPos();

	// 重力計算
	m_move += m_gravity;

	pos += m_move;

	// 座標の設定
	SetPos(pos);

	if (m_scale.x > 0.0f)
	{
		// 拡大率加算
		D3DXVECTOR3 size = GetSize();
		size += m_scale;

		// サイズの設定
		SetSize(size);
	}

	//=====================================================
	// Author : Ito Yogo
	//=====================================================
	// 透明度計算
	if (m_Transparency > 0.0f)
	{
		// 透明度の更新
		UpdateTransparency();
	}
	//=====================================================

	// アニメーションの設定がされたとき
	if (m_nPatternAnim != 0)
	{
		// アニメーションを更新する
		UpdateAnimation();
	}

	// 体力を減らしていく
	m_nLife--;

	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CBillboard::Draw(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 色の設定
	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = GetColor();
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// 光の影響を無くす
	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	// アルファテストを有力化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// Zバッファ
	if (m_bUseZbuf == true)
	{
		// Zバッファを無効化
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	}

	// 加算合成
	if (m_bBlend == true)
	{
		// 加算合成を行う
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// aデスティネーションカラー
	}
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

	//計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// サイズを反映
	D3DXVECTOR3 size = GetSize();
	D3DXMatrixScaling(&mtxScale,
		size.x / m_sizeBase.x,
		size.y / m_sizeBase.y,
		0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	if (GetRot() == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		// 回転の逆行列の生成
		pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
		D3DXMatrixInverse(&mtxRot, NULL,
			&mtxRot);

		mtxRot._41 = 0;
		mtxRot._42 = 0;
		mtxRot._43 = 0;
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	else
	{
		// 向き反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	D3DXVECTOR3 pos = GetPos();
	// 位置を反映、ワールドマトリクス設定、ポリゴン描画
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);


	// ワールドマトリクスの設定 初期化、向き、位置
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャの設定
	pDevice->SetTexture(0, GetTexture());

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// テクスチャをNULL
	pDevice->SetTexture(0, NULL);

	// アルファテストが有効でなかったら
	if (m_bAlpha != true)
	{
		// アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	// 加算合成を行う処理
	if (m_bBlend == true)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー
	}

	// Zバッファ
	if (m_bUseZbuf == true)
	{
		// Zバッファを有効化
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	}

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	pDevice->SetMaterial(&OldMaterial);					// マテリアルを元に戻す

	pDevice->LightEnable(0, TRUE);
}

//=============================================
// アニメーション情報取得
//=============================================
void CBillboard::InitAnimation(D3DXVECTOR2 TexInfo, int nLoop)
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
void CBillboard::UpdateAnimation(void)
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

//=============================================
// 透明度の更新関数
// Author : Ito Yogo
//=============================================
void CBillboard::UpdateTransparency(void)
{
	// 頂点情報を設定
	VERTEX_3D *pVtx = NULL;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// 透明度の設定
	D3DXCOLOR col = GetColor();
	col.a -= m_Transparency;

	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	SetColor(col);

	// 頂点バッファをアンロックする
	GetVtxBuff()->Unlock();
}

//=====================================================
// 移動量設定
//=====================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=====================================================
// ベースサイズ設定
//=====================================================
void CBillboard::SetSizeBase(D3DXVECTOR3 sizeBase)
{
	m_sizeBase = sizeBase;
}

//=====================================================
// 重力設定
//=====================================================
void CBillboard::SetGravity(D3DXVECTOR3 gravity)
{
	m_gravity = gravity;
}

//=====================================================
// 拡大率設定
//=====================================================
void CBillboard::SetScale(D3DXVECTOR3 scale)
{
	m_scale = scale;
}

//=====================================================
// 透明度を減らす量の設定
//=====================================================
void CBillboard::SetTransparency(float transparency)
{
	m_Transparency = transparency;
}

//=====================================================
// 体力の設定
//=====================================================
void CBillboard::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=====================================================
// アルファテストの設定
//=====================================================
void CBillboard::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

//=====================================================
// アルファテストの値
//=====================================================
void CBillboard::SetAlphaNum(int nAlphaNum)
{
	m_nAlphaNum = nAlphaNum;
}

//=====================================================
// 加算合成
//=====================================================
void CBillboard::SetBlend(bool bBlend)
{
	m_bBlend = bBlend;
}

//=====================================================
// Zバッファの設定
//=====================================================
void CBillboard::SetUseZBuf(bool bZbuf)
{
	m_bUseZbuf = bZbuf;
}

//=====================================================
// 移動量情報
//=====================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_move;
}

//=====================================================
// 体力の設定
//=====================================================
int CBillboard::GetLIfe(void)
{
	return m_nLife;
}