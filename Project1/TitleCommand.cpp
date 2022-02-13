/*-------------------------------------------------------------

	[TitleCommand.cpp]
	Author : �o���đ�

	�^�C�g���V�[���̓��͏����̊Ǘ�

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
	bool g_EndSetting = true; // false; // �ݒ�ς݂��ǂ���
}

TitleCommand::TitleCommand() {}
TitleCommand::~TitleCommand() {}
void TitleCommand::Begin()
{
}

void TitleCommand::Update()
{
	m_TitleSystem = Engine::Get().GetApplication()->GetScene()->GetGameObject<TitleSystem>(ELayer::LAYER_2D_UI);
	uint32_t State = m_TitleSystem->GetState();
	// ���߂̉��
	if (m_TitleSystem->EState::BEGIN == State)
	{
 		BeginInput();
	}
	// 
	else if (m_TitleSystem->EState::SELECT == State)
	{
		InputKeyBoard();
	}
		// �ŏ��̓L�[�{�[�h�}�E�X�A�Q�[���p�b�h�������͂ł���悤�ɂ���
		// �ݒ�ς݂Ŗ�����΁A�������͂ł���
#if 0
		if (g_EndSetting == false)
		{
			InputKeyBoard();
			//InputGamePad();
		}
		else
		{
			
			//g_IsInputGamePad ? InputGamePad() : InputKeyBoard();
		}
	}
	else if (m_TitleSystem->EState::SETTING_SELECT == State || m_TitleSystem->EState::CHECK_INPUT == State)
	{
		// �ŏ��̓L�[�{�[�h�}�E�X�A�Q�[���p�b�h�������͂ł���悤�ɂ���
		InputKeyBoard();
		//InputGamePad();
	}
#endif
}
void TitleCommand::Event() {}
void TitleCommand::Draw() {}

void TitleCommand::BeginInput()
{
	// Any Press�œ��͂ł���悤�ɂ���

	// �L�[�{�[�h
	for (int32_t i = 0; i < 256; ++i)
	{
		if (KeyBoard::IsTrigger(i))
		{
			m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
		}
	}
#if 0 
	// �Q�[���p�b�h
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
#endif
}

// �L�[�{�[�h�̓���
void TitleCommand::InputKeyBoard()
{
	uint32_t State = m_TitleSystem->GetState();
	// �I����ʂ̂Ƃ�
	if (m_TitleSystem->EState::SELECT == State)
	{
// �Q�[���p�b�h�͑I�����ł��Ȃ��悤�ɂ���
#if 0
		// �I��
		if (KeyBoard::IsTrigger(DIK_W))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectTop();
		}
		else if (KeyBoard::IsTrigger(DIK_S))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectButtom();
		}
#endif
		// ����
		if (KeyBoard::IsTrigger(DIK_SPACE) || Mouse::LeftTrigger())
		{
			// �Q�[���X�^�[�g�փV�[���`�F���W
			if (m_TitleSystem->GetSelect())
			{
				//�@�V�[���`�F���W
				Engine::Get().GetApplication()->SetScene<GameScene::PanzerSelect>();
				Engine::Get().GetResource()->AudioPlay("Enter", 1.0f);
			}
#if 0
			// �ݒ��ʂ�
			else if (!m_TitleSystem->GetSelect())
			{
				Engine::Get().GetResource()->AudioPlay("Button", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SETTING_SELECT);
			}
#endif
		}
		// �߂�
		if (KeyBoard::IsTrigger(DIK_Q))
		{
			Engine::Get().GetResource()->AudioPlay("Cancel", 1.0f);
			m_TitleSystem->SetState(m_TitleSystem->EState::BEGIN);
		}

	}

#if 0
	// �ݒ���
	if (m_TitleSystem->EState::SETTING_SELECT == State)
	{
		if (KeyBoard::IsTrigger(DIK_A))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->DisableGamePad();
		}
		else if (KeyBoard::IsTrigger(DIK_D))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableGamePad();
		}
		// ����
		else if (KeyBoard::IsTrigger(DIK_SPACE) || Mouse::LeftTrigger())
		{
			if (m_TitleSystem->GetInputGamePad())
			{
				Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::CHECK_INPUT);
			}
			else
			{
				Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
			}
		}
	}

	// �Q�[���p�b�h�ɕύX���邩�`�F�b�N����
	if (m_TitleSystem->EState::CHECK_INPUT == State)
	{
		if (KeyBoard::IsTrigger(DIK_W))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableCheckInput();
		}
		else if (KeyBoard::IsTrigger(DIK_S))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->DisableCheckInput();
		}
		else if (KeyBoard::IsTrigger(DIK_SPACE))
		{
			Engine::Get().GetResource()->AudioPlay("Button", 1.0f);
			g_IsInputGamePad = m_TitleSystem->GetCheckInput();
			m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
			g_EndSetting = true;
		}
	}
#endif 	
}

// �Q�[���p�b�h�̓���
#if 0
void TitleCommand::InputGamePad()
{
	uint32_t State = m_TitleSystem->GetState();
	// �I����ʂ̂Ƃ�
	if (m_TitleSystem->EState::SELECT == State)
	{
		// �I��
		if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectTop();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->SelectButtom();
		}
		// ����
		if (GamePad::IsTrigger(0, BUTTON_2))
		{
			if (m_TitleSystem->GetSelect())
			{
				Engine::Get().GetResource()->AudioPlay("Enter", 1.0f);
				//�@�V�[���`�F���W
				Engine::Get().GetApplication()->SetScene<GameScene::PanzerSelect>();
			}
			// �ݒ��ʂ�
			else if (!m_TitleSystem->GetSelect())
			{
				Engine::Get().GetResource()->AudioPlay("Cancel", 1.0f);
				m_TitleSystem->SetState(m_TitleSystem->EState::SETTING_SELECT);
			}
		}
		// �߂�
		if (GamePad::IsTrigger(0, BUTTON_3))
		{
			Engine::Get().GetResource()->AudioPlay("Cancel", 1.0f);
			m_TitleSystem->SetState(m_TitleSystem->EState::BEGIN);
		}

	}
	// �ݒ���
	if (m_TitleSystem->EState::SETTING_SELECT == State)
	{
		if (GamePad::IsTrigger(0, LEFTSTICK_LEFT) || GamePad::IsTrigger(0, BUTTON_LEFT))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->DisableGamePad();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_RIGHT) || GamePad::IsTrigger(0, BUTTON_LEFT))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableGamePad();
		}
		// ����
		// �L�[�{�[�h����Q�[���p�b�h�ɕύX���悤�Ƃ��Ă���Ƃ�
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
					Engine::Get().GetResource()->AudioPlay("Cancel", 1.0f);
					m_TitleSystem->SetState(m_TitleSystem->EState::SELECT);
				}
			}
		}
	}

	if (m_TitleSystem->EState::CHECK_INPUT == State)
	{
		if (GamePad::IsTrigger(0, LEFTSTICK_UP) || GamePad::IsTrigger(0, BUTTON_UP))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
			m_TitleSystem->EnableCheckInput();
		}
		else if (GamePad::IsTrigger(0, LEFTSTICK_DOWN) || GamePad::IsTrigger(0, BUTTON_DOWN))
		{
			Engine::Get().GetResource()->AudioPlay("Select", 1.0f);
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
#endif
#pragma endregion TitleCommand�̃��\�b�h
