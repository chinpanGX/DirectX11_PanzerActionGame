/*-----------------------------------------------------------

	[Command.cpp]
	Author : �o���đ�

	�Q�[���V�[���Ŏg�����͏����̊Ǘ�

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

	// �J�����̑���
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	// �v���C���[�̑���
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	// ��Ԃ̑��c
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

// �L�[�{�[�h����
void GameCommand::InputKeyboardAndMouse(float deltaTime)
{
	// ���͏�Ԃ����Z�b�g
	for (auto i : m_NowInput)
	{
		i = false;
	}
	m_Controller->FpsCameraMode(false);

	// ���݂̃}�E�X�|�C���^
	m_Mouse.y = (Mouse::GetMouseY() - m_OldMouse.y) * 0.08f;
	m_Mouse.x = (Mouse::GetMouseX() - m_OldMouse.x) * 0.02f;
	
	// �J�������[�h��FPS�ɂ���
	if (Mouse::RightPress())
	{
		m_NowInput[9] = true;
		m_Controller->FpsCameraMode(true);
	}

	// ��ԁi�{�f�B�j�̈ړ�
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
	// ��ԁi�^���b�g�j�̉�]
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

	// �C��̏㉺
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

	// �C�e������
	if (Mouse::LeftTrigger())
	{
		m_NowInput[8] = true;
		m_Controller->Shot();
	}

	// �X�L�����g��
	if (KeyBoard::IsTrigger(DIK_E))
	{
		m_NowInput[10] = true;
		m_Controller->UseSkill();
	}

	// �⋋
	if (KeyBoard::IsTrigger(DIK_R))
	{
		m_Controller->ReplenishBullet();
	}

	// 1f�O�̃}�E�X�|�C���^
	m_OldMouse.x = (float)Mouse::GetMouseX();
	m_OldMouse.y = (float)Mouse::GetMouseY();
}

// �Q�[���p�b�h�̓���
void GameCommand::InputGamePad(float deltaTime)
{
	// ���͏�Ԃ����Z�b�g
// ���͏�Ԃ����Z�b�g
	for (auto i : m_NowInput)
	{
		i = false;
	}
	m_Controller->FpsCameraMode(false);

	// �J�������[�h��FPS�ɂ���
	if (GamePad::IsPress(0, TRIGGER_L2))
	{
		m_NowInput[9] = true;
		m_Controller->FpsCameraMode(true);
	}

	// ��ԁi�{�f�B�j�̈ړ�
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
	// ��ԁi�^���b�g�j�̉�]
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

	// �C��̏㉺
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

	// �C�e������
	if (GamePad::IsTrigger(0, TRIGGER_R2))
	{
		m_NowInput[8] = true;
		m_Controller->Shot();
	}

	// �X�L�����g��
	if (GamePad::IsTrigger(0, BUTTON_1))
	{
		m_NowInput[10] = true;
		m_Controller->UseSkill();
	}

	// �ق��イ�@
	if (GamePad::IsTrigger(0, BUTTON_4))
	{
		m_Controller->ReplenishBullet();
	}
}
#pragma endregion GameCommand���\�b�h


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
	// �|�[�Y���
	else if (m_Pause->NowPausing())
	{
		switch (m_Pause->GetState())
		{
		// �Q�[���ɖ߂��I��
		case 0:
			// ����I��
			if (KeyBoard::IsTrigger(DIK_S))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->SetState(m_Pause->OPERATION);
			}
			// ����
			else if (KeyBoard::IsTrigger(DIK_SPACE))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->Disable();
			}
			break;
		// ������@��I��
		case 1:
			if (!m_Pause->GetOperation())
			{
				// ���̃��j���[��I������
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
				// ������@�̕\������
				else if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationEnable();
				}
			}
			// ������@��I��
			else
			{
				// ������@�̕\�����I��
				if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationDisable();
				}
			}
			break;
		// �Q�[���I����I��
		case 2:
			if (!m_Pause->GetEnd())
			{
				// ���I��
				if (KeyBoard::IsTrigger(DIK_W))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->SetState(m_Pause->OPERATION);
				}
				// �|�[�Y�I��
				else if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->EndEnable();
				}
			}
			// �Q�[���I����I�������Ƃ�
			else
			{
				// �㉺�I��
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
				// ����
				else if (KeyBoard::IsTrigger(DIK_SPACE))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					// �と�Q�[���I���A�����L�����Z��
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
		//������
		case 0:
			if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->SetState(m_Pause->OPERATION);
			}
			// �{�[�Y�I��
			else if (GamePad::IsTrigger(0, BUTTON_2))
			{
				Engine::Get().resource()->AudioPlay("Select", 1.0f);
				m_Pause->Disable();
			}
			break;
		// ������@
		case 1:
			if (!m_Pause->GetOperation())
			{
				// �㉺�I��
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
				// ������@�̕\��
				else if (GamePad::IsTrigger(0, BUTTON_2))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationEnable();
				}
			}
			else
			{
				// �\���I��
				if (GamePad::IsTrigger(0, BUTTON_3))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					m_Pause->OperationDisable();
				}
			}
			break;
		// �Q�[���I��
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
				// �㉺�I��
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
				// ����
				else if (GamePad::IsTrigger(0, BUTTON_2))
				{
					Engine::Get().resource()->AudioPlay("Select", 1.0f);
					// �と�Q�[���I���A�����L�����Z��
					m_Pause->GetToporBottom() ? Engine::Get().application()->SetScene<GameScene::PanzerSelect>() : m_Pause->EndDisable();
				}
			}
			break;
		}
	}
}
#pragma endregion PauseCommand���\�b�h
