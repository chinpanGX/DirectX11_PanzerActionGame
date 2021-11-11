/*--------------------------------------------------------------
	
	[Parameter.cpp]
	Author : �o���đ�

----------------------------------------------------------------*/
#include "Renderer2D.h"
#include "Graphics.h"
#include "Resource.h"
#include "Parameters.h"
#include "Engine.h"

#pragma region Parameter_method
Parameters::Parameters()
{
	m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
	m_Bg = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Param", Math::Vector2(1625.0f, 400.0f), Math::Vector2(256.0f, 432.0f));
}

Parameters::~Parameters()
{
}

void Parameters::Draw(float Param, const Math::Vector2 & pos)
{
	Math::Vector4 color = Math::Vector4(0.0f, 0.0f, 1.0f, 0.5);
	// �w�i
	m_Bg->Draw();
	// MAX��Ԃ̃o�[
	m_Render->Draw(300.0f, pos, color);
	// ���ۂ̃o�[
	m_Render->Draw(Param, pos);
}
#pragma endregion Parameters�̃��\�b�h
