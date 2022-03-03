/*-------------------------------------------------
	
	[ResultBg.cpp]
	Author : �o���đ�

---------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "Application.h"
#include "Renderer2D.h"
#include "ResultState.h"
#include "ResultBg.h"

#pragma region ResultBg_method
GameBg::ResultBg::ResultBg() : m_Count(0), m_Alpha(0.0f)
{
	m_Fade = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Bg");
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "ResultBg");
	m_State = std::make_unique<ResultState>();
}

GameBg::ResultBg::~ResultBg()
{
}

void GameBg::ResultBg::Begin()
{
}

void GameBg::ResultBg::Update()
{
	m_State->Update();
}

void GameBg::ResultBg::Event()
{
}

void GameBg::ResultBg::Draw()
{
	if (m_PlayerWin)
	{
		// WIN��\��
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	}
	else
	{
		// LOSE��\��
		m_Renderer2D->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}
	m_Fade->Draw(Bg::GetSize() * 0.5f, Bg::GetSize(), D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.5f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_State->GetAlpha()));
}

// �ŏ��ɌĂяo��
void GameBg::ResultBg::Begin(bool PlayerWin)
{
	m_PlayerWin = PlayerWin;
}

ResultState & GameBg::ResultBg::GetState() const
{
	return *m_State;
}
#pragma endregion Result���\�b�h

GameBg::ResultUi::ResultUi()
{
	// ���̃V�[���̑I����
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui02", Bg::GetSize() * 0.5f, D3DXVECTOR2(512.0f, 384.0f));
	// �ǂ��I��ł��邩�̃}�[�J�[
	m_Marker = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Ui");
}

GameBg::ResultUi::~ResultUi()
{
}

void GameBg::ResultUi::Begin()
{
	// �w�i
	m_Bg = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameBg::ResultBg>(ELayer::LAYER_2D_BG);
}

void GameBg::ResultUi::Update()
{
	auto& State = m_Bg->GetState();
	// �A���t�@�l���擾����
	m_Alpha = State.GetAlpha();

	//	�}�[�J�[�I�����Ă���ʒu�Ɉړ�������
	switch (State.GetSelect())
	{
	case 0:
		m_Draw_y = 410.0f;
		break;
	case 1:
		m_Draw_y = 550.0f;
		break;
	case 2:
		m_Draw_y = 680.0f;
		break;
	}
}

void GameBg::ResultUi::Event()
{
}

void GameBg::ResultUi::Draw()
{	
	// �ϐ�
	float x = 1920.0f * 0.5f;
	D3DXVECTOR2 size = D3DXVECTOR2(512.0f, 128.0f);
	D3DXVECTOR2 texMin = D3DXVECTOR2(0.0f, 0.375f);
	D3DXVECTOR2 texMax = D3DXVECTOR2(0.25f, 0.5f);
	D3DXVECTOR4 color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_Alpha);


	m_Marker->Draw(D3DXVECTOR2(x, m_Draw_y), size, texMin, texMax, color);

	// �w�i���Â��Ȃ�����A�I������\������
	if (m_Alpha >= 0.7f)
	{
		m_Renderer2D->Draw();
	}
}