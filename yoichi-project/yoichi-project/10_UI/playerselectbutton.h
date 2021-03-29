//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	playerselectbutton.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _PLAYER_SELECT_BUTTON_H_
#define _PLAYER_SELECT_BUTTON_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "button.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�}�N����`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#define PLAYER_SELECT_BUTTON D3DXVECTOR3(150.0f,40.0f,0.0f)

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CPlayerSelectButton : public CButton
{
public:

	CPlayerSelectButton();
	~CPlayerSelectButton();

	HRESULT Init(void);

	static CPlayerSelectButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const int nPlayerNum);

	void Push(void);	//�����ꂽ�Ƃ��̏���
	void Select(void);	//�I�����ꂽ�Ƃ��̏���
	void Unselect(void);	//�I������Ă��Ȃ��Ƃ��̏���

private:
	int m_nPlayerNum;	//�����ꂽ���ɐݒ肷��v���C���[�l��

};
#endif
