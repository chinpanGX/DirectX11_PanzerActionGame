/*-----------------------------------------------------------

	[Fence.cpp]
	Author : �o���đ�

------------------------------------------------------------*/
#include "Fence.h"
#include "Resource.h"
#include "Engine.h"
#include "Application.h"
#include "NormalBullet.h"
#include "Collision.h"
#include "Vehicle.h"
#include "Player.h"
#include "Enemy.h"

Fence::Fence()
{
	m_Transform = AddComponent<Transform>();
	m_BoxComponent = AddComponent<BoxComponent>();
}

Fence::~Fence()
{

}

void Fence::Begin()
{
	m_BoxComponent->SetAABB3(*m_Transform, Math::Vector3(8.0f, 6.0f, 2.0f));
	m_BoxComponent->SetOBB3(*m_Transform, Math::Vector3(8.0f, 6.0f, 2.0f));
}

void Fence::Update()
{
	Actor::UpdateCollision(*m_BoxComponent);
	// �v���C���[
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		OnCollisionToVehicle(player->GetVehicle());
	}
	// �G�l�~�[
	auto enemy_1 = Engine::Get().application()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
	if (enemy_1)
	{
		OnCollisionToVehicle(enemy_1->GetVehicle());
	}
}

void Fence::Event()
{
	if (CollisionEnter())
	{
		OnDestroy();
	}
}

void Fence::Draw()
{
	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("Fence");
}

void Fence::OnCollisionToVehicle(const Vehicle & Vehicle)
{
	if (Intersect(m_BoxComponent->GetOBB3(), Vehicle.GetBoxComponent(0).GetOBB3()))
	{
		OnCollisionEnter();
	}
}
