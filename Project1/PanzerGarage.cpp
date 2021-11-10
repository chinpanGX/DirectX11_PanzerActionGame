/*------------------------------------------------------------

	[PanzerGarage.cpp]
	Author : èoçá„ƒëæ

	êÌé‘ëqå…

-------------------------------------------------------------*/
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
#include "PanzerGarage.h"

PanzerGarage::PanzerGarage() : m_Graphics(*Engine::Get().GetGraphics())
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
	light.Direction = DirectX::XMFLOAT4(-1.0f, -1.0f, 1.0f, 0.0f);
	DirectX::XMVector4Normalize(DirectX::XMLoadFloat4(&light.Direction));
	light.Ambient = DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Graphics.SetLight(light);

	GetResource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	GetResource().SetStaticModel("PanzerGarage");

	light.Enable = false;
	m_Graphics.SetLight(light);
}
