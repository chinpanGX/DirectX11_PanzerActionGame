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
	m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
	m_Bg = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Param", D3DXVECTOR2(1625.0f, 435.0f), D3DXVECTOR2(256.0f, 514.0f));
}

Parameters::~Parameters()
{
}

void Parameters::Draw(float Param, const D3DXVECTOR2 & Position)
{
	D3DXVECTOR4 color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.5);
	// �w�i
	m_Bg->Draw();
	// MAX��Ԃ̃o�[
	m_Render->Draw(300.0f, Position, color);
	// ���ۂ̃o�[
	m_Render->Draw(Param, Position);
}
#pragma endregion Parameters�̃��\�b�h
