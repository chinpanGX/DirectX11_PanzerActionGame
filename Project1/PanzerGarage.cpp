/*------------------------------------------------------------

	[PanzerGarage.cpp]
	Author : �o���đ�

	��ԑq��

-------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "Application.h"
#include "PanzerGarage.h"

PanzerGarage::PanzerGarage() : m_Graphics(*Engine::Get().graphics())
{
	m_Transform = Actor::AddComponent<Transform>();
}

PanzerGarage::~PanzerGarage()
{
}

void PanzerGarage::Begin()
{
	m_Transform->position(0.0f, 0.0f, -6.0f);
	m_Transform->scale(3.0f);
}

void PanzerGarage::Update()
{
	
}

void PanzerGarage::Event()
{
}

void PanzerGarage::Draw()
{
	resource().SetShader("PixelLighting");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("PanzerGarage");
}
