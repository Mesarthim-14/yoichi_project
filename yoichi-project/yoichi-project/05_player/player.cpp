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
#include "effect.h"
#include "effect_factory.h"
#include "texture.h"
#include "resource_manager.h"
#include "xfile.h"
#include "character.h"
#include "motion.h"
#include "wind.h"
#include "barrier.h"
#include "barrier_effect.h"
#include "magichand.h"

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

	//// �d��̃G�t�F�N�g
	//CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
	//	GetModelAnime(21)->GetMtxWorld()._42,
	//	GetModelAnime(21)->GetMtxWorld()._43),
	//	CEffectFactory::EFFECT_TYPE::EFFECT_NUM_SINKER);

	// �����Ƃ�ꂽ�Ƃ��̃G�t�F�N�g
	CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
		GetModelAnime(21)->GetMtxWorld()._42,
		GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_KIRAKIRA);
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
		SetMotion(4);
		SetLanding(false);
	}

	//=============================================================================
	// Author : Ito Yogo
	//=============================================================================
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, m_nNumber) && GetJump() == false)
	{
		// ���̃A�C�e�����g��ꂽ�Ƃ��̃G�t�F�N�g
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_THUNDER);

		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(0.0f, 500.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_LIGHTNINGSTRIKE);
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_Y, m_nNumber) && GetJump() == false)
	{
		// �����Ƃ�ꂽ�Ƃ��̃G�t�F�N�g
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STAR);
		//CEffectFactory::CreateEffect(GetPos()/* + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f)*/, CEffectFactory::EFFECT_TYPE::EFFECT_NUM_SHOCKWAVE);
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, m_nNumber) && GetJump() == false)
	{
		// ���x�����������̃G�t�F�N�g
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
			CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSDOWN);

		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
			CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSDOWNPARTICLE);

	}
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, m_nNumber) && GetJump() == false)
	{
		// ���x���オ�������̃G�t�F�N�g
		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
			CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATUSUP);

		CEffectFactory::CreateEffect(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43) + D3DXVECTOR3(sinf(GetRot().y) * -300.0f, 0.0f, cosf(GetRot().y) * -300.0f),
			CEffectFactory::EFFECT_TYPE::EFFECT_NUM_STATESUPPARTICLE);
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L2_TRIGGER, m_nNumber) && GetJump() == false)
	{
		// �����̃G�t�F�N�g
		CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSION);
		CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSIONCIRCLE);
		CEffectFactory::CreateEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEffectFactory::EFFECT_TYPE::EFFECT_NUM_EXPLOSIONSPARK);
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R2_TRIGGER, m_nNumber) && GetJump() == false)
	{
		// ���̃A�C�e���̃G�t�F�N�g
		CWind::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), 
			ZeroVector3, 10.0f, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_nNumber);

		CWind::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43), 
			ZeroVector3, 10.0f, D3DXVECTOR3(10.0f, 10.0f, 10.0f), m_nNumber);
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R3, m_nNumber) && GetJump() == false)
	{
		// �o���A�̃G�t�F�N�g
		CBARRIER::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
			GetModelAnime(21)->GetMtxWorld()._42,
			GetModelAnime(21)->GetMtxWorld()._43),
			D3DXVECTOR3(50.0f, 50.0f, 50.0f), 10.0f, D3DXVECTOR3(5.0f, 5.0f, 5.0f), m_nNumber);
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L3, m_nNumber) && GetJump() == false)
	{
		for (int nCount = 0; nCount < 100; nCount++)
		{
			// �o���A���󂳂ꂽ�Ƃ��̃G�t�F�N�g
			CBARRIEREFFECT::Create(D3DXVECTOR3(GetModelAnime(21)->GetMtxWorld()._41,
				GetModelAnime(21)->GetMtxWorld()._42,
				GetModelAnime(21)->GetMtxWorld()._43),
				D3DXVECTOR3(50.0f, 50.0f, 50.0f), D3DXVECTOR3(30.0f, 30.0f, 30.0f), 10.0f);
		}
	}

	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, m_nNumber) && GetJump() == false)
	{
		// �}�W�b�N�n���h�̃G�t�F�N�g
		CMagichand::Create(-MAGICHAND_DISTANCE, CTexture::SEPARATE_TEX_MAGICHANDLEFT, m_nNumber);
		CMagichand::Create(MAGICHAND_DISTANCE, CTexture::SEPARATE_TEX_MAGICHANDRIGHT, m_nNumber);
	}
	//=============================================================================
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