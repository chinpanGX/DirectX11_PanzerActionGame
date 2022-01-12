/*-------------------------------------------------------------

	[ResultCommand.cpp]
	Author : �o���đ�

	���U���g�V�[���̓��͏����̊Ǘ�

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
	m_Bg = Engine::Get().application()->GetScene()->GetGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG);
}

void ResultCommand::Update()
{
	// 60�t���[���҂܂ŁA���͂ł��Ȃ��悤�ɂ���
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
	auto& state = m_Bg->GetState();
	// ���̃V�[����I��
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
	// ����
	else if (KeyBoard::IsTrigger(DIK_SPACE))
	{
		// �I�������V�[���֑J��
		switch (state.select())
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

// �Q�[���p�b�h�̓���
#if 0
void ResultCommand::InputGamePad()
{
	auto& state = m_Bg->GetState();
	// ���̃V�[����I��
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
	// ����
	else if (GamePad::IsTrigger(0, BUTTON_2))
	{
		// �I�������V�[���֑J��
		switch (state.select())
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
#endif
#pragma endregion ResultCommand���\�b�h