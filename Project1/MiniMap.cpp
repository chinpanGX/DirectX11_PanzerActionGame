/*-------------------------------------------------------------

	[MiniMap.cpp]
	Author : �o���đ�

	�~�j�}�b�v�̕\��

--------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Graphics.h"
#include "Renderer2D.h"
#include "Vehicle.h"
#include "Player.h"
#include "Enemy.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{
	m_Bg = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "MiniMapBg");
	m_Map = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Gage");
	m_Icon = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Gage");
}

MiniMap::~MiniMap()
{
}

void MiniMap::Begin()
{
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_Enemy = Engine::Get().application()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);

	m_Radius = 200.0f;

	m_Position = D3DXVECTOR2(m_Radius + 25.0f, static_cast<float>(SCREEN_HEIGHT) - m_Radius - 25.0f);
	auto min = D3DXVECTOR2(0.0f, 0.0f);
	auto max = D3DXVECTOR2(1.0f, 1.0f);
	auto color = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 0.7f);

	// �~�j�}�b�v�̐ݒ�
	auto size = D3DXVECTOR2(m_Radius, m_Radius);
	m_Map->SetVertex(m_Position, size, min, max, color);

	// �w�i�̐ݒ�
	// �w�i�e�N�X�`���̑傫���̔��a
	float bgRadius = std::sqrtf(m_Radius * m_Radius + m_Radius * m_Radius) + 20.0f;
	size = D3DXVECTOR2(bgRadius, bgRadius);
	color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.7f);
	m_Bg->SetVertex(m_Position, size, min, max, color);
}

void MiniMap::Update()
{
	m_PlayerPosition.x = m_Position.x - m_Player->vehicle().bodyTransform().position().x * 0.333333f * -1;
	m_PlayerPosition.y = m_Position.y - m_Player->vehicle().bodyTransform().position().z * 0.333333f;

	m_EnemyPosition.x = m_Position.x - m_Enemy->vehicle().bodyTransform().position().x * 0.333333f * -1;
	m_EnemyPosition.y = m_Position.y - m_Enemy->vehicle().bodyTransform().position().z * 0.333333f;
}

void MiniMap::Event()
{
}

void MiniMap::Draw()
{	
	// ���ʕϐ�
	auto min = D3DXVECTOR2(0.0f, 0.0f);
	auto max = D3DXVECTOR2(1.0f, 1.0f);

	// �~�j�}�b�v�̔w�i
	m_Bg->Draw();

	// �}�b�v�̐ݒ�
	m_Map->Draw();

	// �v���C���[�̐ݒ�
	auto size = D3DXVECTOR2(10.0f, 10.0f);
	auto color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_Icon->Draw(m_PlayerPosition, size, min, max, color);

	// �G��`�悵�Ă��邩�`�F�b�N
	if (m_Enemy->IsDraw())
	{
		// �`�悵�Ă���Ȃ�A�~�j�}�b�v�ɉf��
		color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		m_Icon->Draw(m_EnemyPosition, size, min, max, color);
	}
}

