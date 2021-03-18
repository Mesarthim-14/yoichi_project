#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
//=====================================================
//
// ビルボードクラスヘッダー [billboard.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "scene_base.h"

//=====================================================
// ビルボードクラス
//=====================================================
class CBillboard : public CSceneBase
{
public:
	CBillboard(PRIORITY Priority = PRIORITY_PARTICLE);			// コンストラクタ
	~CBillboard();												// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理
	
	void InitAnimation(D3DXVECTOR2 TexInfo, int nLoop);			// アニメーション情報初期化
	void UpdateAnimation(void);									// アニメーションの更新
	void UpdateTransparency(void);								// 透明度の更新
	
	// Set関数
	void SetMove(D3DXVECTOR3 move);								// 移動量設定
	void SetSizeBase(D3DXVECTOR3 sizeBase);						// サイズのベース
	void SetGravity(D3DXVECTOR3 gravity);						// 重力の設定
	void SetScale(D3DXVECTOR3 scale);							// 拡大率の設定
	void SetTransparency(float transparency);					// 透明度を減らす量の設定
	void SetLife(int nLife);									// 体力の設定
	void SetAlpha(bool bAlpha);									// アルファテストの設定
	void SetAlphaNum(int nAlphaNum);							// アルファテストの値
	void SetBlend(bool bBlend);									// 加算合成
	void SetUseZBuf(bool bZbuf);								// Zバッファの設定
	
	// Get関数
	D3DXVECTOR3 GetMove(void);					// 移動量情報
	int GetLIfe(void);							// 体力の情報

private:
	D3DXVECTOR3 m_move;							// 移動量
	D3DXVECTOR3 m_sizeBase;						// サイズのベース
	D3DXVECTOR3 m_gravity;						// 重力
	D3DXVECTOR3 m_scale;						// 拡大率
	float m_Transparency;						// 透明度を減らす量
	D3DXMATRIX m_mtxWorld;						// 行列計算用
	int m_nLife;								// 寿命
	int m_nCountAnim;							// アニメーションテクスチャ
	int m_nCountAnimPattern;					// アニメーションのパターン
	int m_nCounterAnim;							// アニメーションのカウンター
	int m_nPatternAnim;							// アニメーションのパターン数
	int m_nLoop;								// ループするか
	int m_nAlphaNum;							// アルファテストの値
	bool m_bUse;								// 使用判定
	bool m_bAlpha;								// アルファテストを使用するか
	bool m_bBlend;								// 加算合成
	bool m_bUseZbuf;							// Zバッファを使うか
};

#endif