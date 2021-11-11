/*--------------------------------------------------------------

	[Pause.h]
	Author : 出合翔太

	ポーズ画面

---------------------------------------------------------------*/
#include "Pause.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Command.h"

Pause::Pause()
{
	m_RenderBg = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Bg");
}

Pause::~Pause()
{
}

void Pause::Begin()
{
	Math::Vector2 size = Math::Vector2(1920.0f, 1080.0f);
	m_RenderBg->SetVertex(size * 0.5f, size, Math::Vector2(0.5f, 0.0f), Math::Vector2(1.0f, 0.5f));
}

void Pause::Update()
{
	// ポーズが有効になったとき
	if (m_Enable)
	{
		// 色の変更
		m_Alpha += m_Changecolor;
		if (m_Alpha < 0.5f)
		{
			m_Alpha = 0.5f;
			m_Changecolor *= -1;
		}
		else if (m_Alpha > 1.0f)
		{
			m_Alpha = 1.0f;
			m_Changecolor *= -1;
		}

		// ステートチェンジ
		switch (m_State)
		{
		case Pause::KEEPON:
			ChangeState(std::make_unique<Keepon>());
			break;
		case Pause::OPERATION:
			ChangeState(std::make_unique<Operation>());
			break;
		case Pause::END:
			ChangeState(std::make_unique<GameEnd>());
			break;
		}
	}
}

void Pause::Event()
{
}

void Pause::Draw()
{
	if (m_Enable)
	{
		m_RenderBg->Draw();
		m_PauseState->Draw(this);
	}
}

void Pause::Enable()
{
	m_Enable = true;
}

void Pause::Disable()
{
	m_Enable = false;
}

bool Pause::GetEnable() const
{
	return m_Enable;
}

void Pause::SetState(EState State)
{
	m_State = State;
}

float Pause::GetAlpha() const
{
	return m_Alpha;
}

void Pause::KeeponEnable()
{
	m_Keepon = true;
}

void Pause::KeeponDisable()
{
	m_Keepon = false;
}

void Pause::OperationEnable()
{
	m_Operation = true;
}

void Pause::OperationDisable()
{
	m_Operation = false;
}

bool Pause::GetOperation() const
{
	return m_Operation;
}

void Pause::EndEnable()
{
	m_End = true;
}

void Pause::EndDisable()
{
	m_End = false;
}

bool Pause::GetEnd() const
{
	return m_End;
}

void Pause::SelectTop()
{
	m_TopToBottom = true;
}

void Pause::SelectBottom()
{
	m_TopToBottom = false;
}

bool Pause::GetToorBottom()
{
	return m_TopToBottom;
}

void Pause::ChangeState(std::unique_ptr<PauseState> State)
{
	m_PauseState = std::move(State);
}

PauseState::PauseState() : m_Renderer(std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Ui"))
{
}

class Renderer2D& PauseState::GetRenderer() const
{
	return *m_Renderer;
}

#pragma region Keepon
Keepon::Keepon() : PauseState()
{
	
}

void Keepon::Draw(Pause * Pause)
{
	Math::Vector2 size = Math::Vector2(512.0f, 128.0f);
	Math::Vector4 color = Math::Vector4(1.0f, 1.0f, 1.0f, Pause->GetAlpha());
	GetRenderer().Draw(Math::Vector2(960.0f, 400.0f), size, Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f), color);
	GetRenderer().Draw(Math::Vector2(960.0f, 400.0f), size, Math::Vector2(0.0f, 0.5f), Math::Vector2(0.25f, 0.625f));
	GetRenderer().Draw(Math::Vector2(960.0f, 600.0f), size, Math::Vector2(0.0f, 0.625f), Math::Vector2(0.25f, 0.75f));
	GetRenderer().Draw(Math::Vector2(960.0f, 800.0f), size, Math::Vector2(0.25f, 0.375f), Math::Vector2(0.5f, 0.5f));
}
#pragma endregion 続ける

#pragma region Operation 
Operation::Operation() : PauseState()
{

}

void Operation::Draw(Pause * Pause)
{
	if (!Pause->GetOperation())
	{
		Math::Vector2 size = Math::Vector2(512.0f, 128.0f);
		Math::Vector4 color = Math::Vector4(1.0f, 1.0f, 1.0f, Pause->GetAlpha());
		GetRenderer().Draw(Math::Vector2(960.0f, 600.0f), size, Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f), color);
		GetRenderer().Draw(Math::Vector2(960.0f, 400.0f), size, Math::Vector2(0.0f, 0.5f), Math::Vector2(0.25f, 0.625f));
		GetRenderer().Draw(Math::Vector2(960.0f, 600.0f), size, Math::Vector2(0.0f, 0.625f), Math::Vector2(0.25f, 0.75f));
		GetRenderer().Draw(Math::Vector2(960.0f, 800.0f), size, Math::Vector2(0.25f, 0.375f), Math::Vector2(0.5f, 0.5f));
	}
	else
	{
		Math::Vector2 pos = Math::Vector2(960.0f, 540.0f);
		Math::Vector2 size = Math::Vector2(1024.0f, 512.f);
		// キーボードマウスの設定
		if (g_IsInputGamePad == false)
		{
			GetRenderer().Draw(pos, size, Math::Vector2(0.5f, 0.0f), Math::Vector2(1.0f, 0.5f));
		}
		else if (g_IsInputGamePad == true)
		{
			GetRenderer().Draw(pos, size, Math::Vector2(0.5f, 0.5f), Math::Vector2(1.0f, 1.0f));
		}
	}
}
#pragma endregion 操作方法の確認

#pragma region GameEnd
GameEnd::GameEnd() : PauseState()
{

}

void GameEnd::Draw(Pause * Pause)
{
	if (!Pause->GetEnd())
	{
		Math::Vector2 size = Math::Vector2(512.0f, 128.0f);
		Math::Vector4 color = Math::Vector4(1.0f, 1.0f, 1.0f, Pause->GetAlpha());
		GetRenderer().Draw(Math::Vector2(960.0f, 800.0f), size, Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f), color);
		GetRenderer().Draw(Math::Vector2(960.0f, 400.0f), size, Math::Vector2(0.0f, 0.5f), Math::Vector2(0.25f, 0.625f));
		GetRenderer().Draw(Math::Vector2(960.0f, 800.0f), size, Math::Vector2(0.25f, 0.375f), Math::Vector2(0.5f, 0.5f));
		GetRenderer().Draw(Math::Vector2(960.0f, 600.0f), size, Math::Vector2(0.0f, 0.625f), Math::Vector2(0.25f, 0.75f));
	}
	else
	{
		// 上を選んだとき、はい
		if (Pause->GetToorBottom() == true)
		{
			GetRenderer().Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f),Math::Vector4(1.0f, 1.0f, 1.0f, Pause->GetAlpha()));
			GetRenderer().Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.5f), Math::Vector2(0.5f, 0.625f));
			GetRenderer().Draw(Math::Vector2(960.0f, 800.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.625f), Math::Vector2(0.5f, 0.75f));
			GetRenderer().Draw(Math::Vector2(960.0f, 400.0f), Math::Vector2(1024.0f, 128.0f), Math::Vector2(0.0f, 0.875f), Math::Vector2(0.5f, 1.0f));
		}
		// 下を選んだ時、いいえ
		else if (Pause->GetToorBottom() == false)
		{
			GetRenderer().Draw(Math::Vector2(960.0f, 800.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.0f, 0.375f), Math::Vector2(0.25f, 0.5f), Math::Vector4(1.0f,1.0f,1.0f, Pause->GetAlpha()));
			GetRenderer().Draw(Math::Vector2(960.0f, 600.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.5f), Math::Vector2(0.5f, 0.625f));
			GetRenderer().Draw(Math::Vector2(960.0f, 800.0f), Math::Vector2(512.0f, 128.0f), Math::Vector2(0.25f, 0.625f), Math::Vector2(0.5f, 0.75f));
			GetRenderer().Draw(Math::Vector2(960.0f, 400.0f), Math::Vector2(1024.0f, 128.0f), Math::Vector2(0.0f, 0.875f), Math::Vector2(0.5f, 1.0f));
		}
	}
}
#pragma endregion ゲーム終了
