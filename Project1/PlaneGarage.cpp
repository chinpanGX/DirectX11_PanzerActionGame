/*------------------------------------------------------------

	[PlaneGarage.cpp]
	Author : 出合翔太

	戦車倉庫の地面

-------------------------------------------------------------*/
#include "Renderer3D.h"
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "PlaneGarage.h"

PlaneGarage::PlaneGarage()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Renderer = std::make_unique<Renderer3D>(*Engine::Get().graphics(), m_Transform->position(), D3DXVECTOR3(0.0f,0.0f,0.0f), m_Transform->scale());
}

PlaneGarage::~PlaneGarage()
{
}

void PlaneGarage::Begin()
{
	m_Transform->position(D3DXVECTOR3(-27.0f, 0.0f, 0.0f));
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
	// バンプマッピングの設定
	resource().SetShader("Mapping");
	resource().SetTexture(0, "Plane");
	resource().SetTexture(1, "Waffuru");
	Actor::UpdateMatrix(*m_Transform);
	m_Renderer->Draw();
}
