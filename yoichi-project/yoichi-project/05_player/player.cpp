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

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED					(20.0f)				// �v���C���[�̈ړ���
#define PLAYER_JUMP						(17.0f)				// �W�����v�̏���
#define STICK_SENSITIVITY				(50.0f)				// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED				(0.1f)				// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS					(50.0f)				// ���a�̑傫��
#define PLAYER_PARTS					(22)				// �v���C���[�̃p�[�c��
#define GAME_END_FLAME					(100)				// �Q�[�����I���t���[��
#define PLAYER_FLY_SPEED				(30.0f)				// ��s���̃v���C���[�̈ړ���
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
	m_bFly = false;
	m_bDraw = true;
	m_nEndCounter = 0;
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
	SetWeaponTipNum(PARTS_NUM_COLLISION);									// ����̃p�[�c�ԍ�
	SetWeaponRootNum(PARTS_NUM_ROOT);										// ���̍��{�̃p�[�c�ԍ�

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
	if (m_bFly)
	{
		// ��s����
		Fly();
	}
	else
	{
		// �v���C���[�̈ړ�����
		Walk();

		// �W�����v�̏���
		Jump();
	}
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();				// �L�[�{�[�h�擾
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);					// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();	// �T�E���h�|�C���^�擾
	float fSpeed = GetSpeed();											// ���x�擾
	float fCameraAngle = CGame::GetCamera(m_nNumber)->Get��();			// �J�����p�x�擾
	float fMoveAngle = 0.0f; //�ړ��p�x
	D3DXVECTOR3 rot = GetRot();											// ��]�擾
	D3DXVECTOR3 pos = GetPos();											// ���W�擾
	D3DXMATRIX mtxRot;
	ZeroMemory(&mtxRot, sizeof(mtxRot));

	// ���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f))
	{
		m_bWalk = true;

		DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);		// �W���C�p�b�h�̎擾
		fMoveAngle = atan2f((float)js.lX, -(float)js.lY);

		// �p�x�̐ݒ�
		m_rotDest.y = fCameraAngle + fMoveAngle;
	}
	else
	{
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_A))
		{
			fMoveAngle = D3DXToRadian(-90.0f);
		}
		// �E�Ɉړ�
		if (pKeyboard->GetPress(DIK_D))
		{
			fMoveAngle = D3DXToRadian(90.0f);
		}
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_S))
		{
			fMoveAngle = D3DXToRadian(180.0f);

			// ���������p�̏���
			if (pKeyboard->GetPress(DIK_A))
			{
				fMoveAngle += D3DXToRadian(45.0f);
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				fMoveAngle += D3DXToRadian(-45.0f);
			}
		}
		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_W))
		{
			fMoveAngle = D3DXToRadian(0.0f);

			if(pKeyboard->GetPress(DIK_A))
			{
				fMoveAngle += D3DXToRadian(-45.0f);
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				fMoveAngle += D3DXToRadian(45.0f);
			}
		}
		// �ړ��L�[��������Ă����
		if (pKeyboard->GetPress(DIK_W) || pKeyboard->GetPress(DIK_A) || pKeyboard->GetPress(DIK_S) || pKeyboard->GetPress(DIK_D))
		{
			m_bWalk = true;
		}
		else
		{
			m_bWalk = false;
		}
	}

	if (m_bWalk)
	{	// �����Ă��鎞
		if (!GetJump())
		{
			// �������[�V����
			SetMotion(MOTION_WALK);
		}
		// �ړ�
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, -PLAYER_SPEED);
		fMoveAngle += fCameraAngle;
		m_rotDest.y = fMoveAngle;
		D3DXMatrixRotationY(&mtxRot, fMoveAngle);
		D3DXVec3TransformNormal(&move, &move, &mtxRot);
		pos += move;
	}
	else
	{	// �����Ă��Ȃ���
		// �ʏ탂�[�V����
		SetMotion(MOTION_IDOL);
	}

	// ���W�ݒ�
	SetPos(pos);

}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nNumber)
		|| pKeyboard->GetTrigger(DIK_SPACE))
	{
		if (GetJump())
		{
			m_bFly = true;
		}
		else
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
}

//=============================================================================
// ��s����
//=============================================================================
void CPlayer::Fly(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	D3DXVECTOR3 move = ZeroVector3;
	D3DXMATRIX mtxRot;
	if (pKeyboard->GetPress(DIK_W))
	{
		m_rotDest.x = D3DXToRadian(PLAYER_ROT_SPEED);
	}
	if (pKeyboard->GetPress(DIK_S))
	{
		m_rotDest.x = -D3DXToRadian(PLAYER_ROT_SPEED);
	}
	if (pKeyboard->GetPress(DIK_A))
	{
		move.x -= PLAYER_FLY_SPEED;
	}
	if (pKeyboard->GetPress(DIK_D))
	{
		move.x += PLAYER_FLY_SPEED;
	}

	////�㉺�̊p�x����
	//if (D3DXToDegree(m_rot.x) < -PITCH_LIMIT)
	//{
	//	m_rot.x = D3DXToRadian(-PITCH_LIMIT);
	//}
	//if (D3DXToDegree(m_rot.x) > PITCH_LIMIT)
	//{
	//	m_rot.x = D3DXToRadian(PITCH_LIMIT);
	//}

	m_rotDest.y = CGame::GetCamera(m_nNumber)->Get��();
	//�ړ��ʂ��s��ϊ�
	move += D3DXVECTOR3(0.0f, 0.0f, PLAYER_FLY_SPEED);
	move *= -1;
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotDest.y, m_rotDest.x, m_rotDest.z);
	D3DXVec3TransformNormal(&move, &move, &mtxRot);
	SetPos(GetPos()+move);

	if (pKeyboard->GetTrigger(DIK_SPACE))
	{
		m_bFly = false;
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