/*-------------------------------------------------------------

	[PlayerBulletAmount.cpp]
	Author : �o���đ�

	�v���C���[�̒e����`�悷��

--------------------------------------------------------------*/
#include "Player.h"
#include "PlayerBulletAmount.h"
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "Application.h"

namespace
{
	// �`�悷���̈ʒu
	const D3DXVECTOR2 g_PivotDrawPosition = D3DXVECTOR2(1600.0f, 1000.0f);
}

#pragma region _Parts required to draw the number of bullets_
PlayerBulletAmount::PlayerBulletAmount() : DrawNumber(64.0f, 2)
{
}

PlayerBulletAmount::~PlayerBulletAmount()
{
}

void PlayerBulletAmount::Draw(int value)
{
	for (int32_t i = 0; i < Getdigit(); ++i)
	{
		int num = value % 10;
		value /= 10;
		NumberDraw(D3DXVECTOR2(g_PivotDrawPosition.x - 75.0f + ((GetSize() - 20.0f) * (Getdigit() - (i + 1))), g_PivotDrawPosition.y), num);
	}
}

PlayerBulletAmountMax::PlayerBulletAmountMax() : DrawNumber(64.0f, 2)
{
}

PlayerBulletAmountMax::~PlayerBulletAmountMax()
{
}

void PlayerBulletAmountMax::Draw(int value)
{
	for (int32_t i = 0; i < Getdigit(); ++i)
	{
		int num = value % 10;
		value /= 10;
		NumberDraw(D3DXVECTOR2(g_PivotDrawPosition.x + 35.0f + ((GetSize() - 20.0f) * (Getdigit() - (i + 1))), g_PivotDrawPosition.y), num);
	}
}

DrawSlash::DrawSlash() : m_Graphics(*Engine::Get().graphics()), m_Resource(*Engine::Get().resource())
{
	// �}�g���N�X�̌v�Z���g���āA�X���b�V�������
	float x = 5.0f;
	float y = 32.0f;
	D3DXMATRIX mat[4];
	D3DXMatrixTranslation(&mat[0], -x, -y, 0.0f); // ����
	D3DXMatrixTranslation(&mat[1], x, -y, 0.0f);	// �E��
	D3DXMatrixTranslation(&mat[2], -x, y, 0.0f);	// ����	
	D3DXMatrixTranslation(&mat[3], x, y, 0.0f);	// �E��

	D3DXMATRIX mtrans, mrot, mworld;
	float px[4], py[4];

	// �}�g���N�X�̌v�Z
	D3DXMatrixTranslation(&mtrans, g_PivotDrawPosition.x, g_PivotDrawPosition.y, 0.0f);
	D3DXMatrixRotationZ(&mrot, 0.1f);
	for (int i = 0; i < 4; i++)
	{
		mworld = mat[i] * mrot * mtrans;
		px[i] = mworld._41;
		py[i] = mworld._42;
	}

	// ���_�쐬
	Vertex3D vertex[4];

	for (int32_t i = 0; i < 4; i++)
	{
		vertex[i].Position = D3DXVECTOR3(px[i], py[i], 0.0f);
		vertex[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[i].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	m_Graphics.GetDevice()->CreateBuffer(&bd, &sd, m_VertexBuffer.GetAddressOf());
}

DrawSlash::~DrawSlash()
{
}

void DrawSlash::Draw()
{
	m_Resource.SetShader("NoLighting");
	m_Resource.SetTexture(0, "Gage");
	// ���_�o�b�t�@
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;
	m_Graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);

	//�v���~�e�B�u�g�|���W�ݒ�
	m_Graphics.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	m_Graphics.GetDeviceContext()->Draw(4, 0);
}
#pragma endregion _�e����`�悷�邽�߂ɕK�v�ȃp�[�c_

PlayerUi::BulletAmount::BulletAmount()
{
	m_DrawBulletAmount.emplace_back(std::make_unique<PlayerBulletAmount>());
	m_DrawBulletAmount.emplace_back(std::make_unique<PlayerBulletAmountMax>());
	m_Slash = std::make_unique<DrawSlash>();
}

PlayerUi::BulletAmount::~BulletAmount()
{
}

void PlayerUi::BulletAmount::Begin()
{
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	// �ŏ��ɍő吔��������Ă���
	m_BulletValueMax = m_Player->amountBullets();
}

void PlayerUi::BulletAmount::Update()
{
	m_BulletsValue = m_Player->amountBullets();
}

void PlayerUi::BulletAmount::Event()
{
}

void PlayerUi::BulletAmount::Draw()
{
	// �e��/�ő�l�̕`��
	m_Slash->Draw();
	m_DrawBulletAmount[0]->Draw(m_BulletsValue);
	m_DrawBulletAmount[1]->Draw(m_BulletValueMax);
}
