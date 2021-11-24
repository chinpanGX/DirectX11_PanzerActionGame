/*-----------------------------------------------------------

	[Command.cpp]
	Author : 出合翔太

	コマンド

-------------------------------------------------------------*/
#include "TitleScene.h"
#include "ResultState.h"
#include "GameBg.h"
#include "Input.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "GameScene.h"
#include "Player.h"
#include "Pivot.h"
#include "NormalBullet.h"
#include "GameCamera.h"
#include "Fps.h"
#include "PanzerContainer.h"
#include "Controller.h"
#include "TitleSystem.h"
#include "ResultBg.h"
#include "Pause.h"
#include "Command.h"
#include "ResultScene.h"

namespace
{
	bool g_EndSetting = false; // 設定済みかどうか
}

#pragma region TitleCommand_method
TitleCommand::TitleCommand() {}
TitleCommand::~TitleCommand() {}
void TitleCommand::Begin() {}

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
			InputGamePad();
		}
		else
		{
			g_IsInputGamePad ? InputGamePad() : InputKeyBoard();
		}
	}
	else if (m_TitleSystem->EState::SETTING_SELECT == state || m_TitleSystem->EState::CHECK_INPUT == state)
	{
		// 最初はキーボードマウス、ゲームパッド両方入力できるようにする
		InputKeyBoard();
		InputGamePad();
	}
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
	if (GamePad::IsTrigger(0, BUTTON_1))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_2))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_3))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_4))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_UP))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_DOWN))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_RIGHT))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_LEFT))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_OPTION))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, TRIGGER_L2))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, TRIGGER_R2))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_L1))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, BUTTON_R1))		{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0, LEFTSTICK_UP))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0,LEFTSTICK_DOWN))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0,LEFTSTICK_RIGHT))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0,LEFTSTICK_LEFT))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0,RIGHTSTICK_LEFT))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0,RIGHTSTICK_RIGHT)) { m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0,RIGHTSTICK_UP))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
	if (GamePad::IsTrigger(0,RIGHTSTICK_DOWN))	{ m_TitleSystem->SetState(m_TitleSystem->EState::SELECT); }
}

// キーボードの入力
void TitleCommand::InputKeyBoard()
{
	uint32_t state = m_TitleSystem->GetState();	
	// 選択画面のとき
	if (m_TitleSystem->EState::SELECT == state)
	{
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
			// 設定画面へ
			else if (!m_TitleSystem->GetSelect())
			{
				Engine::Get().resource()->AudioPlay("Button", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SETTING_SELECT);
			}
		}
		// 戻る
		if (KeyBoard::IsTrigger(DIK_Q))
		{
			Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
			m_TitleSystem->SetState(m_TitleSystem->EState::BEGIN);
		}

	}

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
			// 設定画面へ
			else if (!m_TitleSystem->GetSelect())
			{
				Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SETTING_SELECT);
			}
		}
		// 戻る
		if (GamePad::IsTrigger(0, BUTTON_3))
		{
			Engine::Get().resource()->AudioPlay("Cancel", 1.0f);
			m_TitleSystem->SetState(m_TitleSystem->EState::BEGIN);
		}

	}
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
}
#pragma endregion TitleCommandのメソッド

#pragma region GameCommand
GameCommand::GameCommand()
{
	// カメラの操作
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	// プレイヤーの操作
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	// 戦車の操縦
	auto& Pivot = m_Player->pivot();
	m_Controller = std::make_unique<Controller>(m_Player, camera, &Pivot);

	// 
	m_NowInput.resize(11);
}
GameCommand::~GameCommand() {}
void GameCommand::Begin() {}

void GameCommand::Update()
{
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
	float deltaTime = Fps::Get().deltaTime;

	// デバッグ用
	if (KeyBoard::IsTrigger(DIK_T))
	{
		Engine::Get().application()->SetScene <GameScene::Title>();
	}
	if (KeyBoard::IsTrigger(DIK_Y))
	{
		Engine::Get().application()->SetScene<GameScene::Result>();
	}

	if (!g_IsInputGamePad)
	{
		if (!pause->NowPausing())
		{
			InputKeyboard(deltaTime);
		}
	}
	else if (g_IsInputGamePad)
	{
		if (!pause->NowPausing())
		{
			InputGamePad(deltaTime);
		}
	}
}

void GameCommand::Event() {}
void GameCommand::Draw() {}
bool GameCommand::GetNowInput(int32_t i) const { return m_NowInput[i]; }

// キーボード入力
void GameCommand::InputKeyboard(float deltaTime)
{
	// 入力状態をリセット
	for (auto i : m_NowInput)
	{
		i = false;
	}
	m_Controller->FpsCameraMode(false);

	// 現在のマウスポインタ
	m_Mouse.y = (Mouse::GetMouseY() - m_OldMouse.y) * 0.08f;
	m_Mouse.x = (Mouse::GetMouseX() - m_OldMouse.x) * 0.02f;
	
	// カメラモードをFPSにする
	if (Mouse::RightPress())
	{
		m_NowInput[9] = true;
		m_Controller->FpsCameraMode(true);
	}

	// 戦車（ボディ）の移動
	if (KeyBoard::IsPress(DIK_W))
	{
		m_NowInput[0] = true;
		m_Controller->MoveForward(deltaTime);
	}
	if (KeyBoard::IsPress(DIK_S))
	{
		m_NowInput[1] = true;
		m_Controller->MoveBackward(deltaTime);
	}
	if (KeyBoard::IsPress(DIK_D))
	{
		m_NowInput[2] = true;
		m_Controller->RotRight(deltaTime);
	}
	if (KeyBoard::IsPress(DIK_A))
	{
		m_NowInput[3] = true;
		m_Controller->RotLeft(deltaTime);
	}
	// 戦車（タレット）の回転
	if (m_Mouse.x < m_OldMouse.x - 2.5f)
	{
		m_NowInput[4] = true;
		m_Controller->RotTurretRight(deltaTime);
	}
	else if (m_Mouse.x > m_OldMouse.x + 5.0f)
	{
		m_NowInput[5] = true;
		m_Controller->RotTurretLeft(deltaTime);
	}

	// 砲台の上下
	if (m_Mouse.y > m_OldMouse.y + 2.5f)
	{
		m_NowInput[6] = true;
		m_Controller->RotMaingunUp(deltaTime);
	}
	else if (m_Mouse.y < m_OldMouse.y - 2.5f)
	{
		m_NowInput[7] = true;
		m_Controller->RotMaingunDown(deltaTime);
	}

	// 砲弾を撃つ
	if (Mouse::LeftTrigger())
	{
		m_NowInput[8] = true;
		m_Controller->Shot();
	}

	// スキルを使う
	if (KeyBoard::IsTrigger(DIK_E))
	{
		m_NowInput[10] = true;
		m_Controller->UseSkill();
	}
	// 1f前のマウスポインタ
	m_OldMouse.x = (float)Mouse::GetMouseX();
	m_OldMouse.y = (float)Mouse::GetMouseY();
}

// ゲームパッドの入力
void GameCommand::InputGamePad(float deltaTime)
{
	// 入力状態をリセット
// 入力状態をリセット
	for (auto i : m_NowInput)
	{
		i = false;
	}
	m_Controller->FpsCameraMode(false);

	// カメラモードをFPSにする
	if (GamePad::IsPress(0, TRIGGER_L2))
	{
		m_NowInput[9] = true;
		m_Controller->FpsCameraMode(true);
	}

	// 戦車（ボディ）の移動
	if (GamePad::IsPress(0, LEFTSTICK_UP))
	{
		if (!m_Player->CollisionEnter())
		{
			m_NowInput[0] = true;
			m_Controller->MoveForward(deltaTime);
		}
	}
	if (GamePad::IsPress(0, LEFTSTICK_DOWN))
	{
		m_NowInput[1] = true;
		m_Controller->MoveBackward(deltaTime);
	}
	if (GamePad::IsPress(0, LEFTSTICK_RIGHT))
	{
		m_NowInput[2] = true;
		m_Controller->RotRight(deltaTime);
	}
	if (GamePad::IsPress(0, LEFTSTICK_LEFT))
	{
		m_NowInput[3] = true;
		m_Controller->RotLeft(deltaTime);
	}
	// 戦車（タレット）の回転
	if (GamePad::IsPress(0, RIGHTSTICK_RIGHT))
	{
		m_NowInput[4] = true;
		m_Controller->RotTurretRight(deltaTime);
	}
	else if (GamePad::IsPress(0, RIGHTSTICK_LEFT))
	{
		m_NowInput[5] = true;
		m_Controller->RotTurretLeft(deltaTime);
	}

	// 砲台の上下
	if (GamePad::IsPress(0, RIGHTSTICK_UP))
	{
		m_NowInput[6] = true;
		m_Controller->RotMaingunUp(deltaTime);
	}
	else if (GamePad::IsPress(0, RIGHTSTICK_DOWN))
	{
		m_NowInput[7] = true;
		m_Controller->RotMaingunDown(deltaTime);
	}

	// 砲弾を撃つ
	if (GamePad::IsTrigger(0, TRIGGER_R2))
	{
		m_NowInput[8] = true;
		m_Controller->Shot();
	}

	// スキルを使う
	if (GamePad::IsTrigger(0, BUTTON_1))
	{
		m_NowInput[10] = true;
		m_Controller->UseSkill();
	}
}
#pragma endregion GameCommandメソッド

#pragma region SelectCommand_method
SelectCommand::SelectCommand() { m_Container = Engine::Get().application()->GetScene()->GetGameObject<PanzerContainer>(LAYER_3D_ACTOR); }
SelectCommand::~SelectCommand() {}
void SelectCommand::Begin() {}
void SelectCommand::Update() { g_IsInputGamePad ? InputGamePad() : InputKeyBoard(); }
void SelectCommand::Event() {}
void SelectCommand::Draw() {}
const bool SelectCommand::GetSelect() const { return m_Select; }

// キーボード入力
void SelectCommand::InputKeyBoard()
{
	auto explain = Engine::Get().application()->GetScene()->GetGameObject<GameBg::PanzerSelectUi>(ELayer::LAYER_2D_UI);
	// ゲーム説明を表示する
	if(explain->GetDrawFlag())
	{
		if (KeyBoard::IsTrigger(DIK_D))
		{
			explain->Up();
		}
		else if(KeyBoard::IsTrigger(DIK_A))
		{
			explain->Down();
		}
		else if(KeyBoard::IsTrigger(DIK_Q))
		{
			explain->Disable();
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
				explain->Enable();
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
	auto explain = Engine::Get().application()->GetScene()->GetGameObject<GameBg::PanzerSelectUi>(ELayer::LAYER_2D_UI);
	// ゲーム説明を表示する
	if (explain->GetDrawFlag())
	{
		if (GamePad::IsTrigger(0, LEFTSTICK_RIGHT) || GamePad::IsTrigger(0, BUTTON_RIGHT))
		{
			explain->Up();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_LEFT) || GamePad::IsTrigger(0, BUTTON_LEFT))
		{
			explain->Down();
		}
		else if (GamePad::IsTrigger(0, BUTTON_3))
		{
			explain->Disable();
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

#pragma region PauseCommnad_method
PauseCommand::PauseCommand() { m_Pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE); }
PauseCommand::~PauseCommand(){}
void PauseCommand::Begin() {}
void PauseCommand::Update() { g_IsInputGamePad ? InputGamePad() : InputKeyBoard(); }
void PauseCommand::Event() {}
void PauseCommand::Draw() { }

void PauseCommand::InputKeyBoard()
{
	// NotPause
	if (!m_Pause->NowPausing())
	{
		if (KeyBoard::IsTrigger(DIK_SPACE))
		{
			m_Pause->Enable();
		}
	}
	// ポーズ画面
	else if (m_Pause->NowPausing())
	{
		switch (m_Pause->GetState())
		{
		// ゲームに戻るを選択
		case 0:
			// 下を選択
			if (KeyBoard::IsTrigger(DIK_S))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->SetState(m_Pause->OPERATION);
			}
			// 決定
			else if (KeyBoard::IsTrigger(DIK_SPACE))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->Disable();
			}
			break;
		// 操作方法を選択
		case 1:
			if (!m_Pause->GetOperation())
			{
				// 他のメニューを選択する
				if (KeyBoard::IsTrigger(DIK_W))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SetState(m_Pause->KEEPON);
				}
				else if (KeyBoard::IsTrigger(DIK_S))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SetState(m_Pause->END);
				}
				// 操作方法の表示する
				else if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationEnable();
				}
			}
			// 操作方法を選択中
			else
			{
				// 操作方法の表示を終了
				if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationDisable();
				}
			}
			break;
		// ゲーム終了を選択
		case 2:
			if (!m_Pause->GetEnd())
			{
				// 上を選択
				if (KeyBoard::IsTrigger(DIK_W))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SetState(m_Pause->OPERATION);
				}
				// ポーズ終了
				else if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->EndEnable();
				}
			}
			// ゲーム終了を選択したとき
			else
			{
				// 上下選択
				if (KeyBoard::IsTrigger(DIK_W))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SelectTop();
				}
				else if (KeyBoard::IsTrigger(DIK_S))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SelectBottom();
				}
				// 決定
				else if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					// 上→ゲーム終了、下→キャンセル
					m_Pause->GetToporBottom() ? Engine::Get().application()->SetScene<GameScene::PanzerSelect>() : m_Pause->EndDisable();
				}
			}
			break;
		}
	}
}

void PauseCommand::InputGamePad()
{
	if (!m_Pause->NowPausing())
	{
		if (GamePad::IsTrigger(0, BUTTON_OPTION))
		{
			Engine::Get().resource()->AudioPlay("Select", 1.0f);
			m_Pause->Enable();
		}
	}
	else if (m_Pause->NowPausing())
	{
		switch (m_Pause->GetState())
		{
		//続ける
		case 0:
			if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->SetState(m_Pause->OPERATION);
			}
			// ボーズ終了
			else if (GamePad::IsTrigger(0, BUTTON_2))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->Disable();
			}
			break;
		// 操作方法
		case 1:
			if (!m_Pause->GetOperation())
			{
				// 上下選択
				if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SetState(m_Pause->KEEPON);
				}
				else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SetState(m_Pause->END);
				}
				// 操作方法の表示
				else if (GamePad::IsTrigger(0, BUTTON_2))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationEnable();
				}
			}
			else
			{
				// 表示終了
				if (GamePad::IsTrigger(0, BUTTON_3))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationDisable();
				}
			}
			break;
		// ゲーム終了
		case 2:
			if (!m_Pause->GetEnd())
			{
				if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SetState(m_Pause->OPERATION);
				}
				else if (GamePad::IsTrigger(0, BUTTON_2))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->EndEnable();
				}
			}
			else
			{
				// 上下選択
				if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SelectTop();
				}
				else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SelectBottom();
				}
				// 決定
				else if (GamePad::IsTrigger(0, BUTTON_2))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					// 上→ゲーム終了、下→キャンセル
					m_Pause->GetToporBottom() ? Engine::Get().application()->SetScene<GameScene::PanzerSelect>() : m_Pause->EndDisable();
				}
			}
			break;
		}
	}
}
#pragma endregion PauseCommandメソッド

#pragma region ResultCommand_method
ResultCommand::ResultCommand() {}
ResultCommand::~ResultCommand() {}
void ResultCommand::Begin() {}

void ResultCommand::Update() 
{ 
	// 60フレーム待つまで、入力できないようにする
	m_Frame++; 
	if (m_Frame > 60)
	{
		g_IsInputGamePad ? InputGamePad() : InputKeyBoard();
	}
}

void ResultCommand::Event() {}
void ResultCommand::Draw() {}
void ResultCommand::InputKeyBoard()
{
	auto& state = Engine::Get().application()->GetScene()->GetGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG)->GetState();
	// 次のシーンを選択
	if (KeyBoard::IsTrigger(DIK_W))
	{
		Engine::Get().resource()->AudioPlay("Select", 1.0f);
		state.SelectTop();
		
	}
	else if (KeyBoard::IsTrigger(DIK_S))
	{
		Engine::Get().resource()->AudioPlay("Select", 1.0f);
		state.SelectDown();
	}
	// 決定
	else if (KeyBoard::IsTrigger(DIK_SPACE))
	{
		// 選択したシーンへ遷移
		switch (state.GetSelect())
		{
		case 0:
			Engine::Get().application()->SetScene<GameScene::Game>();
			break;
		case 1:
			Engine::Get().application()->SetScene<GameScene::PanzerSelect>();
			break;
		case 2:
			Engine::Get().application()->SetScene<GameScene::Title>();
			break;
		}
	}
}

void ResultCommand::InputGamePad()
{
	auto state = Engine::Get().application()->GetScene()->GetGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG)->GetState();
	// 次のシーンを選択
	if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
	{
		Engine::Get().resource()->AudioPlay("Select", 1.0f);
		state.SelectTop();

	}
	else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
	{
		Engine::Get().resource()->AudioPlay("Select", 1.0f);
		state.SelectDown();

	}
	// 決定
	else if (GamePad::IsTrigger(0, BUTTON_2))
	{
		// 選択したシーンへ遷移
		switch (state.GetSelect())
		{
		case 0:
			Engine::Get().application()->SetScene<GameScene::Game>();
			break;
		case 1:
			Engine::Get().application()->SetScene<GameScene::PanzerSelect>();
			break;
		case 2:
			Engine::Get().application()->SetScene<GameScene::Title>();
			break;
		}
	}
}
#pragma endregion ResultCommandメソッド