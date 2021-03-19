#ifndef _MANAGER_H_
#define _MANAGER_H_
//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//前方宣言
//=============================================================================
class CRenderer;
class CInputKeyboard;
class CFade;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CInputJoypad;
class CScene;
class CResourceManager;

//=============================================================================
//マネージャークラス
//=============================================================================
class CManager
{
public:
	//=========================================================================
	//列挙型定義
	//=========================================================================
	typedef enum
	{
		MODE_TYPE_NONE = 0, 
		MODE_TYPE_TITLE,		// タイトルモード
		MODE_TYPE_TUTORIAL,		// チュートリアル
		MODE_TYPE_GAME,			// ゲームモード
		MODE_TYPE_RESULT,		// リザルトモード
		MODE_TYPE_MAX,
	}MODE_TYPE;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void LoadAll(void);												// 全てのロード処理
	void UnLoadAll(void);											// 全てのアンロード

	// Set関数
	static void SetMode(MODE_TYPE mode);							// モードの設定
	
	// Get関数
	static MODE_TYPE GetMode(void);														// モードの情報
	static CRenderer *GetRenderer(void);												// レンダラー情報
	static CInputKeyboard *GetKeyboard(void);											// キーボード情報
	static CFade *GetFade(void);														// フェード情報
	static CInputJoypad *GetJoypad(void);												// ジョイパッドコントローラの情報
	static CScene *GetScene(void) { return m_pScene; }									// シーン情報
	static CResourceManager *GetResourceManager (void) { return m_pResourceManager; }	// リソースマネージャのポインタ
	static CGame *GetGame(void) { return m_pGame; }										// ゲームクラスのポインタ情報
private:
	static MODE_TYPE m_mode;						// モード
	static CRenderer *m_pRenderer;					// レンダラークラスのポインタ
	static CInputKeyboard *m_pInput;				// インプットクラスのポインタ
	static CFade *m_pFade;							// フェードクラスのポインタ
	static CTitle *m_pTitle;						// タイトルクラスのポインタ
	static CTutorial *m_pTutorial;					// チュートリアルのポインタ
	static CGame *m_pGame;							// ゲームのポインタ
	static CResult *m_pResult;						// リザルトのポインタ
	static CInputJoypad *m_pJoypad;					// ジョイパッドコントローrのポインタ
	static CScene *m_pScene;						// シーンのポインタ
	static CResourceManager *m_pResourceManager;	// リソースマネージャのポインタ
};

#endif