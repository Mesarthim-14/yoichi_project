//=====================================================
//
// �V���h�E�N���X [shadow.cpp]
// Author : Ito Yogo
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "stage_map.h"
#include "mesh_pillar.h"
#include "meshfield.h"

//=====================================================
// �}�N����`
//=====================================================
#define DEFAULT_SIZE		(D3DXVECTOR3(150.0f, 150.0f, 0.0f))				// ��{�̑傫��
#define DEFAULT_ROT			(D3DXVECTOR3(D3DXToRadian(90.0f), 0.0f, 0.0f))	// ��{�̊p�x
#define DEFAULT_COLOR		(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))				// ��{�̐F
#define DEFAULT_POS_Y		(-2000.0f)										// ��{�̍��W
#define PILLAR_POS_Y		(0.0f)											// ���̍��W
#define DIVIDE_NUM			(2000.0f)										// ���������鐔

//=====================================================
// �R���X�g���N�^
//=====================================================
CShadow::CShadow(PRIORITY Priority) : CBillboard(Priority)
{
	m_nPlayerNum = 0;
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CShadow::~CShadow()
{

}

//=====================================================
// �C���X�^���X����
//=====================================================
CShadow * CShadow::Create(int nTexInfo, int nPlayerNum)
{
	// �������m��
	CShadow *pEffect = new CShadow;

	if (pEffect != NULL)
	{
		CTexture *pTexture = GET_TEXTURE_PTR;

		// �A�j���[�V�����e�N�X�`���ݒ�
		pEffect->BindTexture(pTexture->GetTexture((CTexture::TEXTURE_TYPE)nTexInfo));

		pEffect->SetSize(DEFAULT_SIZE);
		pEffect->SetRot(DEFAULT_ROT);
		pEffect->SetColor(DEFAULT_COLOR);
		pEffect->SetAlpha(true);			// �A���t�@�e�X�g�̐ݒ�
		pEffect->m_nPlayerNum = nPlayerNum; // �Ǐ]������v���C���[�̔ԍ�

		// ����������
		pEffect->Init();

	}

	return pEffect;
}

//=====================================================
// ����������
//=====================================================
HRESULT CShadow::Init()
{
	// ����������
	CBillboard::Init();

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CShadow::Uninit(void)
{
	// �I������
	CBillboard::Uninit();

	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CShadow::Update(void)
{
	// �X�V����
	CBillboard::Update();

	// ���W�̍X�V
	D3DXVECTOR3 pos = CGame::GetPlayer(m_nPlayerNum)->GetPos();

	// �|�C���^���擾
	CStageMap *pStageMap = CManager::GetGame()->GetStageMap();

	// !nullcheck
	if (pStageMap != nullptr)
	{
		// ���[�J���ϐ��錾
		int mMeshPillarNum = pStageMap->GetMeshPillarNum();		// ���̐�

		for (int nCount = 0; nCount < mMeshPillarNum; nCount++)
		{
			// ���̏��
			CMeshPillar *pMeshPiller = pStageMap->GetMeshPillar(nCount);

			// !nullcheck
			if (pMeshPiller != nullptr)
			{
				D3DXVECTOR3 PillerPos = pMeshPiller->GetPos() * 2;	// ���̍��W
				float fRadius = pMeshPiller->GetSize().x;

				// �v���C���[�̏��擾
				D3DXVECTOR3 PlayerPos = CGame::GetPlayer(m_nPlayerNum)->GetPos();		// ���W�擾
				float fPlayerRadius = CGame::GetPlayer(m_nPlayerNum)->GetRadius();		// ���a

				// ��_�̋����A��_�̊p�x�ݒ�
				float fLength = sqrtf(
					powf((PlayerPos.x - PillerPos.x), 2) +
					powf((PlayerPos.z - PillerPos.z), 2));

				// ��������
				float fDistance = fRadius;

				// �����蔻��
				if (fLength <= fDistance)
				{
					pos.y = PILLAR_POS_Y + 0.1f;
					break;
				}
				else
				{
					pos.y = DEFAULT_POS_Y + 0.1f;
				}
			}
		}
	}
	SetPos(pos);

	// �F�̍X�V
	D3DXCOLOR col = GetColor();
	float fAlphaSub = (CGame::GetPlayer(m_nPlayerNum)->GetPos().y - pos.y) / DIVIDE_NUM;
	col.a = 1.0f - fAlphaSub;
	SetColor(col);
}

//=====================================================
// �`�揈��
//=====================================================
void CShadow::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}