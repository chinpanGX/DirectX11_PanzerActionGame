/*------------------------------------------------------------

	[PlaneGarage.cpp]
	Author : èoçá„ƒëæ

-------------------------------------------------------------*/
#include "Renderer3D.h"
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "PlaneGarage.h"

PlaneGarage::PlaneGarage()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Renderer = std::make_unique<Renderer3D>(*Engine::Get().GetGraphics(), m_Transform->position(), Math::Vector3::Zero, m_Transform->scale());
}

PlaneGarage::~PlaneGarage()
{
}

void PlaneGarage::Begin()
{
	m_Transform->position(Math::Vector3(-27.0f, 0.0f, 0.0f));
	m_Transform->scale(1.0f);
	m_Renderer->CreatePlane(50, 50);
}

void PlaneGarage::Update()
{
}

void PlaneGarage::Event()
{
}

void PlaneGarage::Draw()
{
	GetResource().SetShader("Mapping");
	GetResource().SetTexture(0, "Plane");
	GetResource().SetTexture(1, "Waffuru");
	Actor::UpdateMatrix(*m_Transform);
	m_Renderer->Draw();
}
