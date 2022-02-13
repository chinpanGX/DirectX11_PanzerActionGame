/*------------------------------------------------------------

	[PlaneGarage.cpp]
	Author : �o���đ�

	��ԑq�ɂ̒n��

-------------------------------------------------------------*/
#include "Renderer3D.h"
#include "Engine.h"
#include "Graphics.h"
#include "Resource.h"
#include "PlaneGarage.h"

PlaneGarage::PlaneGarage()
{
	m_Transform = AddComponent<Transform>();
	m_Renderer = std::make_unique<Renderer3D>(*Engine::Get().GetGraphics(), m_Transform->GetPosition(), D3DXVECTOR3(0.0f,0.0f,0.0f), m_Transform->GetScale());
}

PlaneGarage::~PlaneGarage()
{
}

void PlaneGarage::Begin()
{
	m_Transform->SetPosition(D3DXVECTOR3(-27.0f, 0.0f, 0.0f));
	m_Transform->SetScale(1.0f);
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
	// �o���v�}�b�s���O�̐ݒ�
	GetResource().SetShader("Mapping");
	GetResource().SetTexture(0, "Plane");
	GetResource().SetTexture(1, "Waffuru");
	Actor::UpdateMatrix(*m_Transform);
	m_Renderer->Draw();
}
