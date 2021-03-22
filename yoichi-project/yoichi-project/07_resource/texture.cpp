//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
// �e�N�X�`���̖��O
#define TEXTURE_NAME_EFFECT			("data/Texture/effect000.png")		// �G�t�F�N�g
#define TEXTURE_NAME_FLOOR			("data/Texture/scaffold.png")		// ��
#define TEXTURE_NAME_TITLE_LOGO		("data/Texture/titlelogo001.png")	// �^�C�g���̃��S
#define TEXTURE_NAME_ITEM_BLUE_WING	("data/Texture/item_bluewind.png")	// �A�C�e�����H��
#define TEXTURE_NAME_ITEM_RED_WING	("data/Texture/item_redwind.png")	// �A�C�e���Ԃ��H��
#define TEXTURE_NAME_ITEM_BOMB		("data/Texture/item_bomb.png")		// �A�C�e���{��
#define TEXTURE_NAME_ITEM_BARRIER	("data/Texture/item_barrier.png")	// �A�C�e���o���A
#define TEXTURE_NAME_ITEM_THUNDER	("data/Texture/item_thunder.png")	// �A�C�e����
#define TEXTURE_NAME_ITEM_MHAND		("data/Texture/item_mhand.png")		// �A�C�e��M�n���h
#define TEXTURE_NAME_ITEM_VORTEX	("data/Texture/item_vortex.png")	// �A�C�e���Q
#define TEXTURE_NAME_SEA			("data/Texture/sea000.jpeg")		// �C
#define TEXTURE_FILE_ITEM_RESULT_1ST	("data/Texture/1st.png")		// ���U���g1��
#define TEXTURE_FILE_ITEM_RESULT_2ND	("data/Texture/2nd.png")		// ���U���g2��
#define TEXTURE_FILE_ITEM_RESULT_3RD	("data/Texture/3rd.png")		// ���U���g3��
#define TEXTURE_FILE_ITEM_RESULT_4TH	("data/Texture/4th.png")		// ���U���g4��
// �����e�N�X�`���̖��O
#define SEPARATE_TEX_NAME_NUMBER	("data/Texture/number000.png")	// �i���o�[

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTexture * CTexture::Create(void)
{
	CTexture *pTexture = new CTexture;

	return pTexture;
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EFFECT, &m_apTexture[TEXTURE_NUM_EFFECT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FLOOR, &m_apTexture[TEXTURE_NUM_FLOOR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_TITLE_LOGO, &m_apTexture[TEXTURE_NUM_TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BLUE_WING, &m_apTexture[TEXTURE_NUM_ITEM_BLUE_WING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_RED_WING, &m_apTexture[TEXTURE_NUM_ITEM_RED_WING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BOMB, &m_apTexture[TEXTURE_NUM_ITEM_BOMB]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_BARRIER, &m_apTexture[TEXTURE_NUM_ITEM_BARRIER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_THUNDER, &m_apTexture[TEXTURE_NUM_ITEM_THUNDER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_MHAND, &m_apTexture[TEXTURE_NUM_ITEM_MHAND]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ITEM_VORTEX, &m_apTexture[TEXTURE_NUM_ITEM_VORTEX]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SEA, &m_apTexture[TEXTURE_NUM_SEA]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_1ST, &m_apTexture[TEXTURE_NUM_RESULT_1ST]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_2ND, &m_apTexture[TEXTURE_NUM_RESULT_2ND]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_3RD, &m_apTexture[TEXTURE_NUM_RESULT_3RD]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_ITEM_RESULT_4TH, &m_apTexture[TEXTURE_NUM_RESULT_4TH]);
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::Unload(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_NUMBER, &m_apSeparateTexture[SEPARATE_TEX_NUMBER].pSeparateTexture);

	return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnload(void)
{
	// �e�N�X�`���̉��
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != NULL)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
		}
	}
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != NULL)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != NULL)
		{
			// �e�N�X�`�����
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}