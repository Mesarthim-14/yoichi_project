//=============================================================================
//
// �^�C�}�[�w�b�_ [timer.h]
// Author : AYANO KUDO
//
//=============================================================================
#ifndef  _TIMER_H_
#define _TIMER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTimer
{
public:
    CTimer();
    ~CTimer();

    static CTimer* Create(void);

    void Init(void);
    void Uninit(void);
    void Updete(void);

    //�^�C�}�[�̃Z�b�g
    void SetTimer(int nMin) { m_nTimeCount = (nMin * 60); }// �b���̐ݒ�

    // �^�C�}�[�̃Q�b�^
    int GetTimer(void) { return m_nTimeCount; }

    // ���Ԑ؂ꂩ�ǂ���
    bool IsTimeOver(void) { return m_nTimeCount <= 0 ? true : false; }
private:
    int m_nTimeCount;

};
#endif // ! _TIMER_H_
