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

	float angle = D3DXToRadian(myLib::Random::Rand_R(0, 360));

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
		m_Active = false;
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
	
}

void GameBg::TitleBg::Event()
{
}

void GameBg::TitleBg::Draw()
{
	//
	m_ParticleList = Engine::Get().application()->GetScene()->GetGameObjects<Particle>(ELayer::LAYER_2D_BG);
	for (auto particle : m_ParticleList)
	{
		if (particle->NotActive())
		{
			particle->Begin();
		}
	}
	m_TitleSystem = Engine::Get().application()->GetScene()->GetGameObject<TitleSystem>(ELayer::LAYER_2D_UI);
	uint32_t state = m_TitleSystem->GetState();

	if (m_TitleSystem->EState::SETTING_SELECT == state || m_TitleSystem->EState::CHECK_INPUT == state)
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
#pragma endregion TitleBgメソッド