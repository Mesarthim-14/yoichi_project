//================================================
//
// サウンド処理 [sound.h]
// Author : Konishi Yuuto
//
//================================================

#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "xaudio2.h"

//================================================
//クラス宣言
//================================================
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// BGM0
		SOUND_LABEL_BGM_GAME,			// BGM1
		SOUND_LABEL_SE_SLASH,			// 斬撃音
		SOUND_LABEL_SE_STOMP,			// 叩きつけ
		SOUND_LABEL_SE_SWORD_SKILL,		// ソードスキル
		SOUND_LABEL_SE_ROAR_CRY,		// 叫び声
		SOUND_LABEL_SE_ROAR_FIRE,		// 炎

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef enum
	{
		SOUND_LOOP_ON = -1,				//ループする
		SOUND_LOOP_OFF,					//ループしない
	}SOUND_LOOP;

	CSound();							// コンストラクタ
	~CSound();							// デストラクタ

	static CSound *Create(void);		// インスタンス生成
	HRESULT Init(void);			// 初期化処理
	void Uninit(void);					// 終了処理
	HRESULT Play(SOUND_LABEL label);	// サウンド再生
	void Stop(SOUND_LABEL label);		// サウンドストップ
	void Stop(void);					// サウンドストップ

private:
	typedef struct
	{
		char *m_pFilename;																			// ファイル名
		SOUND_LOOP isLoop;																			// ループするかどうか
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	IXAudio2 *m_pXAudio2 = NULL;																	// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;												// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};										// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};														// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};														// オーディオデータサイズ

																									// 各音素材のパラメータ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};

#endif