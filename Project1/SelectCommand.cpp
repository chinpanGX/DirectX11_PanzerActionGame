/*-------------------------------------------------------------

	[SelectCommand.cpp]
	Author : 出合翔太

	戦車選択シーンの入力処理の管理

--------------------------------------------------------------*/
#include "Command.h"
#include "GameBg.h"
#include "PanzerContainer.h"
#include "SelectCommand.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Input.h"
#include "GameScene.h"
#include "TitleScene.h"

#pragma region SelectCommand_method
SelectCommand::SelectCommand() { m_Container = Engine::Get().application()->GetScene()->GetGameObject<PanzerContainer>(LAYER_3D_ACTOR); }
SelectCommand::~SelectCommand() {}
void SelectCommand::Begin()
{
	m_Ui = Engine::Get().application()->GetScene()->GetGameObject<GameBg::PanzerSelectUi>(ELayer::LAYER_2D_UI);
}
void SelectCommand::Update() { g_IsInputGamePad ? InputGamePad() : InputKeyBoard(); }
void SelectCommand::Event() {}
void SelectCommand::Draw() {}
const bool SelectCommand::GetSelect() const { return m_Select; }

// キーボード入力
void SelectCommand::InputKeyBoard()
{
	// ゲーム説明を表示する
	if (m_Ui->GetDrawFlag())
	{
		if (KeyBoard::IsTrigger(DIK_D))
		{
			m_Ui->Up();
		}
		else if (KeyBoard::IsTrigger(DIK_A))
		{
			m_Ui->Down();
		}
		else if (KeyBoard::IsTrigger(DIK_Q))
		{
			m_Ui->Disable();
		}
	}
	// 説明を表示しない
	else
	{
		// 戦車の選択
		if (m_Select)
		{
			if (KeyBoard::IsTrigger(DIK_W))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Container->SetChooseUp();
			}
			else if (KeyBoard::IsTrigger(DIK_S))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Container->SetChooseDown();
			}
			else if (KeyBoard::IsTrigger(DIK_Q))
			{
				Engine::Get().application()->SetScene<GameScene::Title>();
			}
			else if (KeyBoard::IsTrigger(DIK_D))
			{
				m_Ui->Enable();
				Engine::Get().resource()->AudioPlay("Button", 1.0f);
			}
			else if (KeyBoard::IsTrigger(DIK_SPACE))
			{
				m_Select = false;
				Engine::Get().resource()->AudioPlay("Button", 1.0f);
			}
		}
		// ゲームモードの選択
		else
		{
			if (KeyBoard::IsTrigger(DIK_W))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Mode = Engine::Get().application()->GetScene()->GetGameObject<GameBg::Mode>(ELayer::LAYER_2D_BG)->SetMode(false);
			}
			else if (KeyBoard::IsTrigger(DIK_S))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Mode = Engine::Get().application()->GetScene()->GetGameObject<GameBg::Mode>(ELayer::LAYER_2D_BG)->SetMode(true);
			}
			else if (KeyBoard::IsTrigger(DIK_Q))
			{
				m_Select = true;
				Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
			}
			else if (KeyBoard::IsTrigger(DIK_SPACE))
			{
				// シーンのロード
				Engine::Get().resource()->AudioPlay("Enter", 1.0f);
				m_Mode ? Engine::Get().application()->SetScene<GameScene::Game>() : Engine::Get().application()->SetScene<GameScene::Tutorial>();
			}
		}
	}
}

// ゲームパッドの入力
void SelectCommand::InputGamePad()
{
	// ゲーム説明を表示する
	if (m_Ui->GetDrawFlag())
	{
		if (GamePad::IsTrigger(0, LEFTSTICK_RIGHT) || GamePad::IsTrigger(0, BUTTON_RIGHT))
		{
			m_Ui->Up();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_LEFT) || GamePad::IsTrigger(0, BUTTON_LEFT))
		{
			m_Ui->Down();
		}
		else if (GamePad::IsTrigger(0, BUTTON_3))
		{
			m_Ui->Disable();
		}
	}
	// 説明を表示しない
	else
	{
		if (m_Select)
		{
			if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Container->SetChooseUp();
			}
			else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Container->SetChooseDown();
			}
			else if (GamePad::IsTrigger(0, BUTTON_2))
			{
				m_Select = false;
				Engine::Get().resource()->AudioPlay("Button", 1.0f);
			}
		}
		else
		{
			if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Mode = Engine::Get().application()->GetScene()->GetGameObject<GameBg::Mode>(ELayer::LAYER_2D_BG)->SetMode(false);
			}
			else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Mode = Engine::Get().application()->GetScene()->GetGameObject<GameBg::Mode>(ELayer::LAYER_2D_BG)->SetMode(true);
			}
			else if (GamePad::IsTrigger(0, BUTTON_3))
			{
				m_Select = true;
				Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
			}
			else if (GamePad::IsTrigger(0, BUTTON_2))
			{
				Engine::Get().resource()->AudioPlay("Enter", 1.0f);
				// シーンのロード
				m_Mode ? Engine::Get().application()->SetScene<GameScene::Game>() : Engine::Get().application()->SetScene<GameScene::Tutorial>();
			}
		}
	}

}
#pragma endregion SelectCommandメソッド