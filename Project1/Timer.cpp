/*--------------------------------------------------------------
	
	[Timer.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Fps.h"
#include "Engine.h"
#include "Application.h"
#include "GameManager.h"
#include "Pause.h"
#include "Command.h"
#include "Timer.h"

namespace
{
	// �`�悷��ʒu�̊
	const D3DXVECTOR2 g_PivotPosition = D3DXVECTOR2(350.0f, 80.0f);
}

#pragma region DrawTimerMinute_method
DrawTimerMinute::DrawTimerMinute() : DrawNumber(64.0f, 1)
{
}

DrawTimerMinute::~DrawTimerMinute()
{
}

void DrawTimerMinute::Draw(int32_t value)
{
	NumberDraw(D3DXVECTOR2(g_PivotPosition.x - 45.0f, g_PivotPosition.y), value);
}
#pragma endregion DrawTimerMinute_���\�b�h

#pragma region DrawTimerSecond_method
DrawTimerSecond::DrawTimerSecond() : DrawNumber(64.0f, 2)
{
}

DrawTimerSecond::~DrawTimerSecond()
{
}

void DrawTimerSecond::Draw(int32_t value) 
{
	for (int32_t i = 0; i < Getdigit(); ++i)
	{
		int num = value % 10;
		value /= 10;
		NumberDraw(D3DXVECTOR2(g_PivotPosition.x + 15.0f + ((GetSize() - 30.0f) * (Getdigit() - (i + 1))), g_PivotPosition.y), num);
	}
}
#pragma endregion DrawTimerSecond_���\�b�h

#pragma region GameBg::Timer_method
							/* 5��*/
GameBg::Timer::Timer() : m_TimeLimitMin(5), m_NowTime(0)
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Timer", g_PivotPosition, D3DXVECTOR2(200.0f, 128.0f));
	m_DrawTimer[0] = std::make_unique<DrawTimerMinute>();
	m_DrawTimer[1] = std::make_unique<DrawTimerSecond>();
}

GameBg::Timer::~Timer()
{
	m_Is1minSetColor = false;
	m_Is10secSetColor = false;
}

void GameBg::Timer::Begin()
{
	m_NowTime = m_TimeLimitMin * 60.0f; // �b�ɕϊ�
}

void GameBg::Timer::Update()
{
	// �{�[�Y���Ȃ�A�^�C�}�[���X�g�b�v
	if(Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
	

	m_NowTime -= Fps::Get().deltaTime;
	// �c��P���ɂȂ����物�F������
	if (!m_Is1minSetColor && m_NowTime < 60.0f)
	{
		for (int32_t i = 0; i < 2; ++i)
		{
			m_DrawTimer[i]->SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		}
		m_Is1minSetColor = true; // �ݒ�ς�
	}
	// �c��10�b�ŐԂ�����
	if (!m_Is10secSetColor && m_NowTime <= 10.0f)
	{
		for (int32_t i = 0; i < 2; ++i)
		{
			m_DrawTimer[i]->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
		m_Is10secSetColor = true; // �ݒ�ς�
	}
	// �I��
	if (m_NowTime < 0.0f)
	{
		// �������ԂɂȂ��Ă���̓Q�[�W���O�ɂȂ��Ă��Ȃ����߁A�s�k
		Engine::Get().application()->GetScene()->GetGameObject<GameManager>(ELayer::LAYER_SYSTEM)->GameSet();
	}

	// ���Ԃ̐ݒ�
	float m = m_NowTime / 60.0f;
	float s = m_NowTime - m_Minute * 60.0f;
	m_Minute = static_cast<int32_t>(m);
	m_Second = static_cast<int32_t>(s);
}

void GameBg::Timer::Event()
{
}

void GameBg::Timer::Draw()
{
	m_Renderer2D->Draw(); // �w�i�g
	m_DrawTimer[0]->Draw(m_Minute);
	m_DrawTimer[1]->Draw(m_Second);
}
#pragma endregion GameBg::Timer_���\�b�h