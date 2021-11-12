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
	m_TitleSystem = Engine::Get().application()->GetScene()->GetGameObject<TitleSystem>(ELayer::LAYER_2D_UI);
	uint32_t state = m_TitleSystem->GetState();

	if (m_TitleSystem->EState::SETTING_SELECT == state || m_TitleSystem->EState::CHECK_INPUT == state)
	{
		// Setting画面
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	}
	else
	{
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.49f, 1.0f));
	}
}
#pragma endregion TitleBgメソッド