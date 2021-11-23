/*------------------------------------------------------------

	[GameBg.cpp]
	Author : �o���đ�

	�Q�[����2D�w�i

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
}

void GameBg::Scope::Update()
{
}

void GameBg::Scope::Event()
{
}

void GameBg::Scope::Draw()
{
	// �J������FPS���[�h�̂Ƃ��ɃX�R�[�v��`�悷��
	if(Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA)->FpsModeNow() == true)
	{
		m_Renderer2D->Draw();
	}
}
#pragma endregion Scope�N���X�̃��\�b�h

#pragma region PanzerSelectUi_method
GameBg::PanzerSelectUi::PanzerSelectUi()
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "SelectUi");
	m_Operation = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui03");
	m_List = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "SelectList");
	
	// ��Ԗ���Texture���W
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
}

void GameBg::PanzerSelectUi::Update()
{
	auto container = Engine::Get().application()->GetScene()->GetGameObject<PanzerContainer>(LAYER_3D_ACTOR);
	// ��
	if (container->GetButton() == 1)
	{
		std::rotate(m_TexCoord.rbegin(), m_TexCoord.rbegin() + 1, m_TexCoord.rend());
	}
	// ��
	else if (container->GetButton() == 2)
	{
		// �z������V�t�g
		std::rotate(m_TexCoord.begin(), m_TexCoord.begin() + 1, m_TexCoord.end());
	}
	// �I�������Z�b�g
	container->Reset();
}

void GameBg::PanzerSelectUi::Event()
{
}

void GameBg::PanzerSelectUi::Draw()
{
	D3DXVECTOR2 pos = Bg::GetSize() * 0.5f;
	D3DXVECTOR2 size = Bg::GetSize();

	// �w�i
	m_Renderer2D->Draw(pos, size, D3DXVECTOR2(0.5f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));

	auto op_pos = D3DXVECTOR2(960.0f, 960.0f);
	auto op_size = D3DXVECTOR2(500.0f, 70.0f);
	
	// ������@�̐���
	if (g_IsInputGamePad == false)
	{
		m_Operation->Draw(op_pos, op_size, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	}
	else
	{
		m_Operation->Draw(op_pos, op_size, D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}
	
	// ��Ԃ̖��O
	DrawPanzerName();

	// �Q�[������
	DrawGameRule(pos, size);
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
	if (m_Page > 2)
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
		m_Page = 0; // �ŏ��̃y�[�W�ɖ߂�
	}
}

const bool GameBg::PanzerSelectUi::GetDrawFlag() const
{
	return m_DrawFlag;
}

void GameBg::PanzerSelectUi::DrawPanzerName()
{
	// �`�悷��4��
	std::array<float, 4> position = { 1.0f, 1.25f, 1.5f, 0.75f };
	// �`��ʒu�̕␳
	float x = Bg::GetWidth() * 0.1f + 30.0f;
	float y = Bg::GetHeight() * 0.5f + 30.0f;

	// ��Ԃ̃��X�g
	// �z��̐擪����3��
	auto offset = D3DXVECTOR2(0.25f, 0.25f);
	for (int32_t i = 0; i < 3; ++i)
	{
		m_List->Draw(D3DXVECTOR2(x, y * position[i]), D3DXVECTOR2(432.0f, 128.0f), m_TexCoord[i], m_TexCoord[i] + offset);
	}

	// �z��̈�ԍŌ�	
	D3DXVECTOR2 end = m_TexCoord.back();
	m_List->Draw(D3DXVECTOR2(x, y * position[3]), D3DXVECTOR2(432.0f, 128.0f), end, end + offset);

	// �g�̕`��
	m_List->Draw(D3DXVECTOR2(x, y), D3DXVECTOR2(432.0f, 128.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 0.25f));
}

void GameBg::PanzerSelectUi::DrawGameRule(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	// �Q�[���̐���
	if (m_DrawFlag)
	{
		switch (m_Page)
		{
		case 0:
			m_Renderer2D->Draw(pos, size, D3DXVECTOR2(0.0f, 0.02f), D3DXVECTOR2(0.5f, 0.52f));
			break;
		case 1:
			m_Renderer2D->Draw(pos, size, D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
			break;
		case 2:
			m_Renderer2D->Draw(pos, size, D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.5f, 1.0f));
			break;
		}
	}
}
#pragma endregion PranzerSelectUi_method

#pragma region Mode_method
GameBg::Mode::Mode()
{
	m_Renderer2D = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "SelectList");
	m_Renderer = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Ui");
}

GameBg::Mode::~Mode()
{
}

void GameBg::Mode::Begin()
{
}

void GameBg::Mode::Update()
{
	m_Alpha += m_Color;
	if (m_Alpha < 0.5f)
	{
		m_Alpha = 0.5f;
		m_Color *= -1;
	}
	else if (m_Alpha > 1.0f)
	{
		m_Alpha = 1.0f;
		m_Color *= -1;
	}
}

void GameBg::Mode::Event()
{
}

void GameBg::Mode::Draw()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(1600.0f, 900.0f);
	float size_y = 128.0f;
	// �w�i�g
	DrawFrame(pos, size_y);
	// �Q�[�����[�h
	DrawModeName(pos, size_y);
}

bool GameBg::Mode::SetMode(bool f)
{
	m_Mode = f;
	return m_Mode;
}

void GameBg::Mode::DrawFrame(D3DXVECTOR2 pos, float size_y)
{
	if (Engine::Get().application()->GetScene()->GetGameObject<SelectCommand>(ELayer::LAYER_SYSTEM)->GetSelect() == false)
	{
		m_Renderer->Draw(pos, D3DXVECTOR2(512.0f, size_y), D3DXVECTOR2(0.0f, 0.375f), D3DXVECTOR2(0.25f, 0.5f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_Alpha));
	}
	else
	{
		m_Renderer->Draw(pos, D3DXVECTOR2(512.0f, size_y), D3DXVECTOR2(0.0f, 0.375f), D3DXVECTOR2(0.25f, 0.5f));
	}
}

void GameBg::Mode::DrawModeName(D3DXVECTOR2 pos, float size_y)
{
	if (m_Mode)
	{
		m_Renderer2D->Draw(pos, D3DXVECTOR2(432.0f, size_y), D3DXVECTOR2(0.25f, 0.25f), D3DXVECTOR2(0.5f, 0.5f));
	}
	else
	{
		m_Renderer2D->Draw(pos, D3DXVECTOR2(432.0f, size_y), D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 0.25f));
	}
}
#pragma endregion Mode_method

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
	D3DXVECTOR2 size = D3DXVECTOR2(256.0f, 256.0f);
	if (g_IsInputGamePad == false)
	{
		m_Renderer2D->Draw(pos, size, D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
	}
	else 
	{
		m_Renderer2D->Draw(pos, size, D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
	}
}
