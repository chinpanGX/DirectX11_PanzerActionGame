/*------------------------------------------------------------

	[Fade.cpp]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#include "Renderer2D.h"
#include "Fade.h"
#include "Engine.h"
#include "Resource.h"
#include "Application.h"
#include "Fps.h"

Scene* Fade::m_Next = nullptr;

Fade::Fade(Application & app, Resource & res, Fps & fps) : m_App(app), m_Resource(res), m_Fps(fps), m_Time(0.5f)
{
	m_Renderer2D = std::make_unique<Renderer2D>(m_Graphics, m_Resource, "Bg", Bg::GetSize() * 0.5f, Bg::GetSize(), Math::Vector2(0.0f, 0.5f), Math::Vector2(0.5f,1.0f));
}

Fade::~Fade()
{
	
}

void Fade::Begin()
{
}

void Fade::Update()
{
	switch (m_State)
	{
	case Fade::E_IN:
		m_Alpha -= m_Fps.deltaTime / m_Time;
		if (m_Alpha < 0.0f)
		{
			m_State = Fade::E_NONE;
			m_Alpha = 0.0f;
		}
		break;
	case Fade::E_OUT:
		m_Alpha += m_Fps.deltaTime / m_Time;
		if (m_Alpha > 1.0f)
		{
			m_App.ChangeScene(m_Next);
			m_State = Fade::E_IN;
			m_Alpha = 1.0f;
		}
		break;
	}
}

void Fade::Event()
{
}

void Fade::Draw()
{
	m_Renderer2D->Draw(m_Alpha);
}

void Fade::SetNextScene(Scene* next)
{
	m_Next = next;
}

Scene * Fade::GetNextScene() const
{
	return m_Next;
}

void Fade::SetState(const EState & state)
{
	m_State = state;
}

Fade::EState Fade::GetState() const
{
	return m_State;
}

bool Fade::ChackState()
{
	if (m_State != E_NONE)
	{
		return true;
	}
	return false;
}
