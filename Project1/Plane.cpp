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
	m_Renderer = std::make_unique<Renderer3D>(*Engine::Get().graphics(), m_Transform->position(), D3DXVECTOR3(0.0f,0.0f,0.0f), m_Transform->scale());
}

Plane::~Plane()
{
	
}

void Plane::Begin()
{
	m_Transform->scale(1000.0f, 1.0f, 1000.0f);
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
	resource().SetShader("NoLighting");
	resource().SetTexture(0, "Grass");
	Actor::UpdateMatrix(*m_Transform);
	m_Renderer->Draw();
}

