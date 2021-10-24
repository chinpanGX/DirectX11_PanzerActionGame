/*-------------------------------------------------
	
	[ResultBg.cpp]
	Author : 出合翔太

---------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "Application.h"
#include "Renderer2D.h"
#include "ResultState.h"
#include "ResultBg.h"

#pragma region ResultBg_method
GameBg::ResultBg::ResultBg() : m_Count(0), m_Alpha(0.0f)
{
	m_Fade = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Bg");
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "ResultBg");
	m_State = std::make_unique<ResultState>();
}

GameBg::ResultBg::~ResultBg()
{
}

void GameBg::ResultBg::Begin()
{
}

void GameBg::ResultBg::Update()
{
	m_State->Update();
}

void GameBg::ResultBg::Event()
{
}

void GameBg::ResultBg::Draw()
{
	if (m_flag)
	{
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), Math::Vector2(0.0f, 0.0f), Math::Vector2(1.0f, 0.5f));
	}
	else
	{
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), Math::Vector2(0.0f, 0.5f), Math::Vector2(1.0f, 1.0f));
	}
	m_Fade->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), Math::Vector2(0.0f, 0.5f), Math::Vector2(0.5f, 1.0f), Math::Vector4(1.0f, 1.0f, 1.0f, m_State->GetAlpha()));
}

// 最初に呼び出す
void GameBg::ResultBg::Begin(bool winner)
{
	m_flag = winner;
}

ResultState & GameBg::ResultBg::GetState() const
{
	return *m_State;
}
#pragma endregion Resultメソッド

GameBg::ResultUi::ResultUi()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui02", Bg::GetSize() * 0.5f, Math::Vector2(512.0f, 384.0f));
	m_Marker = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui");
}

GameBg::ResultUi::~ResultUi()
{
}

void GameBg::ResultUi::Begin()
{

}

void GameBg::ResultUi::Update()
{
}

void GameBg::ResultUi::Event()
{
}

void GameBg::ResultUi::Draw()
{
	auto& state = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG)->GetState();
	float x = 1920.0f * 0.5f;
	Math::Vector2 size = Math::Vector2(512.0f, 128.0f);
	Math::Vector2 texMin = Math::Vector2(0.0f, 0.375f);
	Math::Vector2 texMax = Math::Vector2(0.25f, 0.5f);
	Math::Vector4 color = Math::Vector4(1.0f, 1.0f, 1.0f, state.GetAlpha());

	switch (state.GetSelect())
	{
	case 0:
		m_Marker->Draw(Math::Vector2(x, 410.0f), size, texMin, texMax, color);
		break;
	case 1:
		m_Marker->Draw(Math::Vector2(x, 550.0f), size, texMin, texMax, color);
		break;
	case 2:
		m_Marker->Draw(Math::Vector2(x, 680.0f), size, texMin, texMax, color);
		break;
	}
	m_Renderer2D->Draw(state.GetAlpha());
}