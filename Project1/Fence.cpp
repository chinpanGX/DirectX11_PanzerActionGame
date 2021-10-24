/*-----------------------------------------------------------

	[Fence.cpp]
	Author : 出合翔太

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
}

void Fence::Update()
{
	Actor::UpdateCollision(*m_BoxComponent);
	// プレイヤー
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		OnCollisionToVehicle(player->GetVehicle());
	}
	// エネミー
	auto enemy_1 = Engine::Get().GetApplication()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
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
	GetResource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	GetResource().SetStaticModel("Fence");
}

void Fence::OnCollisionToVehicle(const Vehicle & Vehicle)
{
	if (Intersect(m_BoxComponent->GetAABB3(), Vehicle.GetBoxComponent(0).GetAABB3()))
	{
		OnCollisionEnter();
	}
}
