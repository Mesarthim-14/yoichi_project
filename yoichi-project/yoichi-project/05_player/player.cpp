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
#include "item.h"
#include "stage_map.h"
#include "mesh_pillar.h"
#include "wind.h"
#include "barrier.h"
#include "barrier_effect.h"
#include "magichand.h"
#include "player_ui.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED				(20.0f)					// �v���C���[�̈ړ���
#define PLAYER_JUMP				(17.0f)					// �W�����v�̏���
#define STICK_DEADZONE			(50.0f)					// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED			(0.1f)					// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS			(200.0f)					// 4���a�̑傫��
#define PLAYER_PARTS				(22)						// �v���C���[�̃p�[�c��
#define GAME_END_FLAME			(100)					// �Q�[�����I���t���[��
#define PLAYER_FLY_SPEED			(30.0f)					// ��s���̃v���C���[�̈ړ���
#define FLY_ROT_X_MAX			(-D3DXToRadian(10.0f))	// ��s�̍ő�p
#define FLY_ROT_X_MIN			(-D3DXToRadian(170.0f))	// ��s�̍ŏ��p
#define FLY_GRAVITY_RATE		(0.5f)					// ��s���̏d��
// �G�t�F�N�g�p�[�c
#define BLADE_EFFECT_INTER		(190)					// ���g�̃p�[�e�B�N���̊Ԋu
#define WEAPON_TIP_NUM			(20)					// ����̃p�[�c�ԍ�
#define WEAPON_ROOT_NUM			(21)					// ���̍����̃p�[�c�ԍ�

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nCount)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;

	// �ԍ��̐ݒ�
	pPlayer->m_nNumber = nCount;


	pPlayer->SetPos(pos);
	pPlayer->SetRot(rot);
	// ����������
	pPlayer->Init();
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
	m_bStickReverseVartical = false;
	m_bDraw = true;
	m_nEndCounter = 0;
	m_fBaseSpeed = 0.0f;
	m_bArmor = false;
	m_nStarNum = 0;
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
HRESULT CPlayer::Init(void)
{
	// ���f�����擾
	CXfile *pXfile = CManager::GetResourceManager()->GetXfileClass();

	// !nullcheck
	if (pXfile != NULL)
	{
		// ���f���̏���n��
		ModelCreate(CXfile::HIERARCHY_XFILE_NUM_PLAYER);
	}

    // UI�̐���
    m_pPlayerUI = CPlayer_UI::Create();
    m_pPlayerUI->Init(m_nNumber);

	// ����������
	CCharacter::Init();				// ���W �p�x
	SetRadius(PLAYER_RADIUS);				// ���a�̐ݒ�
	SetSpeed(PLAYER_FLY_SPEED);				// ���x�̐ݒ�

	m_fBaseSpeed = PLAYER_FLY_SPEED;		// ���̃X�s�[�h�ێ�
	m_fBaseRadius = PLAYER_RADIUS;			// ���a

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

	// ���W���
	D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
	SetPosOld(pos);				// �Â����W�ۑ�

	// �v���C���[�̏��
	UpdateState();

	// ���[�V�������
	UpdateMotionState();

	// �v���C���[�̐���
	PlayerControl();

	// �A�C�e���̍폜����
    m_pPlayerUI->ItemErase();

	// �e�N���X�̍X�V����
	CCharacter::Update();

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

	while (m_rotDest.x - rot.x > D3DXToRadian(180))
	{
		m_rotDest.x -= D3DXToRadian(360);
	}

	while (m_rotDest.x - rot.x < D3DXToRadian(-180))
	{
		m_rotDest.x += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	rot += (m_rotDest - rot) * PLAYER_ROT_SPEED;

	while (rot.y > D3DXToRadian(180))
	{
		rot.y -= D3DXToRadian(360);
	}

	while (rot.y < D3DXToRadian(-180))
	{
		rot.y += D3DXToRadian(360);
	}

	while (rot.x > D3DXToRadian(180))
	{
		rot.x -= D3DXToRadian(360);
	}

	while (rot.x < D3DXToRadian(-180))
	{
		rot.x += D3DXToRadian(360);
	}

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

    // �L�[�{�[�h���
    CInputKeyboard *pKeyboard = CManager::GetKeyboard();

    // SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
    if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_R_TRIGGER, GetPlayerNum())
        || pKeyboard->GetTrigger(DIK_I))
    {
        // �A�C�e���̎g�p
        m_pPlayerUI->UseItem();
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
	float fCameraAngle = CGame::GetCamera(m_nNumber)->GetHorizontal();	// �J�����p�x�擾
	float fMoveAngle = 0.0f; 											// �ړ��p�x
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

			// �W�����v���[�V�����̍Đ�
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
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();		// �L�[�{�[�h���擾
	DIJOYSTATE js = CInputJoypad::GetStick(m_nNumber);		// �W���C�p�b�h���擾
	D3DXVECTOR3 move = ZeroVector3;							// �ړ���
	D3DXMATRIX mtxRot;										// ��]�v�Z�p�s��
	ZeroMemory(&mtxRot, sizeof(mtxRot));
	CCamera* pCamera = CGame::GetCamera(m_nNumber);

	// �d�͂𖳌���
	if (GetUseGravity())
	{
		SetUseGravity(false);
	}
	
	//�v���C���[�̏�����Ɉړ�
	move = D3DXVECTOR3(0.0f, GetSpeed(), 0.0f);
	// �X�e�B�b�N���������܂ꂽ��㉺���]����
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L3, m_nNumber))
	{
		m_bStickReverseVartical = !m_bStickReverseVartical;
	}
	// �R���g���[���[�̓��͂�ϊ�
	m_rotDest.y += D3DXToRadian((float)js.lX / 1000.0f);
	if (m_bStickReverseVartical)
	{
		m_rotDest.x -= D3DXToRadian((float)js.lY / 1000.0f);
	}
	else
	{
		m_rotDest.x += D3DXToRadian((float)js.lY / 1000.0f);
	}
	
	// �㉺�ړ��̐���
	if (m_rotDest.x > FLY_ROT_X_MAX)
	{
		m_rotDest.x = FLY_ROT_X_MAX;
	}
	if (m_rotDest.x < FLY_ROT_X_MIN)
	{
		m_rotDest.x = FLY_ROT_X_MIN;
	}
	// �R���g���[���[���͂𗘗p���ăv���C���[�̌�����ϊ�
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rotDest.y, m_rotDest.x, m_rotDest.z);
	D3DXVec3TransformNormal(&move, &move, &mtxRot);
	move.y -= abs(move.y * FLY_GRAVITY_RATE);
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
	// ���W�󂯎��
	D3DXVECTOR3 pos = GetPos();

	// �}�b�v�̏��XToZ
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

	// �}�b�v���Y
	if (pos.y < -MAP_LIMIT_Y)
	{
		// ���|�b�v�̏���
		Repop();
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
// ���|�b�v�̏���
//=============================================================================
void CPlayer::Repop(void)
{
	// �|�C���^���擾
	CStageMap *pStageMap = CManager::GetGame()->GetStageMap();

	// !nullcheck
	if (pStageMap != nullptr)
	{
		// ���[�J���ϐ��錾
		int mMeshPillarNum = pStageMap->GetMeshPillarNum();		// ���̐�
		float fPrevLenght = 0.0f;								// �O��܂ł̋����擾
		int nSortNum = -1;										// ��ԏ������z��ԍ����m��

		for (int nCount = 0; nCount < mMeshPillarNum; nCount++)
		{
			// ���̏��
			CMeshPillar *pMeshPiller = pStageMap->GetMeshPillar(nCount);

			// !nullcheck
			if (pMeshPiller != nullptr)
			{
				// ���W�擾
				D3DXVECTOR3 pos = GetPos();						// ���g�̍��W
				D3DXVECTOR3 PillerPos = pMeshPiller->GetPos();	// ���̍��W
				
				// ��_�̋���
				float fLength = sqrtf(
					powf((PillerPos.x - pos.x), 2) +
					powf((PillerPos.z - pos.z), 2));

				// �O�̒��̋������n����������
				if (fPrevLenght > fLength || fPrevLenght == 0.0f)
				{
					fPrevLenght = fLength;	// �߂���������
					nSortNum = nCount;		// �߂��z��ԍ���ݒ�
				}
			}
		}

		// ��ԋ߂��������̏��擾
		CMeshPillar *pMeshPiller = pStageMap->GetMeshPillar(nSortNum);

		// ���W�ݒ�
		SetPos(pMeshPiller->GetPos()*2);
		SetFly(false);
		SetUseGravity(true);
	}
}