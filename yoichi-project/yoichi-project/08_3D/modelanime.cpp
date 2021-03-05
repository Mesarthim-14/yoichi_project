//=============================================================================
//
// 階層構造用のモデルクラス処理 [modelanime.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "modelanime.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//階層モデルクラスのコンストラクタ
//=============================================================================
CModelAnime::CModelAnime()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));

	//各メンバ変数のクリア
	memset(&m_model, 0, sizeof(m_model));
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotAnime = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
}

//=============================================================================
//階層モデルクラスのデストラクタ
//=============================================================================
CModelAnime::~CModelAnime()
{
}

//=============================================================================
//階層モデルクラスのクリエイト処理
//=============================================================================
CModelAnime * CModelAnime::Create(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//階層モデルクラスのポインタ変数
	CModelAnime *pModelAnime = NULL;

	//インスタンス生成
	pModelAnime = new CModelAnime;

	// nullcheck
	if (pModelAnime != NULL)
	{
		//初期化処理呼び出し
		pModelAnime->Init(xfilename, pos, rot);
	}
	//失敗していた場合
	else
	{
		return NULL;
	}

	return pModelAnime;
}

//=============================================================================
//階層モデルクラスの初期化処理
//=============================================================================
HRESULT CModelAnime::Init(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//モデルの読み込み
	D3DXLoadMeshFromX(xfilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_model.pBuffMat,
		NULL,
		&m_model.dwNumMat,
		&m_model.pMesh);

	//マテリアル情報の解析
	D3DXMATERIAL *materials = (D3DXMATERIAL*)m_model.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_model.dwNumMat; nCntMat++)
	{
		if (materials[nCntMat].pTextureFilename != NULL)
		{
			// ファイルネームの取得
			char cData[256] = {};

			sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, cData, &m_apTexture[nCntMat]);
		}
	}

	//位置の設定
	m_pos = pos;

	//向きの設定
	m_rot = rot;

	return S_OK;
}

//=============================================================================
//階層モデルクラスの終了処理
//=============================================================================
void CModelAnime::Uninit(void)
{
	//マテリアル情報の破棄
	if (m_model.pBuffMat != NULL)
	{
		m_model.pBuffMat->Release();
		m_model.pBuffMat = nullptr;
	}

	//メッシュ情報の破棄
	if (m_model.pMesh != NULL)
	{
		m_model.pMesh->Release();
		m_model.pMesh = nullptr;
	}
}

//=============================================================================
//階層モデルクラスの更新処理
//=============================================================================
void CModelAnime::Update(void)
{
}

//=============================================================================
//階層モデルクラスの描画処理
//=============================================================================
void CModelAnime::Draw(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;
	D3DMATERIAL9 matDef;	//現在のマテリアル保持用
	D3DXMATERIAL*pMat;		//マテリアルデータへのポインタ

	// 剣の軌跡の古いデータ
	m_OldMtxWorld1[4] = m_OldMtxWorld1[3];
	m_OldMtxWorld1[3] = m_OldMtxWorld1[2];
	m_OldMtxWorld1[2] = m_OldMtxWorld1[1];
	m_OldMtxWorld1[1] = m_OldMtxWorld1[0];
	m_OldMtxWorld1[0] = m_OldMtxWorld;
	m_OldMtxWorld = m_mtxWorld;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//アニメーションの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotAnime.y, m_rotAnime.x, m_rotAnime.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//アニメーションの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_posAnime.x, m_posAnime.y, m_posAnime.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//親が存在する場合
	if (m_pParent != NULL)
	{
		//親情報を設定
		mtxParent = m_pParent->GetMtxWorld();
	}
	//親が存在しない場合
	else
	{
		//デバイス情報を設定
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//親のマトリクスと掛け合わせる
	m_mtxWorld *= mtxParent;

	//ワールドマトリクスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得する
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_model.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_model.dwNumMat; nCntMat++)
	{
		//マテリアルのアンビエントにディフューズカラーを設定
		pMat[nCntMat].MatD3D.Ambient = pMat[nCntMat].MatD3D.Diffuse;

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_apTexture[nCntMat] != NULL)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_apTexture[nCntMat]);
		}
		else
		{
			// テクスチャ設定
			pDevice->SetTexture(0, NULL);
		}

		//モデルパーツの描画
		m_model.pMesh->DrawSubset(nCntMat);

		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
//階層モデルクラスの親情報の設定処理
//=============================================================================
void CModelAnime::SetParent(CModelAnime * pParent)
{
	m_pParent = pParent;
}

//=============================================================================
//階層モデルクラスの位置設定処理
//=============================================================================
void CModelAnime::SetPosAnime(const D3DXVECTOR3 posAnime)
{
	m_posAnime = posAnime;
}

//=============================================================================
//階層モデルクラスの位置取得処理
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPos(void) const
{
	return m_pos;
}

//=============================================================================
//階層モデルクラスのアニメーション位置の取得
//=============================================================================
D3DXVECTOR3 CModelAnime::GetPosAnime(void) const
{
	return m_posAnime;
}

//=============================================================================
//階層モデルクラスの向きの設定処理
//=============================================================================
void CModelAnime::SetRotAnime(const D3DXVECTOR3 rotAnime)
{
	m_rotAnime = rotAnime;
}

//=============================================================================
//階層モデルクラスの向きの取得処理
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRot(void) const
{
	return m_rot;
}

//=============================================================================
//階層モデルクラスのアニメーション向きの取得
//=============================================================================
D3DXVECTOR3 CModelAnime::GetRotAnime(void) const
{
	return m_rotAnime;
}

//=============================================================================
//階層モデルクラスのマトリクス情報の取得処理
//=============================================================================
D3DXMATRIX CModelAnime::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// 古い座標の情報
//=============================================================================
D3DXMATRIX CModelAnime::GetOldMtxWorld(void)
{
	return m_OldMtxWorld;
}