//=====================================================
//
// �}�W�b�N�n���h�N���X [magichand.cpp]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "wind_effect.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"

//=====================================================
// �}�N����`
//=====================================================
#define DEFAULT_SIZE		(D3DXVECTOR3(10.0f, 200.0f, 0.0f))	// ��{�̑傫��
#define DEFAULT_LIFE		(20)								// ��{�̗̑�

//=====================================================
// �R���X�g���N�^
//=====================================================
CWindEffect::CWindEffect(PRIORITY Priority) : CBillboard(Priority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CWindEffect::~CWindEffect()
{

}

//=====================================================
// �C���X�^���X����
//=====================================================
CWindEffect * CWindEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Distance, int nTexInfo)
{
	// �������m��
	CWindEffect *pEffect = new CWindEffect;

	if (pEffect != NULL)
	{
		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// �A�j���[�V�����e�N�X�`���ݒ�
		pEffect->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));

		float fAngle = D3DXToRadian((float)(rand() % 360));
		D3DXVECTOR3 Createrot = D3DXVECTOR3(rot.x + D3DXToRadian(90.0f) + fAngle, rot.y + D3DXToRadian(90.0f) + fAngle, rot.z);

		// �͈͂̐ݒ�
		D3DXVECTOR3 Range = D3DXVECTOR3(
			(300.0f),
			(300.0f),
			(300.0f));

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			(float)(rand() % (int)(Range.x)) + pos.x - (Range.x / 2),
			(float)(rand() % (int)(Range.y)) + pos.y - (Range.y / 2),
			(float)(rand() % (int)(Range.z)) + pos.z - (Range.z / 2));

		pEffect->SetPos(TargetPos);

		pEffect->SetRot(rot);
		pEffect->SetSize(DEFAULT_SIZE);
		pEffect->SetSizeBase(DEFAULT_SIZE);
		pEffect->SetLife(DEFAULT_LIFE);		// �̗͂̐ݒ�
		pEffect->SetAlpha(true);			// �A���t�@�e�X�g�̐ݒ�

		// ����������
		pEffect->Init();
	}

	return pEffect;
}

//=====================================================
// ����������
//=====================================================
HRESULT CWindEffect::Init()
{
	// ����������
	CBillboard::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CWindEffect::Uninit(void)
{
	// �I������
	CBillboard::Uninit();

	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CWindEffect::Update(void)
{
	// �X�V����
	CBillboard::Update();

	D3DXCOLOR col = GetColor();
	col.a -= 0.1f;
	SetColor(col);

	//D3DXVECTOR3 pos =
	//	D3DXVECTOR3(CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._41,
	//		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._42,
	//		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._43) +
	//	D3DXVECTOR3(m_Distance.x * sinf(CGame::GetCamera(m_nPlayerNum)->GetHorizontal() + D3DXToRadian(90.0f)),
	//		m_Distance.y,
	//		m_Distance.x * cosf(CGame::GetCamera(m_nPlayerNum)->GetHorizontal() + D3DXToRadian(90.0f)));
	//SetPos(pos);

	//D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,
	//	CGame::GetCamera(m_nPlayerNum)->GetHorizontal(),
	//	0.0f);
	//SetRot(rot);
}

//=====================================================
// �`�揈��
//=====================================================
void CWindEffect::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}