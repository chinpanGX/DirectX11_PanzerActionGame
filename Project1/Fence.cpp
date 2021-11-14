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
	m_Collider = AddComponent<Collider>();
}

Fence::~Fence()
{

}

void Fence::Begin()
{
	m_Collider->SetAABB3(*m_Transform, D3DXVECTOR3(8.0f, 6.0f, 2.0f));
	m_Collider->SetOBB3(*m_Transform, D3DXVECTOR3(8.0f, 6.0f, 2.0f));
}

void Fence::Update()
{
	Actor::UpdateCollision(*m_Collider);
	// プレイヤー
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		OnCollisionToVehicle(player->vehicle());
	}
	// エネミー
	auto enemy_1 = Engine::Get().application()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
	if (enemy_1)
	{
		OnCollisionToVehicle(enemy_1->vehicle());
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
	if (Intersect(m_Collider->GetOBB3(), Vehicle.collider(0).GetOBB3()))
	{
		OnCollisionEnter();
	}
}
