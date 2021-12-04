/*-----------------------------------------------------------

	[Command.cpp]
	Author : 出合翔太

	ゲームシーンで使う入力処理の管理

-------------------------------------------------------------*/
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
#include "Controller.h"
#include "Pause.h"
#include "Command.h"

#pragma region TitleCommand_method
#pragma region GameCommand
GameCommand::GameCommand()
{
}
GameCommand::~GameCommand() {}
void GameCommand::Begin() 
{

	// カメラの操作
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	// プレイヤーの操作
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	// 戦車の操縦
	auto& Pivot = m_Player->pivot();
	m_Controller = std::make_unique<Controller>(m_Player, camera, &Pivot);

	m_Pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
	// 
	m_NowInput.resize(11);
}

void GameCommand::Update()
{
	float deltaTime = Fps::Get().deltaTime;

	if (!g_IsInputGamePad)
	{
		if (!m_Pause->NowPausing())
		{
			InputKeyboardAndMouse(deltaTime);
		}
	}
	else if (g_IsInputGamePad)
	{
		if (!m_Pause->NowPausing())
		{
			InputGamePad(deltaTime);
		}
	}
}

void GameCommand::Event() {}
void GameCommand::Draw() {}
bool GameCommand::GetNowInput(int32_t i) const { return m_NowInput[i]; }

// キーボード入力
void GameCommand::InputKeyboardAndMouse(float deltaTime)
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

	// 補給
	if (KeyBoard::IsTrigger(DIK_R))
	{
		m_Controller->ReplenishBullet();
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

	// ほきゅう　
	if (GamePad::IsTrigger(0, BUTTON_4))
	{
		m_Controller->ReplenishBullet();
	}
}
#pragma endregion GameCommandメソッド


#pragma region PauseCommnad_method
PauseCommand::PauseCommand() {}
PauseCommand::~PauseCommand(){}
void PauseCommand::Begin() 
{
	m_Pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
}

void PauseCommand::Update() 
{ 
	g_IsInputGamePad ? InputGamePad() : InputKeyBoardAndMouse(); 

}
void PauseCommand::Event() {}
void PauseCommand::Draw() { }

void PauseCommand::InputKeyBoardAndMouse()
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
