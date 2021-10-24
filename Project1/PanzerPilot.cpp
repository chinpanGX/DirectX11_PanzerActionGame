/*---------------------------------------------------------------

	[PanzerPilot.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "MoveComponent.h"
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Player.h"
#include "Vehicle.h"
#include "Fps.h"
#include "PanzerPilot.h"

PanzerPilot::PanzerPilot(Vehicle & vehicle) : m_Vehicle(vehicle)
{
	m_Transform = Actor::AddComponent<Transform>();
	m_MoveComponent = std::make_unique<MoveComponent>(m_Vehicle.GetStatus());
}

PanzerPilot::~PanzerPilot()
{

}

void PanzerPilot::Begin()
{
}

void PanzerPilot::Update()
{
	Move();
}

void PanzerPilot::Event()
{
}

void PanzerPilot::Draw()
{
	
}

void PanzerPilot::SetStartPosition(Math::Vector3 Position, Math::Vector3 Rot)
{
	auto tmp = Position;
	tmp.y += 5.0f;
	m_Transform->SetPosition(tmp);
	m_Transform->SetRotation(Rot.x, Rot.y, Rot.z);
}

const float PanzerPilot::GetTpsOffset() const
{
	return m_TspOffset;
}

const float PanzerPilot::GetFpsOffset() const
{
	return m_FpsOffset;
}

const float PanzerPilot::GetTargetOffset() const
{
	return m_TargetOffset;
}

void PanzerPilot::Move()
{
	// 移動はボディの位置に合わせる
	Math::Vector3& pos = m_Transform->GetPosition();
	Math::Vector3 body = m_Vehicle.GetBodyTransform().GetPosition();
	pos.x = body.x;
	pos.z = body.z;
}

MoveComponent & PanzerPilot::GetMoveComponent() const
{
	if (!m_MoveComponent)
	{
		std::domain_error("null");
	}
	return *m_MoveComponent;
}
