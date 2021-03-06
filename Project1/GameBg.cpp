/*------------------------------------------------------------

	[GameBg.cpp]
	Author : 出合翔太

	ゲームの2D背景

-------------------------------------------------------------*/
#include "Resource.h"
#include "Engine.h"
#include "Application.h"
#include "Renderer2D.h"
#include "TitleSystem.h"
#include "GameBg.h"
#include "GameCamera.h"
#include "PanzerContainer.h"
#include "Command.h"
#include "SelectCommand.h"
#include <string>
#include <vector>
#include <algorithm>

#pragma region Scope_method
GameBg::Scope::Scope()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Bg", Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.5f, 0.5f));
}

GameBg::Scope::~Scope()
{
}

void GameBg::Scope::Begin()
{
	m_Camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
}

void GameBg::Scope::Update()
{
}

void GameBg::Scope::Event()
{
}

void GameBg::Scope::Draw()
{
	// カメラがFPSモードのときにスコープを描画する
	if(m_Camera->FpsModeNow() == true)
	{
		m_Renderer2D->Draw();
	}
}
#pragma endregion Scopeクラスのメソッド

#pragma region PanzerSelectUi_method
GameBg::PanzerSelectUi::PanzerSelectUi()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "SelectUi");
	m_Render[0] = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui03");
	m_Render[1] = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "SelectList");
	m_Render[2] = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui05");
	
	// 戦車名のTexture座標
	m_TexCoord = 
	{ 
		D3DXVECTOR2(0.0f, 0.25f), 
		D3DXVECTOR2(0.0f, 0.5f), 
		D3DXVECTOR2(0.0f, 0.75f), 
		D3DXVECTOR2(0.25f, 0.5f), 
		D3DXVECTOR2(0.25f, 0.75f), 
		D3DXVECTOR2(0.5f, 0.0f) 
	};
}

GameBg::PanzerSelectUi::~PanzerSelectUi()
{
}

void GameBg::PanzerSelectUi::Begin()
{
	m_Container = Engine::Get().GetApplication()->GetScene()->GetGameObject<PanzerContainer>(LAYER_3D_ACTOR);
}

void GameBg::PanzerSelectUi::Update()
{
	// 上
	if (m_Container->GetButton() == 1)
	{
		std::rotate(m_TexCoord.rbegin(), m_TexCoord.rbegin() + 1, m_TexCoord.rend());
	}
	// 下
	else if (m_Container->GetButton() == 2)
	{
		// 配列を左シフト
		std::rotate(m_TexCoord.begin(), m_TexCoord.begin() + 1, m_TexCoord.end());
	}
	// 選択をリセット
	m_Container->Reset();
}

void GameBg::PanzerSelectUi::Event()
{
}

void GameBg::PanzerSelectUi::Draw()
{
	D3DXVECTOR2 Position = Bg::GetSize() * 0.5f;
	D3DXVECTOR2 Size = Bg::GetSize();

	// 背景
	m_Renderer2D->Draw(Position, Size, D3DXVECTOR2(0.5f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));

	auto op_pos = D3DXVECTOR2(960.0f, 960.0f);
	auto op_size = D3DXVECTOR2(500.0f, 70.0f);
	
	// 操作方法の説明	
	m_Render[0]->Draw(op_pos, op_size, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	
	// 戦車の名前
	DrawPanzerName();

	// ゲーム説明
	DrawGameRule(Position, Size);
}

void GameBg::PanzerSelectUi::Down()
{
	m_Page--;
	if (m_Page < 0)
	{
		Disable();
	}
}

void GameBg::PanzerSelectUi::Up()
{
	m_Page++;
	if (m_Page > 4)
	{
		Disable();
	}
}

void GameBg::PanzerSelectUi::Enable()
{
	m_DrawFlag = true;
}

void GameBg::PanzerSelectUi::Disable()
{
	if (m_DrawFlag)
	{
		m_DrawFlag = false;
		m_Page = 0; // 最初のページに戻す
	}
}

const bool GameBg::PanzerSelectUi::GetDrawFlag() const
{
	return m_DrawFlag;
}

void GameBg::PanzerSelectUi::DrawPanzerName()
{
	// 描画する4つ
	std::array<float, 4> position = { 1.0f, 1.25f, 1.5f, 0.75f };
	// 描画位置の補正
	float x = Bg::GetWidth() * 0.1f + 30.0f;
	float y = Bg::GetHeight() * 0.5f + 30.0f;

	// 戦車のリスト
	// 配列の先頭から3つ
	auto offset = D3DXVECTOR2(0.25f, 0.25f);
	for (int32_t i = 0; i < 3; ++i)
	{
		m_Render[1]->Draw(D3DXVECTOR2(x, y * position[i]), D3DXVECTOR2(432.0f, 128.0f), m_TexCoord[i], m_TexCoord[i] + offset);
	}

	// 配列の一番最後	
	D3DXVECTOR2 end = m_TexCoord.back();
	m_Render[1]->Draw(D3DXVECTOR2(x, y * position[3]), D3DXVECTOR2(432.0f, 128.0f), end, end + offset);

	// 枠の描画
	m_Render[1]->Draw(D3DXVECTOR2(x, y), D3DXVECTOR2(432.0f, 128.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 0.25f));
}

void GameBg::PanzerSelectUi::DrawGameRule(D3DXVECTOR2 Position, D3DXVECTOR2 Size)
{
	// ゲームの説明
	if (m_DrawFlag)
	{
		switch (m_Page)
		{
		case 0:
			m_Renderer2D->Draw(Position, Size, D3DXVECTOR2(0.0f, 0.02f), D3DXVECTOR2(0.5f, 0.52f));
			break;
		case 1:
			m_Renderer2D->Draw(Position, Size, D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.5f, 1.0f));			
			break;
		case 2:
			m_Renderer2D->Draw(Position, Size, D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
			break;
		case 3:
			m_Render[2]->Draw(Position, Size, D3DXVECTOR2(0.0, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
			break;
		case 4:
			m_Render[2]->Draw(Position, Size, D3DXVECTOR2(0.0, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			break;
		}
	}
}
#pragma endregion PranzerSelectUi_method

#pragma region モード選択
GameBg::Mode::Mode()
{
	m_Renderer2D = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "SelectList");
	m_BgFrame = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Ui");
}

GameBg::Mode::~Mode()
{
}

void GameBg::Mode::Begin()
{
	m_Command = Engine::Get().GetApplication()->GetScene()->GetGameObject<SelectCommand>(ELayer::LAYER_SYSTEM);
}

void GameBg::Mode::Update()
{
	m_Alpha += m_Color;
	if (m_Alpha < 0.4f)
	{
		m_Alpha = 0.4f;
		m_Color *= -1;
	}
	else if (m_Alpha > 1.0f)
	{
		m_Alpha = 1.0f;
		m_Color *= -1;
	}

	// ゲームモードを選択していないとき
	if (m_Command->GetSelect() == true)
	{
		m_Alpha = 1.0f;
	}
}

void GameBg::Mode::Event()
{
}

void GameBg::Mode::Draw()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(1600.0f, 900.0f);
	float size_y = 128.0f;
	// 背景枠
	DrawFrame(pos, size_y);
	// ゲームモード
	DrawModeName(pos, size_y);
}

bool GameBg::Mode::SetMode(bool f)
{
	m_TutorialMode = f;
	return m_TutorialMode;
}

// 背景の枠を描画する
void GameBg::Mode::DrawFrame(D3DXVECTOR2 Position, float Size_y)
{
	auto Size = D3DXVECTOR2(512.0f, Size_y);
	auto ul = D3DXVECTOR2(0.0f, 0.375f);
	auto lr = D3DXVECTOR2(0.25f, 0.5f);
	m_Renderer2D->Draw(Position, Size, ul, lr, D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_Alpha));
	
}

// ゲームモードの表示
void GameBg::Mode::DrawModeName(D3DXVECTOR2 Position, float Size_y)
{
	if (m_TutorialMode)
	{
		// チュートリアル
		m_Renderer2D->Draw(Position, D3DXVECTOR2(432.0f, Size_y), D3DXVECTOR2(0.25f, 0.25f), D3DXVECTOR2(0.5f, 0.5f));
	}
	else
	{
		// ゲーム
		m_Renderer2D->Draw(Position, D3DXVECTOR2(432.0f, Size_y), D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 0.25f));
	}
}
#pragma endregion Mode_method

#pragma region チュートリアルの操作方法の描画
GameBg::TutorialUi::TutorialUi()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui04");
}

GameBg::TutorialUi::~TutorialUi()
{
}

void GameBg::TutorialUi::Begin()
{
}

void GameBg::TutorialUi::Update()
{
}

void GameBg::TutorialUi::Event()
{
}

void GameBg::TutorialUi::Draw()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(1700.0f, 600.0f);
	D3DXVECTOR2 size = D3DXVECTOR2(432.0f, 432.0f);
	D3DXVECTOR2 min = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 max = D3DXVECTOR2(1.0f, 1.0f);

	m_Renderer2D->Draw(pos, size, min, max);
}
#pragma endregion チュートリアルの操作方法の描画 