//=====================================================
//
// �}�W�b�N�n���h�N���X [magichand.cpp]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "magichand.h"
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
#define DEFAULT_SIZE		(D3DXVECTOR3(200.0f, 277.5f, 0.0f))	// ��{�̑傫��
#define DEFAULT_LIFE		(300)								// ��{�̗̑�

//=====================================================
// �R���X�g���N�^
//=====================================================
CMagichand::CMagichand(PRIORITY Priority) : CBillboard(Priority)
{

}

//=====================================================
// �f�X�g���N�^
//=====================================================
CMagichand::~CMagichand()
{

}

//=====================================================
// �C���X�^���X����
//=====================================================
CMagichand * CMagichand::Create(D3DXVECTOR3 Distance, int nTexInfo, int nPlayerNum)
{
	// �������m��
	CMagichand *pEffect = new CMagichand;

	if (pEffect != NULL)
	{
		// ����������
		pEffect->Init(CGame::GetPlayer(nPlayerNum)->GetPos() + Distance, DEFAULT_SIZE);

		CTexture *pTexture = CManager::GetResourceManager()->GetTextureClass();

		// �A�j���[�V�����e�N�X�`���ݒ�
		pEffect->BindTexture(pTexture->GetSeparateTexture((CTexture::SEPARATE_TEX_TYPE)nTexInfo));
		pEffect->InitAnimation(
			pTexture->GetSparateTexInfo((CTexture::SEPARATE_TEX_TYPE)nTexInfo),
			pTexture->GetSparateTexLoop((CTexture::SEPARATE_TEX_TYPE)nTexInfo));

		pEffect->SetLife(DEFAULT_LIFE);		// �̗͂̐ݒ�
		pEffect->SetAlpha(true);			// �A���t�@�e�X�g�̐ݒ�
		pEffect->m_nPlayerNum = nPlayerNum; // �Ǐ]������v���C���[�̔ԍ�
		pEffect->m_Distance = Distance;		// ����
	}

	return pEffect;
}

//=====================================================
// ����������
//=====================================================
HRESULT CMagichand::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CMagichand::Uninit(void)
{
	// �I������
	CBillboard::Uninit();

	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CMagichand::Update(void)
{
	// �X�V����
	CBillboard::Update();

	D3DXVECTOR3 pos =
		D3DXVECTOR3(CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._41,
		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._42,
		CGame::GetPlayer(m_nPlayerNum)->GetModelAnime(21)->GetMtxWorld()._43) +
		D3DXVECTOR3(m_Distance.x * sinf(CGame::GetCamera(m_nPlayerNum)->Get��() + D3DXToRadian(90.0f)),
			m_Distance.y,
			m_Distance.x * cosf(CGame::GetCamera(m_nPlayerNum)->Get��() + D3DXToRadian(90.0f)));
	SetPos(pos);

	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,
		CGame::GetCamera(m_nPlayerNum)->Get��(),
		0.0f);
	SetRot(rot);
}

//=====================================================
// �`�揈��
//=====================================================
void CMagichand::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}