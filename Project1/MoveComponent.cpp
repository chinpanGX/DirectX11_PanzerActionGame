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

void MoveComponent::Update(Transform& transform)
{
	if (m_cmd == nullptr)
	{
		m_cmd = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	}
	bool nowInput = false;
	myLib::Timeline acc(0.0f, m_Status.speed(), m_Status.addForce());
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

void MoveComponent::MoveForward(Transform & transform, float deltaTime)
{
	// 進むベクトル
	m_Velocity = transform.forward() * m_Speed * deltaTime;	

	transform.GetPosition().x += m_Velocity.x;
	transform.GetPosition().z += m_Velocity.z;
}

void MoveComponent::MoveBackward(Transform & transform, float deltaTime)
{
	m_Velocity = -transform.forward() * m_Speed * deltaTime;

	transform.GetPosition().x += m_Velocity.x;
	transform.GetPosition().z += m_Velocity.z;
}

void MoveComponent::RotRight(Transform & transform, float deltaTime)
{
	transform.GetRotation().y += m_Status.rotSpeed() * deltaTime;
}

void MoveComponent::RotLeft(Transform & transform, float deltaTime)
{	
	transform.GetRotation().y -= m_Status.rotSpeed() * deltaTime;	
}

void MoveComponent::GunUp(Transform & transform, float deltaTime)
{
	transform.GetRotation().x -= m_Status.rotSpeed() * 0.9f * deltaTime;
	if (transform.GetRotation().x <= -m_Status.gunAngleUpMax())
	{
		transform.GetRotation().x = -m_Status.gunAngleUpMax();
	}
}

void MoveComponent::GunDown(Transform & transform, float deltaTime)
{
	transform.GetRotation().x += m_Status.rotSpeed() * 0.9f * deltaTime;
	if (transform.GetRotation().x >= m_Status.gunAngleDownMax())
	{
		transform.GetRotation().x = m_Status.gunAngleDownMax();
	}
}

void MoveComponent::Stop()
{
	m_Speed = 0.0f;
}

D3DXVECTOR3 & MoveComponent::velocity()
{
	return m_Velocity;
}
