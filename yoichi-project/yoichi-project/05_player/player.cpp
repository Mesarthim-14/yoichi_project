//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include <stdio.h>
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "collision.h"
#include "fade.h"
#include "particle.h"
#include "effect_factory.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "character.h"
#include "motion.h"
#include "item.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(20.0f)				// �v���C���[�̈ړ���
#define PLAYER_JUMP						(17.0f)				// �W�����v�̏���
#define STICK_SENSITIVITY				(50.0f)				// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)				// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS					(200.0f)			// ���a�̑傫��
#define PLAYER_PARTS					(22)				// �v���C���[�̃p�[�c��
#define GAME_END_FLAME					(100)				// �Q�[�����I���t���[��

// �G�t�F�N�g�p�[�c
#define BLADE_EFFECT_INTER				(190)				// ���g�̃p�[�e�B�N���̊Ԋu
#define WEAPON_TIP_NUM					(20)				// ����̃p�[�c�ԍ�
#define WEAPON_ROOT_NUM					(21)				// ���̍����̃p�[�c�ԍ�

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nCount)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;

	// �ԍ��̐ݒ�
	pPlayer->m_nNumber = nCount;

	// ����������
	pPlayer->Init(pos, size);

	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = ZeroVector3;
	m_bWalk = false;
	m_bDraw = true;
	m_nEndCounter = 0;
	m_pItem = NULL;
	m_fBaseSpeed = 0.0f;
	m_bArmor = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != NULL)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

	// ����������
	CCharacter::Init(pos, rot);												// ���W�@�p�x
	SetRadius(PLAYER_RADIUS);												// ���a�̐ݒ�
	SetSpeed(PLAYER_SPEED);													// ���x�̐ݒ�

	m_fBaseSpeed = PLAYER_SPEED;		// ���̃X�s�[�h�ێ�

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{	
	// �I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �e�N���X�̍X�V����
	CCharacter::Update();

	// ���W���
	D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
	SetPosOld(pos);				// �Â����W�ۑ�

	// �v���C���[�̏��
	UpdateState();

	// ���[�V�������
	UpdateMotionState();

	// �v���C���[�̐���
	PlayerControl();

	// �A�C�e�����g���Ă�����
	if (m_pItem != nullptr)
	{
		// �A�C�e���̍폜�t���O����������
		if (m_pItem->GetEnd() == true)
		{
			m_pItem->Uninit();
			m_pItem = nullptr;
		}
	}

	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	// �p�x�̐ݒ�
	SetRot(rot);

	// �}�b�v�̐���
	MapLimit();

	// �̗͂�0�ɂȂ�����
	if (GetLife() <= 0)
	{
		// ���񂾂Ƃ�
		Death();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �`�揈��
	CCharacter::Draw();
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::UpdateState(void)
{
	switch (GetState())
	{
	case STATE_NORMAL:
		// �ʏ���

		break;

	case STATE_DAMAGE:
		break;
	}
}

//=============================================================================
// ���[�V�������
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotion()->GetMotionState();

	// ���[�V�������
	switch (MotionState)
	{
	case 0:
		break;
	default:
		break;
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	// �v���C���[�̈ړ�����
	Walk();

	// �W�����v�̏���
	Jump();

	// �A�C�e���̎g�p
	UseItem();
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// �L�[�{�[�h�X�V
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);				// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// �J�����p�x�擾
	float fAngle = CGame::GetCamera(m_nNumber)->Get��();
	D3DXVECTOR3 pos = GetPos();

	//���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		//�_���[�W���󂯂Ă��Ȃ��Ƃ��݈̂ړ�����
		bool bJump = GetJump();

		//�W�����v���Ă��Ȃ��Ƃ�
		if (bJump == false)
		{
			// ������Ԃɂ���
			m_bWalk = true;

			//���s���[�V�����̍Đ�
			SetMotion(MOTION_WALK);
		}

		DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);				// �W���C�p�b�h�̎擾
		float fAngle3 = atan2f((float)js.lX, -(float)js.lY);	// �R���g���[���̊p�x
		float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);	// �R���g���[���̊p�x
		float fAngle = CGame::GetCamera(m_nNumber)->Get��();				// �J�����̊p�x

		// �ړ��ʐݒ�
		pos.x += sinf(fAngle + (fAngle2))* GetSpeed();
		pos.z += cosf(fAngle + (fAngle2))* GetSpeed();

		// �p�x�̐ݒ�
		m_rotDest.y = fAngle + (fAngle3);
	}
	else
	{
		// �����Ă�����
		if (m_bWalk == true)
		{
			//�ҋ@���[�V�������Đ�
			SetMotion(MOTION_IDOL);
			m_bWalk = false;
		}
	}

	// �O�Ɉړ�
	if (pKeyboard->GetPress(DIK_W))
	{
		// �������[�V����
		SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x -= sinf((CGame::GetCamera(m_nNumber)->Get��()))*GetSpeed();
		pos.z -= cosf((CGame::GetCamera(m_nNumber)->Get��()))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Get��();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Get��(), GetRot().z));
	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_S))
	{
		// �������[�V����
		SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x += sinf((CGame::GetCamera(m_nNumber)->Get��()))*GetSpeed();
		pos.z += cosf((CGame::GetCamera(m_nNumber)->Get��()))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Get��();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Get��() + D3DXToRadian(-180.0f), GetRot().z));

	}
	// ���Ɉړ�
	if (pKeyboard->GetPress(DIK_A))
	{
		// �������[�V����
		SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x += sinf((CGame::GetCamera(m_nNumber)->Get��() + D3DXToRadian(90.0f)))*GetSpeed();
		pos.z += cosf((CGame::GetCamera(m_nNumber)->Get��() + D3DXToRadian(90.0f)))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Get��();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Get��() + D3DXToRadian(-90.0f), GetRot().z));

	}
	// �E�Ɉړ�
	if (pKeyboard->GetPress(DIK_D))
	{
		// �������[�V����
		SetMotion(MOTION_WALK);

		// �ړ��ʁE�p�x�̐ݒ�
		pos.x += sinf((CGame::GetCamera(m_nNumber)->Get��() + D3DXToRadian(-90.0f)))*GetSpeed();
		pos.z += cosf((CGame::GetCamera(m_nNumber)->Get��() + D3DXToRadian(-90.0f)))*GetSpeed();
		m_rotDest.y = CGame::GetCamera(m_nNumber)->Get��();
		SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera(m_nNumber)->Get��() + D3DXToRadian(90.0f), GetRot().z));

	}

	// ���W�ݒ�
	SetPos(pos);

	// �Â����W�擾
	D3DXVECTOR3 OldPos = GetOldPos();

	// �����Ă��Ȃ�������
	if (OldPos == pos)
	{
		// �ʏ탂�[�V����
		SetMotion(MOTION_IDOL);
	}
}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nNumber) && GetJump() == false
		|| pKeyboard->GetTrigger(DIK_SPACE) && GetJump() == false)
	{
		// �ړ��ʐݒ�
		D3DXVECTOR3 move = GetMove();
		move.y = PLAYER_JUMP;
		SetMove(move);
		SetJump(true);
		m_bWalk = false;

		//�W�����v���[�V�����̍Đ�
		SetMotion(MOTION_JUMP);
		SetLanding(false);
	}
}

//=============================================================================
// ���񂾂Ƃ��̏���
//=============================================================================
void CPlayer::Death(void)
{
	m_bDraw = false;
}

//=============================================================================
// �͈͊O�ɍs���Ȃ��悤�ɂ��鏈��
//=============================================================================
void CPlayer::MapLimit(void)
{
	//�E
	if (GetPos().x > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(MAP_LIMIT, GetPos().y, GetPos().z));
	}

	//��
	if (GetPos().x <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(-MAP_LIMIT, GetPos().y, GetPos().z));
	}

	//��
	if (GetPos().z > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, MAP_LIMIT));
	}

	//��O
	if (GetPos().z <-MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(GetPos().x, GetPos().y, -MAP_LIMIT));
	}
}

//=============================================================================
// �A�C�e���̎g�p����
//=============================================================================
void CPlayer::UseItem(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nNumber)
		|| pKeyboard->GetTrigger(DIK_I))
	{
		// !nullcheck
		if (m_pItem != nullptr)
		{
			if (m_pItem->GetUse() == false)
			{
				// �A�C�e�����g��
				m_pItem->SetItem();
			}
		}
	}
}

//=============================================================================
// �A�C�e���̃f�[�^��n��
//=============================================================================
void CPlayer::AcquiredItem(CItem *pItem)
{
	// nullcheck
	if (m_pItem == nullptr)
	{
		m_pItem = pItem;
	}
}