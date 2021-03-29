//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	button.h
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#ifndef _BUTTON_H_
#define _BUTTON_H_

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "ui.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�N���X��`
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
class CButton : public CUi
{
public:

	typedef enum
	{
		BUTTON_TYPE_NONE = 0,
		BUTTON_TYPE_2P,
		BUTTON_TYPE_3P,
		BUTTON_TYPE_4P,
		BUTTON_TYPE_MAX
	}BUTTON_TYPE;

    CButton();	
    virtual ~CButton();

    HRESULT Init(void);	//����������
    void Uninit(void);	//�I������
    void Update(void);	//�X�V����
    void Draw(void);	//�`�揈��

    virtual void Push(void)     = 0;	//�����ꂽ�Ƃ��̏���
    virtual void Select(void)   = 0;	//�I�����ꂽ�Ƃ��̏���
    virtual void Unselect(void) = 0;	//�I������Ă��Ȃ��Ƃ��̏���

	void SetButtonType(BUTTON_TYPE eButtonType) { m_eButtonType = eButtonType; }
	void SetSelect(bool bSelect) { m_bSelect = bSelect; }

private:
	
	static BUTTON_TYPE m_eSelectingButton;
	BUTTON_TYPE m_eButtonType;
	bool m_bSelect;	//�I������Ă��邩�ǂ���
	bool m_bSelectOld;
	
};
#endif
