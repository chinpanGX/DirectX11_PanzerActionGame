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
	m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
	m_Bg = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Param", D3DXVECTOR2(1625.0f, 400.0f), D3DXVECTOR2(256.0f, 432.0f));
}

Parameters::~Parameters()
{
}

void Parameters::Draw(float Param, const D3DXVECTOR2 & pos)
{
	D3DXVECTOR4 color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.5);
	// 背景
	m_Bg->Draw();
	// MAX状態のバー
	m_Render->Draw(300.0f, pos, color);
	// 実際のバー
	m_Render->Draw(Param, pos);
}
#pragma endregion Parametersのメソッド
