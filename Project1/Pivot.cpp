/*---------------------------------------------------------------

	[Pivot.cpp]
	Author : 出合翔太

	カメラ、弾の出る位置などの基準の位置を管理するクラス

---------------------------------------------------------------*/
#include "MoveComponent.h"
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Player.h"
#include "Vehicle.h"
#include "Fps.h"
#include "Pivot.h"

Pivot::Pivot(Vehicle & Vehicle) : m_Vehicle(Vehicle)
{
	m_Transform = AddComponent<Transform>();
	m_MoveComponent = std::make_unique<MoveComponent>(Vehicle.GetStatus());
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
	m_Transform->SetPosition(tmp);
	m_Transform->SetRotation(Rot.x, Rot.y, Rot.z, 1.0f);
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
	m_Transform->GetPosition().x = m_Vehicle.GetBodyTransform().GetPosition().x;
	m_Transform->GetPosition().z = m_Vehicle.GetBodyTransform().GetPosition().z;
}

MoveComponent & Pivot::GetMoveComponent() const
{
	if (!m_MoveComponent)
	{
		std::domain_error("null");
	}
	return *m_MoveComponent;
}
