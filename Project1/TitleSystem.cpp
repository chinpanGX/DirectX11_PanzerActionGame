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
	// α値の変更
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
			m_Render->Draw(D3DXVECTOR2(960.0f, 600.0f), D3DXVECTOR2(512.0f, 128.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 0.125f), m_Color);
			break;
		// Game or Setting　の選択
		case EState::SELECT:
			DrawSelect();
			break;
		// Setting画面
		case EState::SETTING_SELECT:
			DrawSetting();
			break;
		// Deviceの変更のチェック
		case EState::CHECK_INPUT:
			DrawInput();
			break;
	}
}

#pragma region _SelectionStatus_
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
#pragma endregion _選択状況_

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

// Game or Settingの画面
void TitleSystem::DrawSelect()
{
	// 共通変数
	D3DXVECTOR4 beginColor = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	D3DXVECTOR4 alpha = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_Alpha);
	D3DXVECTOR2 size = D3DXVECTOR2(512.0f, 128.0f);
	float px = 960.0f; // ｘ座標の位置

	// 上を選んだ時はゲームスタートを選択、下を選んだときはSettingを選択している
	if (m_ToporButtom)
	{
		m_Render->Draw(D3DXVECTOR2(px, 600.0f), size, D3DXVECTOR2(0.0f, 0.375f), D3DXVECTOR2(0.25f, 0.5f), alpha);
		m_Render->Draw(D3DXVECTOR2(px, 600.0f), size, D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 0.125f), m_Color);
		m_Render->Draw(D3DXVECTOR2(px, 750.0f), size, D3DXVECTOR2(0.0f, 0.125f), D3DXVECTOR2(0.25f, 0.245f), beginColor);
	}
	else
	{
		m_Render->Draw(D3DXVECTOR2(px, 750.0f), size, D3DXVECTOR2(0.0f, 0.375f), D3DXVECTOR2(0.25f, 0.5f), alpha);
		m_Render->Draw(D3DXVECTOR2(px, 600.0f), size, D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 0.125f), beginColor);
		m_Render->Draw(D3DXVECTOR2(px, 750.0f), size, D3DXVECTOR2(0.0f, 0.125f), D3DXVECTOR2(0.25f, 0.245f), m_Color);
	}
}

// Settingの画面
void TitleSystem::DrawSetting()
{
	D3DXVECTOR4 clearColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f);
	float sx = 512.0f; // サイズx座標
	// キーボード
	if (m_InputGamePad == false)
	{
		m_Render->Draw(D3DXVECTOR2(660.0f, 400.0f), D3DXVECTOR2(sx, 128.0f), D3DXVECTOR2(0.25f, 0.25f), D3DXVECTOR2(0.5f, 0.375f));
		m_Render->Draw(D3DXVECTOR2(1260.0f, 400.0f), D3DXVECTOR2(sx, 128.0f), D3DXVECTOR2(0.0f, 0.25f), D3DXVECTOR2(0.25f, 0.3745f), clearColor);
		m_Render->Draw(D3DXVECTOR2(960.0f, 750.0f), D3DXVECTOR2(sx * 2.0f, 512.f), D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	}
	// ゲームパッド
	else if (m_InputGamePad == true)
	{
		m_Render->Draw(D3DXVECTOR2(660.0f, 400.0f), D3DXVECTOR2(sx, 128.0f), D3DXVECTOR2(0.25f, 0.25f), D3DXVECTOR2(0.5f, 0.375f), clearColor);
		m_Render->Draw(D3DXVECTOR2(1260.0f, 400.0f), D3DXVECTOR2(sx, 128.0f), D3DXVECTOR2(0.0f, 0.25f), D3DXVECTOR2(0.25f, 0.3745f));
		m_Render->Draw(D3DXVECTOR2(960.0f, 750.0f), D3DXVECTOR2(sx * 2.0f, 512.f), D3DXVECTOR2(0.5f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}
}

// デバイスを変更してもいいかのチェック画面
void TitleSystem::DrawInput()
{
	// 共通変数
	float px = 960.0f; // x座標
	float sx = 512.0f; // サイズx座標
	float sy = 128.0f; // サイズy座標
	if (m_InputGamePad == true)
	{
		// いいえ
		if (m_InputCheck == false)
		{
			m_Render->Draw(D3DXVECTOR2(px, 750.0f), D3DXVECTOR2(sx, sy), D3DXVECTOR2(0.0f, 0.375f), D3DXVECTOR2(0.25f, 0.5f));
			m_Render->Draw(D3DXVECTOR2(px, 600.0f), D3DXVECTOR2(sx, sy), D3DXVECTOR2(0.25f, 0.5f), D3DXVECTOR2(0.5f, 0.625f));
			m_Render->Draw(D3DXVECTOR2(px, 750.0f), D3DXVECTOR2(sx, sy), D3DXVECTOR2(0.25f, 0.625f), D3DXVECTOR2(0.5f, 0.75f));
			m_Render->Draw(D3DXVECTOR2(px, 450.0f), D3DXVECTOR2(sx * 2.0f, sy), D3DXVECTOR2(0.0f, 0.75f), D3DXVECTOR2(0.5f, 0.875f), m_Color);
		}
		// はい
		else if (m_InputCheck == true)
		{
			m_Render->Draw(D3DXVECTOR2(px, 600.0f), D3DXVECTOR2(sx, sy), D3DXVECTOR2(0.0f, 0.375f), D3DXVECTOR2(0.25f, 0.5f));
			m_Render->Draw(D3DXVECTOR2(px, 600.0f), D3DXVECTOR2(sx, sy), D3DXVECTOR2(0.25f, 0.5f), D3DXVECTOR2(0.5f, 0.625f));
			m_Render->Draw(D3DXVECTOR2(px, 750.0f), D3DXVECTOR2(sx, sy), D3DXVECTOR2(0.25f, 0.625f), D3DXVECTOR2(0.5f, 0.75f));
			m_Render->Draw(D3DXVECTOR2(px, 450.0f), D3DXVECTOR2(sx * 2.0f, sy), D3DXVECTOR2(0.0f, 0.75f), D3DXVECTOR2(0.5f, 0.875f), m_Color);
		}
	}
}
#pragma endregion privateメソッド