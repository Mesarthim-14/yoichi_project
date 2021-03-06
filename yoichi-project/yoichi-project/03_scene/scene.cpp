//=============================================================================
//
// シーンクラス処理 [scene.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"
#include "game.h"
#include "camera.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CScene * CScene::m_pTop[CScene::PRIORITY_MAX] = {};
CScene * CScene::m_pCur[CScene::PRIORITY_MAX] = {};
bool CScene::m_bPause = false;

//=============================================================================
//オブジェクトクラスのデフォルトコンストラクタ
//=============================================================================
CScene::CScene(PRIORITY Priority)
{
	//プライオリティの設定
	m_nPriority = Priority;

	//死亡フラグをfalseに設定する
	m_bDeath = false;

	//先頭オブジェクトが確保されていないとき
	if (!m_pTop[m_nPriority])
	{
		//先頭オブジェクトに自身のポインタを設定する
		m_pTop[m_nPriority] = this;

		//先頭のため、前情報をNULLでクリアする
		m_pPrev = NULL;
	}

	//現在オブジェクトが確保されていなかった場合
	if (!m_pCur[m_nPriority])
	{
		//現在オブジェクトへ自身のポインタを設定
		m_pCur[m_nPriority] = this;
	}

	//現在オブジェクトの次のオブジェクト情報に自分の情報を入れる
	m_pCur[m_nPriority]->m_pNext = this;

	//現在オブジェクトが自分だった場合
	if (m_pCur[m_nPriority] == this)
	{
		//前情報にNULLを入れる
		m_pPrev = NULL;
	}
	else
	{
		//前情報に現在オブジェクトを入れる
		m_pPrev = m_pCur[m_nPriority];
	}

	//現在オブジェクトに自身のポインタ情報に上書きする
	m_pCur[m_nPriority] = this;

	//自身の次情報をクリアする
	m_pNext = NULL;

}

//=============================================================================
//オブジェクトクラスのデフォルトデストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//全ての更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	//ポーズしているか　bool pause = m_pause   ->>  pause =true ->> if (type == OBJTYPE_PAUSE)
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			// 先頭シーン
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				// 次のシーンを取得
				CScene *pSceneCur = pScene->m_pNext;

				// 死亡フラグがないとき
				if (pScene->m_bDeath != true)
				{
					// 更新処理
					pScene->Update();
				}

				// 次のシーンへ
				pScene = pSceneCur;
			} 
		}
	}

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		// !nullcheck
		if (m_pTop[nCount] != NULL)
		{
			// 先頭のシーンを確保
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				CScene *pSceneCur = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					// 死亡フラグの処理
					pScene->DeathRelease();
				}

				// 次のシーンへ
				pScene = pSceneCur;
			} 
		}
	}
}

//=============================================================================
//UI以外の描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		// !nullcheck
		if (m_pTop[nCount] != NULL)
		{
			// 先頭を取得
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				// 次のシーン取得
				CScene *pSceneCur = pScene->m_pNext;

				// 死亡フラグがない時
				if (pScene->m_bDeath != true && pScene->m_nPriority != PRIORITY_UI)
				{
					pScene->Draw();
				}

				// 次のシーンへ
				pScene = pSceneCur;
			} 
		}
	}
}

void CScene::DrawUI(void)
{
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		// !nullcheck
		if (m_pTop[nCount] != NULL)
		{
			// 先頭を取得
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				// 次のシーン取得
				CScene *pSceneCur = pScene->m_pNext;

				// 死亡フラグがない時
				if (pScene->m_bDeath != true && pScene->m_nPriority == PRIORITY_UI)
				{
					pScene->Draw();
				}

				// 次のシーンへ
				pScene = pSceneCur;
			}
		}
	}
}

//=============================================================================
//全ての終了処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		// 先頭を取得
		CScene *pScene = m_pTop[nCount];

		while (pScene != NULL)
		{
			// 次のシーン取得
			CScene *pCurScene = pScene->m_pNext;

			// シーンの終了処理
			pScene->Uninit();

			// 次のシーンへ
			pScene = pCurScene;
		}
	}

	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		// !nullcheck
		if (m_pTop[nCount] != NULL)
		{
			// 先頭のシーン
			CScene *pScene = m_pTop[nCount];

			while (pScene != NULL)
			{
				// 次のシーン取得
				CScene *pSceneCur = pScene->m_pNext;

				// 死亡フラグがあったら
				if (pScene->m_bDeath == true)
				{
					// 死亡フラグの処理
					pScene->DeathRelease();
				}

				// 次のシーンへ
				pScene = pSceneCur;
			}
		}
	}
}

//=============================================================================
// 単数リリース
//=============================================================================
void CScene::Release(void)
{
	// 死亡フラグ
	m_bDeath = true;
}

//=============================================================================
// 死亡フラグを持ったやつのリリース
//=============================================================================
void CScene::DeathRelease(void)
{
	// 位置をずらす
	for (int nCount = 0; nCount < PRIORITY_MAX; nCount++)
	{
		// 先頭だったら
		if (m_pTop[nCount] == this)
		{
			// 先頭を次のオブジェクトにする
			m_pTop[nCount] = m_pNext;
		}

		// 最後だったら
		if (m_pCur[nCount] == this)
		{
			// 最後をその前のオブジェクトにする
			m_pCur[nCount] = m_pPrev;
		}

		// 前後のシーンを繋げる処理
		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	// 自身をdelete
	delete this;
}

//=============================================================================
//先頭情報の取得処理
//=============================================================================
CScene * CScene::GetTop(int nNum)
{
	return m_pTop[nNum];
}


//=============================================================================
// 次のシーン情報
//=============================================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
//ポーズ情報の取得
//=============================================================================
void CScene::SetPause(bool Pause)
{
	m_bPause = Pause;
}