/*-------------------------------------------------------------

	[TitleCommand.cpp]
	Author : 出合翔太

	タイトルシーンの入力処理の管理

--------------------------------------------------------------*/
#include "Command.h"
#include "TitleSystem.h"
#include "TitleCommand.h"
#include "Input.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "GameScene.h"

namespace
{
	bool g_EndSetting = true; // false; // 設定済みかどうか
}

TitleCommand::TitleCommand() {}
TitleCommand::~TitleCommand() {}
void TitleCommand::Begin()
{
}

void TitleCommand::Update()
{
	m_TitleSystem = Engine::Get().application()->GetScene()->GetGameObject<TitleSystem>(ELayer::LAYER_2D_UI);
	uint32_t state = m_TitleSystem->GetState();
	// 初めの画面
	if (m_TitleSystem->EState::BEGIN == state)
	{
 		BeginInput();
	}
	// 
	else if (m_TitleSystem->EState::SELECT == state)
	{
		// 最初はキーボードマウス、ゲームパッド両方入力できるようにする
		// 設定済みで無ければ、両方入力できる
		if (g_EndSetting == false)
		{
			InputKeyBoard();
			//InputGamePad();
		}
		else
		{
			g_IsInputGamePad ? InputGamePad() : InputKeyBoard();
		}
	}
#if 0
	else if (m_TitleSystem->EState::SETTING_SELECT == state || m_TitleSystem->EState::CHECK_INPUT == state)
	{
		// 最初はキーボードマウス、ゲームパッド両方入力できるようにする
		InputKeyBoard();
		//InputGamePad();
	}
#endif
}
void TitleCommand::Event() {}
void TitleCommand::Draw() {}

void TitleCommand::BeginInput()
{
	// Any Pressで入力できるようにする

	// キーボード
	for (int32_t i = 0; i < 256; ++i)
	{
		if (KeyBoard::IsTrigger(i))
		{
			m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
		}
	}

	// ゲームパッド
	if (GamePad::IsTrigger(0, BUTTON_1)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_2)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_3)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_4)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_UP)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_DOWN)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_RIGHT)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_LEFT)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_OPTION)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	//if (GamePad::IsTrigger(0, TRIGGER_L2)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	//if (GamePad::IsTrigger(0, TRIGGER_R2)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_L1)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_R1)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, LEFTSTICK_UP)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, LEFTSTICK_DOWN)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, LEFTSTICK_RIGHT)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, LEFTSTICK_LEFT)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, RIGHTSTICK_LEFT)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, RIGHTSTICK_RIGHT)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, RIGHTSTICK_UP)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, RIGHTSTICK_DOWN)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
}

// キーボードの入力
void TitleCommand::InputKeyBoard()
{
	uint32_t state = m_TitleSystem->GetState();
	// 選択画面のとき
	if (m_TitleSystem->EState::SELECT == state)
	{
// 選択ができないようにする
#if 0
		// 選択
		if (KeyBoard::IsTrigger(DIK_W))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectTop();
		}
		else if (KeyBoard::IsTrigger(DIK_S))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectButtom();
		}
#endif
		// 決定
		if (KeyBoard::IsTrigger(DIK_SPACE) || Mouse::LeftTrigger())
		{
			// ゲームスタートへシーンチェンジ
			if (m_TitleSystem->GetSelect())
			{
				//　シーンチェンジ
				Engine::Get().application()->SetScene<GameScene::PanzerSelect>();
				Engine::Get().resource()->AudioPlay("Enter", 1.0f);
			}
#if 0
			// 設定画面へ
			else if (!m_TitleSystem->GetSelect())
			{
				Engine::Get().resource()->AudioPlay("Button", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SETTING_SELECT);
			}
#endif
		}
		// 戻る
		if (KeyBoard::IsTrigger(DIK_Q))
		{
			Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
			m_TitleSystem->SetState(m_TitleSystem->EState::BEGIN);
		}

	}

#if 0
	// 設定画面
	if (m_TitleSystem->EState::SETTING_SELECT == state)
	{
		if (KeyBoard::IsTrigger(DIK_A))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->DisableGamePad();
		}
		else if (KeyBoard::IsTrigger(DIK_D))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableGamePad();
		}
		// 決定
		else if (KeyBoard::IsTrigger(DIK_SPACE) || Mouse::LeftTrigger())
		{
			if (m_TitleSystem->GetInputGamePad())
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::CHECK_INPUT);
			}
			else
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
			}
		}
	}

	// ゲームパッドに変更するかチェックする
	if (m_TitleSystem->EState::CHECK_INPUT == state)
	{
		if (KeyBoard::IsTrigger(DIK_W))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableCheckInput();
		}
		else if (KeyBoard::IsTrigger(DIK_S))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->DisableCheckInput();
		}
		else if (KeyBoard::IsTrigger(DIK_SPACE))
		{
			Engine::Get().resource()->AudioPlay("Button", 1.0f);
			g_IsInputGamePad = m_TitleSystem->GetCheckInput();
			m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
			g_EndSetting = true;
		}
	}
#endif 	
}

// ゲームパッドの入力
void TitleCommand::InputGamePad()
{
	uint32_t state = m_TitleSystem->GetState();
	// 選択画面のとき
	if (m_TitleSystem->EState::SELECT == state)
	{
		// 選択
		if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectTop();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectButtom();
		}
		// 決定
		if (GamePad::IsTrigger(0, BUTTON_2))
		{
			if (m_TitleSystem->GetSelect())
			{
				Engine::Get().resource()->AudioPlay("Enter", 1.0f);
				//　シーンチェンジ
				Engine::Get().application()->SetScene<GameScene::PanzerSelect>();
			}
#if 0 
			// 設定画面へ
			else if (!m_TitleSystem->GetSelect())
			{
				Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SETTING_SELECT);
			}
#endif
		}
		// 戻る
		if (GamePad::IsTrigger(0, BUTTON_3))
		{
			Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
			m_TitleSystem->SetState(m_TitleSystem->EState::BEGIN);
		}

	}
// ゲームパッドは選択できないようにする
#if 0
	// 設定画面
	if (m_TitleSystem->EState::SETTING_SELECT == state)
	{
		if (GamePad::IsTrigger(0, LEFTSTICK_LEFT) || GamePad::IsTrigger(0, BUTTON_LEFT))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->DisableGamePad();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_RIGHT) || GamePad::IsTrigger(0, BUTTON_LEFT))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableGamePad();
		}
		// 決定
		// キーボードからゲームパッドに変更しようとしているとき
		if (!g_IsInputGamePad)
		{
			if (GamePad::IsTrigger(0, BUTTON_2))
			{
				if (m_TitleSystem->GetInputGamePad())
				{
					m_TitleSystem->SetState(m_TitleSystem->EState::CHECK_INPUT);
				}
				else
				{
					Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
					m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
				}
			}
		}
	}

	if (m_TitleSystem->EState::CHECK_INPUT == state)
	{
		if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableCheckInput();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->DisableCheckInput();
		}
		else if (GamePad::IsTrigger(0, BUTTON_2))
		{
			g_IsInputGamePad = m_TitleSystem->GetCheckInput();
			m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
			g_EndSetting = true;
		}
	}
#endif
}
#pragma endregion TitleCommandのメソッド
