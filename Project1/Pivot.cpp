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
	m_Transform = Actor::AddComponent<Transform>();
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
	// 移動はボディの位置に合わせる
	D3DXVECTOR3 pos = m_Transform->position();
	D3DXVECTOR3 body = m_Vehicle.bodyTransform().position();
	pos.x = body.x;
	pos.z = body.z;
	m_Transform->position(pos);
}

MoveComponent & Pivot::moveComponent() const
{
	if (!m_MoveComponent)
	{
		std::domain_error("null");
	}
	return *m_MoveComponent;
}
