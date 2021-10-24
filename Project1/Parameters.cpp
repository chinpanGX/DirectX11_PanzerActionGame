/*--------------------------------------------------------------
	
	[Parameter.cpp]
	Author : 出合翔太

----------------------------------------------------------------*/
#include "Renderer2D.h"
#include "Graphics.h"
#include "Resource.h"
#include "Parameters.h"
#include "Engine.h"

#pragma region Parameter_method
Parameters::Parameters()
{
	m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
	m_Bg = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Param", Math::Vector2(1625.0f, 400.0f), Math::Vector2(256.0f, 432.0f));
}

Parameters::~Parameters()
{
}

void Parameters::Draw(float Param, const Math::Vector2 & pos)
{
	Math::Vector4 color = Math::Vector4(0.0f, 0.0f, 1.0f, 0.5);
	m_Bg->Draw();
	m_Render->Draw(300.0f, pos, color);
	m_Render->Draw(Param, pos);
}
#pragma endregion Parametersのメソッド
