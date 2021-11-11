/*--------------------------------------------------------------

	[TitleSystem.cpp]
	Author : 出合翔太

----------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "Application.h"
#include "Command.h"
#include "Renderer2D.h"
#include "TitleSystem.h"
#include "Fps.h"

TitleSystem::TitleSystem() : m_State(EState::BEGIN), m_Changecolor(0.01f)
{
	auto& g = Engine::Get().graphics();
	auto& r = Engine::Get().resource();

	m_Render = std::make_unique<Renderer2D>(*g, *r, "Ui");		
}

TitleSystem::~TitleSystem()
{
}

void TitleSystem::Begin()
{
}

void TitleSystem::Update()
{
	UpdateColorChenge();
	m_Alpha += m_Changecolor;
	if (m_Alpha < 0.5f)
	{
		m_Alpha = 0.5f;
		m_Changecolor *= -1;
	}
	else if (m_Alpha > 1.0f)
	{
		m_Alpha = 1.0f;
		m_Changecolor *= -1;
	}
}

void TitleSystem::Event()
{
}

void TitleSystem::Draw()
{
	switch (m_State)
	{
		// Press Any Buttonの表示
		case EState::BEGIN:
			m_Render->Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.0f), Math::Vector2(0.25f, 0.125f), m_Color);
			break;
		// GameStartorSetting
		case EState::SELECT:
			DrawSelect();
			break;
		// Setting
		case EState::SETTING_SELECT:
			DrawSetting();
			break;
		case EState::CHECK_INPUT:
			DrawInput();
			break;
	}
}

void TitleSystem::SetState(uint32_t State)
{
	m_State = State;
}

const uint32_t TitleSystem::GetState() const
{
	return m_State;
}

bool TitleSystem::GetCheckInput()
{
	return m_InputCheck;
}

void TitleSystem::EnableCheckInput()
{
	m_InputCheck = true;
}

void TitleSystem::DisableCheckInput()
{
	m_InputCheck = false;
}

const bool TitleSystem::GetInputGamePad() const
{
	return m_InputGamePad;
}

void TitleSystem::EnableGamePad()
{
	m_InputGamePad = true;
}

void TitleSystem::DisableGamePad()
{
	m_InputGamePad = false;
}

void TitleSystem::SelectTop()
{
	m_ToporButtom = true;
}

void TitleSystem::SelectButtom()
{
	m_ToporButtom = false;
}

const bool TitleSystem::GetSelect() const
{
	return m_ToporButtom;
}

#pragma region private_method
// カラーチェンジ
void TitleSystem::UpdateColorChenge()
{
	m_Color.x += m_Changecolor;
	m_Color.z += m_Changecolor;
	if (m_Color.x < 0.1f)
	{
		m_Color.x = 0.1f;
		m_Color.z = 0.1f;
		m_Changecolor *= -1;
	}
	else if (m_Color.x > 0.6f)
	{
		m_Color.x = 0.6f;
		m_Color.z = 0.6f;
		m_Changecolor *= -1;
	}
}
void TitleSystem::DrawSelect()
{
	Math::Vector4 beginColor = Math::Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	Math::Vector4 alpha = Math::Vector4(1.0f, 1.0f, 1.0f, m_Alpha);
	// 上を選んだ時はゲームスタートを選択、下を選んだときはSettingを選択している
	if (m_ToporButtom)
	{
		m_Render->Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f), alpha);
		m_Render->Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.0f), Math::Vector2(0.5f, 0.125f), m_Color);
		m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.125f), Math::Vector2(0.25f, 0.245f), beginColor);
	}
	else
	{
		m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f), alpha);
		m_Render->Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.0f), Math::Vector2(0.5f, 0.125f), beginColor);
		m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.125f), Math::Vector2(0.25f, 0.245f), m_Color);
	}
}

void TitleSystem::DrawSetting()
{
	Math::Vector4 clearColor = Math::Vector4(1.0f, 1.0f, 1.0f, 0.5f);
	if (m_InputGamePad == false)
	{
		m_Render->Draw(Math::Vector2(660.0f, 400.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.25f), Math::Vector2(0.5f, 0.375f));
		m_Render->Draw(Math::Vector2(1260.0f, 400.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.25f), Math::Vector2(0.25f, 0.3745f), clearColor);
		m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(1024.0f, 512.f), Math::Vector2(0.5f, 0.0f), Math::Vector2(1.0f, 0.5f));
	}
	else if (m_InputGamePad == true)
	{
		m_Render->Draw(Math::Vector2(660.0f, 400.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.25f), Math::Vector2(0.5f, 0.375f), clearColor);
		m_Render->Draw(Math::Vector2(1260.0f, 400.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.25f), Math::Vector2(0.25f, 0.3745f));
		m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(1024.0f, 512.f), Math::Vector2(0.5f, 0.5f), Math::Vector2(1.0f, 1.0f));
	}
}

void TitleSystem::DrawInput()
{
	if (m_InputGamePad == true)
	{
		if (m_InputCheck == false)
		{
			m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f));
			m_Render->Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.5f), Math::Vector2(0.5f, 0.625f));
			m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.625f), Math::Vector2(0.5f, 0.75f));
			m_Render->Draw(Math::Vector2(960.0f, 450.0f), Math::Vector2(1024.0f, 128.0f), Math::Vector2(0.0f, 0.75f), Math::Vector2(0.5f, 0.875f), m_Color);
		}
		else if (m_InputCheck == true)
		{
			m_Render->Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f));
			m_Render->Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.5f), Math::Vector2(0.5f, 0.625f));
			m_Render->Draw(Math::Vector2(960.0f, 750.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.625f), Math::Vector2(0.5f, 0.75f));
			m_Render->Draw(Math::Vector2(960.0f, 450.0f), Math::Vector2(1024.0f, 128.0f), Math::Vector2(0.0f, 0.75f), Math::Vector2(0.5f, 0.875f), m_Color);
		}
	}
}
#pragma endregion privateメソッド