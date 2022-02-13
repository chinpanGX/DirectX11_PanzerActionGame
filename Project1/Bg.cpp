/*-----------------------------------------------------------

	[Bg.cpp]
	Author : èoçá„ƒëæ

------------------------------------------------------------*/
#include "Renderer2D.h"
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Bg.h"

Bg::Bg() : m_Resource(*Engine::Get().GetResource()), m_Graphics(*Engine::Get().GetGraphics())
{
	m_Size = D3DXVECTOR2(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT));
}

Bg::~Bg()
{
}

void Bg::Begin()
{
}

void Bg::Update()
{
}

void Bg::Event()
{
}

void Bg::Draw()
{
}

const D3DXVECTOR2& Bg::GetSize() const
{
	return m_Size;
}

const float Bg::GetWidth() const
{
	return m_Size.x;
}

const float Bg::GetHeight() const
{
	return m_Size.y;
}
