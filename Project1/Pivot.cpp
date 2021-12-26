/*---------------------------------------------------------------

	[Pivot.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "MoveComponent.h"
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Player.h"
#include "Vehicle.h"
#include "Fps.h"
#include "Pivot.h"

Pivot::Pivot(Vehicle & vehicle) : m_Vehicle(vehicle)
{
	m_Transform = AddComponent<Transform>();
	m_MoveComponent = std::make_unique<MoveComponent>(m_Vehicle.status());
}

Pivot::~Pivot()
{

}

void Pivot::Begin()
{
}

void Pivot::Update()
{
	Move();
}

void Pivot::Event()
{
}

void Pivot::Draw()
{
	
}

void Pivot::SetStartPosition(D3DXVECTOR3 Position, D3DXVECTOR3 Rot)
{
	auto tmp = Position;
	tmp.y += 5.0f;
	m_Transform->position(tmp);
	m_Transform->rotation(Rot.x, Rot.y, Rot.z, 1.0f);
}

const float Pivot::GetTpsOffset() const
{
	return m_TspOffset;
}

const float Pivot::GetFpsOffset() const
{
	return m_FpsOffset;
}

const float Pivot::GetTargetOffset() const
{
	return m_TargetOffset;
}

void Pivot::Move()
{
	m_Transform->position().x = m_Vehicle.bodyTransform().position().x;
	m_Transform->position().z = m_Vehicle.bodyTransform().position().z;
}

MoveComponent & Pivot::moveComponent() const
{
	if (!m_MoveComponent)
	{
		std::domain_error("null");
	}
	return *m_MoveComponent;
}
