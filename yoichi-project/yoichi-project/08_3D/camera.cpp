//=============================================================================
//
// �J�����̏��� [camera.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "keyboard.h"
#include "game.h"
#include "player.h"
#include "joypad.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CAMERA_DEFAULT_FVARTICAL	(D3DXToRadian(75.0f))			// �J�����̏c��]�����l
#define DISTANCE					(1700.0f)						// ���_�`�����_�̋���
#define DISTANCE_FAR_UP				(35.0f)							// �J�����������l
#define HEIGHT_FROM_PLAYER			(200.0f)						// �����_�̍���
#define CAMERA_MIN_FHORIZONTAL		(D3DXToRadian(10.0f))			// �J�����̍ŏ��p
#define CAMERA_MAX_FHORIZONTAL		(D3DXToRadian(170.0f))			// �J�����̍ő�p
#define CAMERA_MIN_HIGHT			(2.0f)							// �J�����̍Œፂ�x
#define STICK_DEADZONE				(50.0f)						// �X�e�B�b�N���x
#define STICK_INPUT_CONVERSION		(D3DXToRadian(2.0f))			// �X�e�B�b�N���͍ő�ω���
#define	ANGLE_FIX_RATE				(0.01f)							// �J���������␳��
#define REVERSE_ANGLE				(D3DXToRadian(180.0f))			// �J�������]�p

//=============================================================================
// static�������錾
//=============================================================================
int CCamera::m_nAllNum = 0;

//=============================================================================
// �C���X�^���X����
//=============================================================================
CCamera * CCamera::Create(int nCount)
{
	// �������m��
	CCamera *pCamera = new CCamera;

	// !nullcheck
	if (pCamera != NULL)
	{
		// ���g�̔ԍ����擾
		pCamera->m_nNumber = nCount;

		// ����������
		pCamera->Init();
	}

	return pCamera;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	//�e�����o�ϐ��̃N���A
	m_posV = ZeroVector3;		// �J�����̍��W
	m_posVDest = ZeroVector3;	// �J�����̍��W�i�ړI�n�j
	m_posR = ZeroVector3;		// �����_
	m_posRDest = ZeroVector3;	// �����_�i�ړI�n�j
	m_posU = ZeroVector3;		// ������x�N�g��
	m_rot = ZeroVector3;		// ����
	m_fDistance = 0.0f;			// ���_�`�����_�̋���
	m_fMove = 0.0f;				// �ړ���
	m_nNumber = ++m_nAllNum;	// �J�����̔ԍ��̐ݒ�
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
	m_nAllNum = 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_fMove = 5.0f;
	m_fDistance = DISTANCE;
	m_fVartical = CAMERA_DEFAULT_FVARTICAL;
	m_fHorizontal = D3DXToRadian(0.0f);											// �����l�G�̂ق�������
	m_posR = D3DXVECTOR3(0.0f, HEIGHT_FROM_PLAYER, 0.0f);						// �����_�ݒ�
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);										// ������x�N�g��
	m_posV.x = m_posR.x + m_fDistance* sinf(m_fVartical) * sinf(m_fHorizontal);	// �J�����ʒuX
	m_posV.y = m_posR.z + m_fDistance* cosf(m_fVartical);						// �J�����ʒuY
	m_posV.z = m_posR.y + m_fDistance* sinf(m_fVartical) * cosf(m_fHorizontal);	// �J�����ʒuZ

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();
	CPlayer* pPlayer = CGame::GetPlayer(m_nNumber);

	// �v���C���[���g���Ă�����
	if (CGame::GetPlayer(m_nNumber) != NULL)
	{
		// �ʏ��Ԃ̃J�����ړ�
		NomalUpdate(pPlayer->GetPos());

		if (pPlayer->GetIsFly())
		{
			FixAngleToPlayerDirection(pPlayer->GetRot());
		}
	}
}

//=============================================================================
// �ʏ��Ԃ̍X�V����
//=============================================================================
void CCamera::NomalUpdate(D3DXVECTOR3 PlayerPos)
{
	//�L�[�{�[�h�N���X���̎擾
	CInputKeyboard *pKeyInput = CManager::GetKeyboard();

	// �W���C�p�b�h�̎擾
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);
	if (js.lZ > STICK_DEADZONE || js.lZ < -STICK_DEADZONE || js.lRz > STICK_DEADZONE || js.lRz < -STICK_DEADZONE)
	{
		if (js.lZ > STICK_DEADZONE || js.lZ < -STICK_DEADZONE)
		{
			m_fHorizontal += js.lZ / (STICK_MAX_VALUE / STICK_INPUT_CONVERSION);
		}
		//���_�i�J�������W�j�̏����
		if (js.lRz > STICK_DEADZONE || js.lRz < -STICK_DEADZONE)
		{
			m_fVartical -= js.lRz / (STICK_MAX_VALUE / STICK_INPUT_CONVERSION);
		}
	}
	else
	{
		//���_�i�J�������W�j�̍�����
		if (pKeyInput->GetPress(DIK_LEFT))
		{
			m_fHorizontal += STICK_INPUT_CONVERSION;
		}
		//���_�i�J�������W�j�̉E����
		if (pKeyInput->GetPress(DIK_RIGHT))
		{
			m_fHorizontal -= STICK_INPUT_CONVERSION;
		}
		//���_�i�J�������W�j�̏����
		if (pKeyInput->GetPress(DIK_UP))
		{
			m_fVartical -= STICK_INPUT_CONVERSION;
		}
		//���_�i�J�������W�j�̉�����
		if (pKeyInput->GetPress(DIK_DOWN))
		{
			m_fVartical += STICK_INPUT_CONVERSION;
		}
	}

	// �c�����̉�]�̐���
	if (m_fVartical > CAMERA_MAX_FHORIZONTAL)
	{
		m_fVartical = CAMERA_MAX_FHORIZONTAL;
	}
	if (m_fVartical < CAMERA_MIN_FHORIZONTAL)
	{
		m_fVartical = CAMERA_MIN_FHORIZONTAL;
	}

	// �J�����̈ʒu�ݒ�
	m_posVDest.x = PlayerPos.x + m_fDistance * sinf(m_fVartical) * sinf(m_fHorizontal);			// �J�����ʒuX�ݒ�
	m_posVDest.y = PlayerPos.y + HEIGHT_FROM_PLAYER + m_fDistance * cosf(m_fVartical);			// �J�����ʒuY�ݒ�
	m_posVDest.z = PlayerPos.z + m_fDistance * sinf(m_fVartical) * cosf(m_fHorizontal);			// �J�����ʒuZ�ݒ�

	m_posRDest = D3DXVECTOR3(PlayerPos.x, PlayerPos.y + HEIGHT_FROM_PLAYER, PlayerPos.z);		//�����_�ݒ�

	//�J����POSY�̉���
	if (m_posVDest.y <= CAMERA_MIN_HIGHT)
	{
		m_posVDest.y = CAMERA_MIN_HIGHT;	//���E�l�ɖ߂�
	}

	//�ݒ�l�̔��f
	m_posV += (m_posVDest - m_posV)*0.1f;
	m_posR += (m_posRDest - m_posR)*0.9f;
}

//=============================================================================
// �J�����̌������v���C���[�̌����ɕ␳����
//=============================================================================
void CCamera::FixAngleToPlayerDirection(D3DXVECTOR3 PlayerRot)
{
	m_fHorizontal += (PlayerRot.y - m_fHorizontal) * ANGLE_FIX_RATE;
	m_fVartical += (PlayerRot.x + REVERSE_ANGLE - m_fVartical) * ANGLE_FIX_RATE;
}

//=============================================================================
//�J�����N���X�̃Z�b�g����
//=============================================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	if (CGame::GetPlayerNum() == 2)
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH/2 / (float)SCREEN_HEIGHT,
			10.0f,
			100000.0f);
	}
	else
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
			10.0f,
			100000.0f);
	}
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//=============================================================================
// �^�[�Q�b�g�̐ݒ�
//=============================================================================
void CCamera::SetTarget(bool Target)
{
	m_bTarget = Target;
}

//=============================================================================
//�J�����̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CCamera::GetposV(void)
{
	return m_posV;
}

//=============================================================================
//�J�����̊p�x�擾����
//=============================================================================
D3DXVECTOR3 CCamera::GetposR(void)
{
	return m_posR;
}

//=============================================================================
//�J�����̃r���[�}�g���b�N�X�擾����
//=============================================================================
D3DXMATRIX CCamera::GetMtxView(void)
{
	return m_mtxView;
}

//=============================================================================
// �ړI�̊p�x
//=============================================================================
D3DXVECTOR3 CCamera::GetposVDest(void)
{
	return m_posVDest;
}

//=============================================================================
//�J�����̃^�[�Q�b�g�t���O�擾����
//=============================================================================
bool CCamera::GetTargetBool(void)
{
	return m_bTarget;
}

//=============================================================================
//�J�����̏c��]�p�擾����
//=============================================================================
float CCamera::GetVartical(void)
{
	return m_fVartical;
}

//=============================================================================
//�J�����̉���]�p�擾����
//=============================================================================
float CCamera::GetHorizontal(void)
{
	return m_fHorizontal;
}