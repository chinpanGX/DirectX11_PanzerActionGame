/*------------------------------------------------------------

	[PanzerGarage.cpp]
	Author : èoçá„ƒëæ

	êÌé‘ëqå…

-------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
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
	Light light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(-1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetLight(light);

	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("PanzerGarage");

	light.Enable = false;
	m_Graphics.SetLight(light);
}
