/*------------------------------------------------------------

	[Plane.cpp]
	Author : èoçá„ƒëæ

--------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Engine.h"
#include "Renderer3D.h"
#include "Grass.h"
#include "Plane.h"

Plane::Plane()
{
	m_Transform = AddComponent<Transform>();
	m_Renderer = std::make_unique<Renderer3D>(*Engine::Get().GetGraphics(), m_Transform->GetPosition(), Math::Vector3::Zero, m_Transform->GetScale());
}

Plane::~Plane()
{
	
}

void Plane::Begin()
{
	m_Transform->SetScale(1000.0f, 1.0f, 1000.0f);
	m_Renderer->CreatePlane(10, 1000);
}

void Plane::Update()
{
	
}

void Plane::Event()
{
}

void Plane::Draw()
{
	GetResource().SetShader("NoLighting");
	GetResource().SetTexture(0, "Grass");
	Actor::UpdateMatrix(*m_Transform);
	m_Renderer->Draw();
}

