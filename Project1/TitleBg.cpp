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

#pragma region _TitleParticle_method
int32_t TitleParticle::m_TypeToGenerate = 0;

TitleParticle::TitleParticle()
{
	m_Render = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Effect");
	m_Transform = AddComponent<Transform>();
}

TitleParticle::~TitleParticle()
{
}

void TitleParticle::Begin()
{	
	m_Life = myLib::Random::Rand_R(50, 100);
}

void TitleParticle::Update()
{
	m_Life--;
	
	if (m_Life > 0)
	{
		// 位置を更新
		m_Velocity += m_Acceleration;
		m_Transform->GetPosition() += m_Velocity;
	}
	// ライフが０になったら、生成する
	else
	{
		Generate();
	}
}

void TitleParticle::Event()
{
}

void TitleParticle::Draw()
{
	// 加算合成
	Engine::Get().GetGraphics()->SetBlendStateAdd();
	
	D3DXVECTOR2 pos = D3DXVECTOR2(m_Transform->GetPosition().x, m_Transform->GetPosition().y);
	D3DXVECTOR2 texMin = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 texMax = D3DXVECTOR2(1.0f, 1.0f);

	m_Render->Draw(pos, m_Size, texMin, texMax, m_Color);

	Engine::Get().GetGraphics()->SetBlendStateDefault();
}

void TitleParticle::SetTitleSystem(TitleSystem * Title)
{
	m_TitleSystem = Title;
}

void TitleParticle::Begin(float x, float y, float vx, float vy, float ax, float ay)
{
	m_Life = 50;

	m_Transform->GetPosition().x = x;
	m_Transform->GetPosition().y = y;

	m_Velocity.x = vx;
	m_Velocity.y = vy;
	m_Velocity.z = 0.0f;

	m_Acceleration.x = ax;
	m_Acceleration.y = ay;
	m_Acceleration.z = 0.0f;

	m_Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR2(50.0f, 50.0f);
}

// パーティクルを発生させる
void TitleParticle::Generate()
{
	// 発生位置
	switch (m_TypeToGenerate)
	{
		// 左
	case 0:
		Begin(0.0f - 50.0f, static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT)), 2.0f, 0.0f, 0.0f, 0.0f);
		break;
		//右
	case 1:
		Begin(static_cast<float>(SCREEN_WIDTH) + 50.0f, static_cast<float>(myLib::Random::Rand_R(0, SCREEN_HEIGHT)), -2.0f, 0.0f, 0.0f, 0.0f);
		break;
		// 上
	case 2:
		Begin(static_cast<float>(myLib::Random::Rand_R(0, SCREEN_WIDTH)), 0.0f - 50.0f, 0.0f, 2.0f, 0.0f, 0.0f);
		break;
		// 下
	case 3:
		Begin(static_cast<float>(myLib::Random::Rand_R(0, SCREEN_WIDTH)), static_cast<float>(SCREEN_HEIGHT) + 50.0f, 0.0f, -2.0f, 0.0f, 0.0f);
		break;
	}
	// 次の生成位置を設定
	m_TypeToGenerate++;
	
	// 変数をリセットする
	if (m_TypeToGenerate > 3)
	{
		m_TypeToGenerate = 0;
	}
}
#pragma endregion TitleParticleメソッド

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
	// タイトル画面
	m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.49f, 0.9f));
}
void GameBg::TitleBg::SetTitleSystem(TitleSystem * Title)
{
	m_TitleSystem = Title;
}
#pragma endregion TitleBgメソッド