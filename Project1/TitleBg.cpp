/*-------------------------------------------------

	[GameBg.cpp]
	Author : 出合翔太

--------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Application.h"
#include "Renderer2D.h"
#include "TitleSystem.h"
#include "TitleBg.h"

namespace
{
	int32_t g_BeginSpan = 0;
}

Particle::Particle()
{
	m_Render = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Effect");
	m_Transform = AddComponent<Transform>();
	m_Angle = 0.0f;
}

Particle::~Particle()
{
}

void Particle::Begin()
{	
	m_Life = myLib::Random::Rand_R(50, 100);

	m_Transform->position().x = 0.0f - 50.0f;
	m_Transform->position().y = static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT));

	m_Velocity.x = 0.0f;
	m_Velocity.y = myLib::Random::GetRandomXOR();
	m_Velocity.z = 0.0f;

	m_Acceleration.x = 1.0f;
	m_Acceleration.y = 0.0f;
	m_Acceleration.z = 0.0f;

	m_Color = D3DXVECTOR4(myLib::Random::GetRandomXORf(), myLib::Random::GetRandomXORf(), myLib::Random::GetRandomXORf(), 0.5f);

	m_Active = true;
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
		if (m_TitleSystem->GetState() == m_TitleSystem->BEGIN)
		{
			Begin();
		}
		else
		{
			switch (g_BeginSpan)
			{
			case 0:
				Begin(0.0f - 50.0f, static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT)), 5.0f, 0.0f, 0.0f, 0.0f);
				break;
			case 1:
				Begin(static_cast<float>(SCREEN_WIDTH) + 50.0f, static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT)), -5.0f, 0.0f, 0.0f, 0.0f);
				break;
			case 2:
				Begin(static_cast<float>(myLib::Random::Rand_R(0, SCREEN_WIDTH)), 0.0f - 50.0f, 0.0f, 5.0f, 0.0f, 0.0f);
				break;
			case 3:
				Begin(static_cast<float>(myLib::Random::Rand_R(0, SCREEN_WIDTH)), static_cast<float>(SCREEN_HEIGHT) + 50.0f, 0.0f, -5.0f, 0.0f, 0.0f);
				break;
			}
			g_BeginSpan++;
			if (g_BeginSpan > 3)
			{
				g_BeginSpan = 0;
			}
		}
	}
}

void Particle::Event()
{
}

void Particle::Draw()
{
	Engine::Get().graphics()->SetBlendStateSub();
	
	D3DXVECTOR2 pos = D3DXVECTOR2(m_Transform->position().x, m_Transform->position().y);
	D3DXVECTOR2 size = D3DXVECTOR2(50.0f, 50.0f);
	D3DXVECTOR2 t1 = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 t2 = D3DXVECTOR2(1.0f, 1.0f);

	m_Render->Draw(pos, size, t1, t2, m_Color);

	Engine::Get().graphics()->SetBlendStateDefault();
}

void Particle::titleSystem(TitleSystem * p)
{
	m_TitleSystem = p;
}

void Particle::Begin(float x, float y, float vx, float vy, float ax, float ay)
{
	m_Life = myLib::Random::Rand_R(50, 100);

	m_Transform->position().x = x;
	m_Transform->position().y = y;

	m_Velocity.x = vx;
	m_Velocity.y = vy;
	m_Velocity.z = 0.0f;

	m_Acceleration.x = ax;
	m_Acceleration.y = ay;
	m_Acceleration.z = 0.0f;

	m_Color = D3DXVECTOR4(myLib::Random::GetRandomXORf(), myLib::Random::GetRandomXORf(), myLib::Random::GetRandomXORf(), 0.5f);

	m_Active = true;
}

void Particle::Velocity(float x, float y)
{
	m_Velocity.x = x;
	m_Velocity.y = y;
}

void Particle::Acceleration(float x, float y)
{
	m_Acceleration.x = x;
	m_Acceleration.y = y;
}

bool Particle::NotActive()
{
	// アクティブ状態でないならtrueを返す
	if (m_Active == false)
	{
		return true;
	}
	return false;
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
	// タイトルのステート
	m_State = m_TitleSystem->GetState();
}

void GameBg::TitleBg::Event()
{
}

void GameBg::TitleBg::Draw()
{
	if (m_TitleSystem->EState::SETTING_SELECT == m_State || m_TitleSystem->EState::CHECK_INPUT == m_State)
	{
		// Setting画面
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	}
	else
	{
		// タイトル画面
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.49f, 0.9f));
	}
}
void GameBg::TitleBg::titleSystem(TitleSystem * p)
{
	m_TitleSystem = p;
}
#pragma endregion TitleBgメソッド