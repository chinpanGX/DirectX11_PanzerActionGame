/*-------------------------------------------------------------

	[ResultCommand.cpp]
	Author : 出合翔太

	リザルトシーンの入力処理の管理

--------------------------------------------------------------*/
#include "Command.h"
#include "ResultState.h"
#include "ResultBg.h"
#include "ResultCommand.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Input.h"
#include "GameScene.h"
#include "TitleScene.h"

#pragma region ResultCommand_method
ResultCommand::ResultCommand() {}
ResultCommand::~ResultCommand() {}
void ResultCommand::Begin()
{
	m_Bg = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG);
}

void ResultCommand::Update()
{
	// 60フレーム待つまで、入力できないようにする
	m_Frame++;
	if (m_Frame > 60)
	{
		InputKeyBoard();
		//g_IsInputGamePad ? InputGamePad() : InputKeyBoard();
	}
}

void ResultCommand::Event() {}
void ResultCommand::Draw() {}
void ResultCommand::InputKeyBoard()
{
	auto& State = m_Bg->GetState();
	// 次のシーンを選択
	if (KeyBoard::IsTrigger(DIK_W))
	{
		Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
		State.SelectTop();

	}
	else if (KeyBoard::IsTrigger(DIK_S))
	{
		Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
		State.SelectDown();
	}
	// 決定
	else if (KeyBoard::IsTrigger(DIK_SPACE))
	{
		// 選択したシーンへ遷移
		switch (State.GetSelect())
		{
		case 0:
			Engine::Get().GetApplication()->SetScene<GameScene::Game>();
			break;
		case 1:
			Engine::Get().GetApplication()->SetScene<GameScene::PanzerSelect>();
			break;
		case 2:
			Engine::Get().GetApplication()->SetScene<GameScene::Title>();
			break;
		}
	}
}

// ゲームパッドの入力
#if 0
void ResultCommand::InputGamePad()
{
	auto& State = m_Bg->GetState();
	// 次のシーンを選択
	if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
	{
		Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
		State.SelectTop();

	}
	else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
	{
		Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
		State.SelectDown();

	}
	// 決定
	else if (GamePad::IsTrigger(0, BUTTON_2))
	{
		// 選択したシーンへ遷移
		switch (State.GetSelect())
		{
		case 0:
			Engine::Get().GetApplication()->SetScene<GameScene::Game>();
			break;
		case 1:
			Engine::Get().GetApplication()->SetScene<GameScene::PanzerSelect>();
			break;
		case 2:
			Engine::Get().GetApplication()->SetScene<GameScene::Title>();
			break;
		}
	}
}
#endif
#pragma endregion ResultCommandメソッド