/*-----------------------------------------------------------

	[Fence.cpp]
	Author : 出合翔太

------------------------------------------------------------*/
#include "Resource.h"
#include "Engine.h"
#include "Application.h"
#include "Collision.h"
#include "Vehicle.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Fence.h"

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
	m_EnemyList = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Enemy>(ELayer::LAYER_3D_ACTOR);
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_Camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);

	StageObject::SetRadius(8.0f);
	m_Collider->SetAABB3(*m_Transform, D3DXVECTOR3(8.0f, 6.0f, 2.0f));
	m_Collider->SetOBB3(*m_Transform, D3DXVECTOR3(8.0f, 6.0f, 2.0f));
}

void Fence::Update()
{
	Actor::UpdateCollision(*m_Collider);
	// プレイヤー
	OnCollisionToVehicle(m_Player->GetVehicle());
	// エネミー
	for(auto enemy : m_EnemyList)
	{
		OnCollisionToVehicle(enemy->GetVehicle());
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
	if (m_Camera->NotDrawObject(m_Transform->GetPosition(), StageObject::GetRadius())) { return; }

	GetResource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	GetResource().SetStaticModel("Fence");
}

void Fence::OnCollisionToVehicle(const Vehicle & Vehicle)
{
	if (Intersect(m_Collider->GetOBB3(), Vehicle.GetCollider(0).GetOBB3()))
	{
		OnCollisionEnter();
	}
}
