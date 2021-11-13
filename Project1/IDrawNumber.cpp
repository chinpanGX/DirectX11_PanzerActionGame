/*--------------------------------------------------------------

	[IDrawNumber.cpp]
	Author : �o���đ�

	������`�悷��C���^�[�t�F�C�X

---------------------------------------------------------------*/
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "IDrawNumber.h"

IDrawNumber::IDrawNumber(float size , int32_t digit) : m_Size(size), m_digit(digit)
{
	m_Render = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Number");
	// �e�N�X�`�����W��x�̒l
	m_Numbers = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f };
	m_Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}

void IDrawNumber::SetColor(float r, float g, float b, float a)
{
	m_Color = D3DXVECTOR4(r, g, b, a);
}

void IDrawNumber::NumberDraw(const D3DXVECTOR2& position, int32_t n)
{
	m_Render->Draw(position, D3DXVECTOR2(m_Size, m_Size), D3DXVECTOR2(m_Numbers[n], 0.0f), D3DXVECTOR2(m_Numbers[n + 1], 1.0f), m_Color);
}

const float IDrawNumber::GetSize() const
{
	return m_Size;
}

const int32_t IDrawNumber::Getdigit() const
{
	return m_digit;
}
