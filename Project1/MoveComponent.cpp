/*--------------------------------------------------------------

	[MoveComponent.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Vehicle.h"
#include "Status.h"
#include "MoveComponent.h"
#include "myLib.h"
#include "Pawn.h"
#include "Turret.h"
#include "MainGun.h"
#include "Engine.h"
#include "Application.h"
#include "Command.h"

MoveComponent::MoveComponent(Status & status) : m_Status(status)
{

}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(Transform& Transform)
{
	if (m_cmd == nullptr)
	{
		m_cmd = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	}
	bool nowInput = false;
	myLib::Timeline acc(0.0f, m_Status.GetSpeed(), m_Status.GetAddForce());
	for (int32_t i = 0; i < 2; i++)
	{
		nowInput = m_cmd->GetNowInput(i);
		if (nowInput == true) { break; }
	}
	// スピードアップ
	if (nowInput)
	{
		acc.Start(m_Speed);
	}
	// ブレーキ
	else if (!nowInput)
	{
		m_Speed -= 1.0f;
		m_Speed = Math::Max(m_Speed, 0.0f);
	}
}

// 前進
void MoveComponent::MoveForward(Transform & Transform, float DeltaTime)
{
	// 進むベクトル
	m_Velocity = Transform.forward() * m_Speed * DeltaTime;	

	Transform.GetPosition().x += m_Velocity.x;
	Transform.GetPosition().z += m_Velocity.z;
}

// 後退
void MoveComponent::MoveBackward(Transform & Transform, float DeltaTime)
{
	m_Velocity = -Transform.forward() * m_Speed * DeltaTime;

	Transform.GetPosition().x += m_Velocity.x;
	Transform.GetPosition().z += m_Velocity.z;
}

// 右旋回
void MoveComponent::RotRight(Transform & Transform, float DeltaTime)
{
	Transform.GetRotation().y += m_Status.GetRotSpeed() * DeltaTime;
}

// 左旋回
void MoveComponent::RotLeft(Transform & Transform, float DeltaTime)
{	
	Transform.GetRotation().y -= m_Status.GetRotSpeed() * DeltaTime;	
}

// 砲塔をあげる
void MoveComponent::GunUp(Transform & Transform, float DeltaTime)
{
	Transform.GetRotation().x -= m_Status.GetRotSpeed() * 0.9f * DeltaTime;
	if (Transform.GetRotation().x <= -m_Status.GetGunAngleUpMax())
	{
		Transform.GetRotation().x = -m_Status.GetGunAngleUpMax();
	}
}

// 砲塔を下げる
void MoveComponent::GunDown(Transform & Transform, float DeltaTime)
{
	Transform.GetRotation().x += m_Status.GetRotSpeed() * 0.9f * DeltaTime;
	if (Transform.GetRotation().x >= m_Status.GetGunAngleDownMax())
	{
		Transform.GetRotation().x = m_Status.GetGunAngleDownMax();
	}
}

// ストップ
void MoveComponent::Stop()
{
	m_Speed = 0.0f;
}

const D3DXVECTOR3 & MoveComponent::GetVelocity() const
{
	return m_Velocity;
}
