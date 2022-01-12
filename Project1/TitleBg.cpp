/*-------------------------------------------------

	[GameBg.cpp]
	Author : �o���đ�

--------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Application.h"
#include "Renderer2D.h"
#include "TitleSystem.h"
#include "TitleBg.h"

int32_t Particle::m_BeginTypetoGenerateOtherBeginScene = 0;

Particle::Particle()
{
	m_Render = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Effect");
	m_Transform = AddComponent<Transform>();
}

Particle::~Particle()
{
}

void Particle::Begin()
{	
	m_Life = myLib::Random::Rand_R(50, 100);
	//
	//m_Transform->position().x = 0.0f - 50.0f;
	//m_Transform->position().y = static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT));
	//
	//m_Velocity.x = 0.0f;
	//m_Velocity.y = myLib::Random::GetRandomXOR();
	//m_Velocity.z = 0.0f;
	//
	//m_Acceleration.x = 1.0f;
	//m_Acceleration.y = 0.0f;
	//m_Acceleration.z = 0.0f;
	//
	//m_Color = D3DXVECTOR4(myLib::Random::GetRandomXORf(), myLib::Random::GetRandomXORf(), 1.0f, 1.0f);
	//m_Size = D3DXVECTOR2(55.0f, 20.0f);
}

void Particle::Update()
{
	m_Life--;
	if (m_Life > 0)
	{
		m_Velocity += m_Acceleration;
		m_Transform->position() += m_Velocity;
	}
	else
	{
		BeginGenerateOtherBeginScene();
	}
}

void Particle::Event()
{
}

void Particle::Draw()
{
	// ���Z����
	Engine::Get().graphics()->SetBlendStateAdd();
	
	D3DXVECTOR2 pos = D3DXVECTOR2(m_Transform->position().x, m_Transform->position().y);
	D3DXVECTOR2 t1 = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 t2 = D3DXVECTOR2(1.0f, 1.0f);

	m_Render->Draw(pos, m_Size, t1, t2, m_Color);

	Engine::Get().graphics()->SetBlendStateDefault();
}

void Particle::titleSystem(TitleSystem * p)
{
	m_TitleSystem = p;
}

void Particle::Begin(float x, float y, float vx, float vy, float ax, float ay)
{
	m_Life = 50;

	m_Transform->position().x = x;
	m_Transform->position().y = y;

	m_Velocity.x = vx;
	m_Velocity.y = vy;
	m_Velocity.z = 0.0f;

	m_Acceleration.x = ax;
	m_Acceleration.y = ay;
	m_Acceleration.z = 0.0f;

	m_Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(50.0f, 50.0f);
}

// �p�[�e�B�N���𔭐�������
void Particle::BeginGenerateOtherBeginScene()
{
	// �����ʒu
	switch (m_BeginTypetoGenerateOtherBeginScene)
	{
		// ��
	case 0:
		Begin(0.0f - 50.0f, static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT)), 2.0f, 0.0f, 0.0f, 0.0f);
		break;
		//�E
	case 1:
		Begin(static_cast<float>(SCREEN_WIDTH) + 50.0f, static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT)), -2.0f, 0.0f, 0.0f, 0.0f);
		break;
		// ��
	case 2:
		Begin(static_cast<float>(myLib::Random::Rand_R(0, SCREEN_WIDTH)), 0.0f - 50.0f, 0.0f, 2.0f, 0.0f, 0.0f);
		break;
		// ��
	case 3:
		Begin(static_cast<float>(myLib::Random::Rand_R(0, SCREEN_WIDTH)), static_cast<float>(SCREEN_HEIGHT) + 50.0f, 0.0f, -2.0f, 0.0f, 0.0f);
		break;
	}
	// ���̐����ʒu��ݒ�
	m_BeginTypetoGenerateOtherBeginScene++;
	
	// �ϐ������Z�b�g����
	if (m_BeginTypetoGenerateOtherBeginScene > 3)
	{
		m_BeginTypetoGenerateOtherBeginScene = 0;
	}
}

#pragma region TitleBg_method
GameBg::TitleBg::TitleBg()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "TitleBg");	
	
}

GameBg::TitleBg::~TitleBg()
{
}

void GameBg::TitleBg::Begin()
{
	
}

void GameBg::TitleBg::Update()
{
	// �^�C�g���̃X�e�[�g
	m_State = m_TitleSystem->GetState();
}

void GameBg::TitleBg::Event()
{
}

void GameBg::TitleBg::Draw()
{
	if (m_TitleSystem->EState::SETTING_SELECT == m_State || m_TitleSystem->EState::CHECK_INPUT == m_State)
	{
		// Setting���
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	}
	else
	{
		// �^�C�g�����
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.49f, 0.9f));
	}
}
void GameBg::TitleBg::titleSystem(TitleSystem * p)
{
	m_TitleSystem = p;
}
#pragma endregion TitleBg���\�b�h