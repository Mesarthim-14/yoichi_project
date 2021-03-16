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
	// �������m��
	for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
	{
		// !nullcheck
		if (m_apItem[nCount] != nullptr)
		{
			// �I������
			m_apItem[nCount]->Uninit();
			m_apItem[nCount] = nullptr;
		}
	}

	// �z�񂪂����
	if (m_apItem.size() != NULL)
	{
		// �z��̃N���A
		m_apItem.clear();
	}

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

	// �������m��
	for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
	{
		// !nullcheck
		if (m_apItem[nCount] != nullptr)
		{
			// �A�C�e���̍폜�t���O����������
			if (m_apItem[nCount]->GetEnd() == true)
			{
				// �z�����ɂ���
				m_apItem.erase(m_apItem.begin() + nCount);
			}
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

	// �A�C�e���̎g�p
	UseItem();
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

	m_rotDest.x = 0.0f;

	// �ړ����͂�����Ă����
	if (pKeyboard->GetPress(DIK_W) || pKeyboard->GetPress(DIK_A) || pKeyboard->GetPress(DIK_S) || pKeyboard->GetPress(DIK_D) || js.lX != 0.0f || js.lY != 0.0f)
	{
		fMoveAngle = InputToAngle();
		m_bWalk = true;
	}
	else
	{
		m_bWalk = false;
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
			m_rotDest.x -= D3DXToRadian(90.0f);
			SetMove(ZeroVector3);
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
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// �L�[�{�[�h���擾
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);		// �W���C�p�b�h���擾
	D3DXVECTOR3 move = ZeroVector3;							// �ړ���
	D3DXMATRIX mtxRot;										// ��]�v�Z�p�s��
	CCamera* pCamera = CGame::GetCamera(m_nNumber);
	// �d�͂𖳌���
	if (GetUseGravity())
	{
		SetUseGravity(false);
	}
	
	//�v���C���[�̏�����Ɉړ�
	move = D3DXVECTOR3(0.0f, PLAYER_FLY_SPEED, 0.0f);

	//�R���g���[���[�̓��͂�ϊ�
	m_rotDest.y += D3DXToRadian(js.lX / 1000);
	m_rotDest.x += D3DXToRadian(js.lY / 1000);

	//�R���g���[���[���͂𗘗p���ăv���C���[�̌�����ϊ�
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotDest.y, m_rotDest.x, m_rotDest.z);
	D3DXVec3TransformNormal(&move, &move, &mtxRot);

	// �ړ��ʂ𑫂�
	SetPos(GetPos() + move);
	
	// ���͂��ꂽ�p�x
	if (pKeyboard->GetTrigger(DIK_SPACE)||CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, m_nNumber))
	{
		m_bFly = false;
		if (!GetUseGravity())
		{
			SetUseGravity(true);
		}
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
	D3DXVECTOR3 pos = GetPos();

	if (pos.x > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(MAP_LIMIT, pos.y, pos.z));
	}
	if (pos.x < -MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(-MAP_LIMIT, pos.y, pos.z));
	}
	if (pos.z > MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, MAP_LIMIT));
	}
	if (pos.z < -MAP_LIMIT)
	{
		SetPos(D3DXVECTOR3(pos.x, pos.y, -MAP_LIMIT));
	}
}

//=============================================================================
// ���͏����p�x�ɕϊ�����
//=============================================================================
float CPlayer::InputToAngle(void)
{
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);					// �W���C�X�e�B�b�N�̎擾
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();				// �L�[�{�[�h�̎擾
	float fInputAngle = NULL;											//�ړ��A���O��
	//�R���g���[���[���͂�����ꍇ
	if (js.lX != 0.0f || js.lY != 0.0f)
	{
		fInputAngle = atan2f((float)js.lX, -(float)js.lY);
	}
	else
	{
		//�L�[�{�[�h���͂��p�x�ɕϊ�
		if (pKeyboard->GetPress(DIK_A))
		{
			fInputAngle = D3DXToRadian(-90.0f);
		}
		if (pKeyboard->GetPress(DIK_D))
		{
			fInputAngle = D3DXToRadian(90.0f);
		}
		if (pKeyboard->GetPress(DIK_S))
		{
			fInputAngle = D3DXToRadian(180.0f);

			// ���������p�̏���
			if (pKeyboard->GetPress(DIK_A))
			{
				fInputAngle += D3DXToRadian(45.0f);
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				fInputAngle += D3DXToRadian(-45.0f);
			}
		}
		if (pKeyboard->GetPress(DIK_W))
		{
			fInputAngle = D3DXToRadian(0.0f);

			if (pKeyboard->GetPress(DIK_A))
			{
				fInputAngle += D3DXToRadian(-45.0f);
			}
			if (pKeyboard->GetPress(DIK_D))
			{
				fInputAngle += D3DXToRadian(45.0f);
			}
		}
	}

	return fInputAngle;
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
		for (unsigned nCount = 0; nCount < m_apItem.size(); nCount++)
		{
			// !nullcheck
			if (m_apItem[nCount] != nullptr)
			{
				if (m_apItem[nCount]->GetUse() == false)
				{
					// �A�C�e�����g��
					m_apItem[nCount]->SetItem();

					break;
				}
			}
		}

	}
}

//=============================================================================
// �A�C�e���̃f�[�^��n��
//=============================================================================
void CPlayer::AcquiredItem(CItem *pItem)
{
	if (m_apItem.size() == 0)
	{
		// �A�C�e���̃|�C���^
		m_apItem.push_back(pItem);
	}
	else if (m_apItem[0] != nullptr)
	{
		// �g���Ă����ԂȂ�
		if (m_apItem[0]->GetUse() == true)
		{
			// �A�C�e���̃|�C���^
			m_apItem.push_back(pItem);
		}
	}
}