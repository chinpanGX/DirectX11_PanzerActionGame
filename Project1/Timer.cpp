/*--------------------------------------------------------------
	
	[Timer.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Fps.h"
#include "Engine.h"
#include "Application.h"
#include "GameManager.h"
#include "Pause.h"
#include "Command.h"
#include "Timer.h"

#pragma region DrawTimerMinute_method
DrawTimerMinute::DrawTimerMinute() : IDrawNumber(64.0f, 1)
{
}

DrawTimerMinute::~DrawTimerMinute()
{
}

void DrawTimerMinute::Draw(int32_t n)
{
	NumberDraw(D3DXVECTOR2(305.0f, 80.0f), n);
}
#pragma endregion DrawTimerMinute_メソッド

#pragma region DrawTimerSecond_method
DrawTimerSecond::DrawTimerSecond() : IDrawNumber(64.0f, 2)
{
}

DrawTimerSecond::~DrawTimerSecond()
{
}

void DrawTimerSecond::Draw(int32_t n) 
{
	for (int32_t i = 0; i < Getdigit(); ++i)
	{
		int num = n % 10;
		n /= 10;
		NumberDraw(D3DXVECTOR2(365.0f + ((GetSize() - 30.0f) * (Getdigit() - (i + 1))), 80.0f), num);
	}
}
#pragma endregion DrawTimerSecond_メソッド

#pragma region GameBg::Timer_method
							/* 5分*/
GameBg::Timer::Timer() : m_TimeLimit_min(5), m_NowTime(0)
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Timer", D3DXVECTOR2(350.0f, 80.0f), D3DXVECTOR2(200.0f, 128.0f));
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
	m_NowTime = m_TimeLimit_min * 60.0f; // 秒に変換
}

void GameBg::Timer::Update()
{
	// ボーズ中なら、タイマーをストップ
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }

	m_NowTime -= Fps::Get().deltaTime;
	// 残り１分になったら黄色くする
	if (!m_Is1minSetColor && m_NowTime < 60.0f)
	{
		for (int32_t i = 0; i < 2; ++i)
		{
			m_DrawTimer[i]->SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		}
		m_Is1minSetColor = true; // 設定済み
	}
	// 残り10秒で赤くする
	if (!m_Is10secSetColor && m_NowTime <= 10.0f)
	{
		for (int32_t i = 0; i < 2; ++i)
		{
			m_DrawTimer[i]->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
		m_Is10secSetColor = true; // 設定済み
	}
	// 終了
	if (m_NowTime < 0.0f)
	{
		// 制限時間になっても戦力ゲージが０になっていないため、敗北
		Engine::Get().application()->GetScene()->GetGameObject<GameManager>(ELayer::LAYER_SYSTEM)->GameSet();
	}
	// 時間の設定
	m_Minute = (int32_t)m_NowTime / 60;
	m_Second = m_NowTime - m_Minute * 60;
}

void GameBg::Timer::Event()
{
}

void GameBg::Timer::Draw()
{
	m_Renderer2D->Draw(); // 背景枠
	m_DrawTimer[0]->Draw(m_Minute);
	m_DrawTimer[1]->Draw((int32_t)m_Second);
}
#pragma endregion GameBg::Timer_メソッド