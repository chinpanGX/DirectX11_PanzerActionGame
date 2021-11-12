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

void MoveComponent::Update()
{
	bool nowInput = false;
	myLib::Timeline acc(0.0f, m_Status.GetSpeed(), m_Status.GetAddForce());
	for (int32_t i = 0; i < 2; i++)
	{
		nowInput = Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(i);
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
	D3DXVECTOR3 position = transform.position();
	position.x += transform.forward().x * m_Speed * deltaTime;
	position.z += transform.forward().z * m_Speed * deltaTime;
	transform.position(position);
}

void MoveComponent::MoveBackward(Transform & transform, float deltaTime)
{
	D3DXVECTOR3 position = transform.position();
	position.x += -transform.forward().x * m_Speed * deltaTime;
	position.z += -transform.forward().z * m_Speed * deltaTime;
	transform.position(position);
}

void MoveComponent::RotRight(Transform & transform, float deltaTime)
{
	D3DXVECTOR3 Rotation = transform.rotation();
	Rotation.y += m_Status.GetRotSpeed() * deltaTime;
	transform.rotation(Rotation);
}

void MoveComponent::RotLeft(Transform & transform, float deltaTime)
{
	D3DXVECTOR3 Rotation = transform.rotation();
	Rotation.y -= m_Status.GetRotSpeed() * deltaTime;
	transform.rotation(Rotation);
}

void MoveComponent::GunUp(Transform & transform, float deltaTime)
{
	D3DXVECTOR3 GunRotation = transform.rotation();
	GunRotation.x -= m_Status.GetRotSpeed() * 0.9f * deltaTime;
	if (GunRotation.x <= -m_Status.GetGunAngleUpMax())
	{
		GunRotation.x = -m_Status.GetGunAngleUpMax();
	}
	transform.rotation(GunRotation);
}

void MoveComponent::GunDown(Transform & transform, float deltaTime)
{
	D3DXVECTOR3 GunRotation = transform.rotation();
	GunRotation.x += m_Status.GetRotSpeed() * 0.9f * deltaTime;
	if (GunRotation.x >= m_Status.GetGunAngleDownMax())
	{
		GunRotation.x = m_Status.GetGunAngleDownMax();
	}
	transform.rotation(GunRotation);
}
