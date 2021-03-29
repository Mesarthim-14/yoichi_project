//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	playerselectbutton.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "playerselectbutton.h"
#include "game.h"
#include "texture.h"
#include "manager.h"
#include "resource_manager.h"
#include "fade.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPlayerSelectButton::CPlayerSelectButton()
{
	m_nPlayerNum = 0;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPlayerSelectButton::~CPlayerSelectButton()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CPlayerSelectButton::Init(void)
{
	CTexture *pTexture = GET_TEXTURE_PTR;
	CButton::Init();
	BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)(CTexture::TEXTURE_NUM_BUTTON_2P - MIN_PLAYER_NUM + m_nPlayerNum)));
	SetButtonType((BUTTON_TYPE)(BUTTON_TYPE_2P + m_nPlayerNum - MIN_PLAYER_NUM));
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//生成処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CPlayerSelectButton* CPlayerSelectButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size , const int nPlayerNum)
{
	CPlayerSelectButton* pPlayerSelectButton = new CPlayerSelectButton;
	pPlayerSelectButton->SetPos(pos);
	pPlayerSelectButton->SetSize(size);
	pPlayerSelectButton->m_nPlayerNum = nPlayerNum;
	pPlayerSelectButton->Init();
	return pPlayerSelectButton;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//押されたときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayerSelectButton::Push(void)
{
	CFade* pFade = CManager::GetFade();
	if (pFade->GetFade() == CFade::FADE_MODE_NONE)
	{
		CGame::SetPlayerNum(m_nPlayerNum);
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されているときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayerSelectButton::Select(void)
{
	SetCol(D3DXCOLOR(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)));
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//選択されていないときの処理
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CPlayerSelectButton::Unselect(void)
{
	SetCol(D3DXCOLOR(0.5f,0.5f,0.5f,1.0f));
}