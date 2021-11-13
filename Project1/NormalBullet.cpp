/*-----------------------------------------------------------

	[NormalBullet.cpp]
	Author : 出合翔太

	通常弾の処理

------------------------------------------------------------*/
#include "Vehicle.h"
#include "Engine.h"
#include "Resource.h"
#include "BulletStateMove.h"
#include "BulletStateDestory.h"
#include "Fps.h"
#include "Engine.h"
#include "Application.h"
#include "MuzzleFlash.h"
#include "BulletComponentEvent.h"
#include "Player.h" 
#include "Enemy.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet() : m_Resource(*Engine::Get().resource())
{
	AddComponentEvent<BulletEvent::OnComponentEventFence>();
	AddComponentEvent<BulletEvent::OnComponentEventWallBox>();
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Begin()
{
}

void NormalBullet::Update()
{
	m_State->Update(this, Fps::Get().deltaTime);
	Actor::UpdateCollision(*m_BoxComponent);
}

void NormalBullet::Event()
{
	// 当たったら、消す
	if(Actor::CollisionEnter())
	{
		ChangeState(std::make_unique<BulletStateDestory>());
	}
}

void NormalBullet::Draw()
{
	m_Resource.SetShader("Default");
	// マトリクス設定
	Actor::UpdateMatrix(*m_Transform);
	m_Resource.SetStaticModel("Bullet");
	//m_BoxComponent->SystemDraw();
}

void NormalBullet::Create(const D3DXVECTOR3& Position, const D3DXVECTOR3 & Vector)
{
	// インスタンス生成
	Bullet::SetProperty(Vector, 300.0f, 240);
	m_Transform = Actor::AddComponent<Transform>();
	m_Transform->position(Position);
	m_Transform->scale(1.5f);

	// コンポーネントの設定
	m_BoxComponent = Actor::AddComponent<BoxComponent>();
	D3DXVECTOR3 scale = m_Transform->scale() * 0.5f;
	m_BoxComponent->SetSphere3(*m_Transform, 1.0f);
	m_BoxComponent->SetAABB3(*m_Transform, scale);
	m_BoxComponent->SetOBB3(*m_Transform, scale);
	m_State = std::make_unique<BulletStateMove>();

	// リソース
	auto effect = Engine::Get().application()->GetScene()->AddGameObject<MuzzleFlash>(ELayer::LAYER_2D_EFFECT);
	effect->transform().position(Position);
}

void NormalBullet::ChangeState(std::unique_ptr<BulletState> State)
{
	m_State = std::move(State);
}

void NormalBullet::OnCollision()
{
	// プレイヤー
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		OnCollisionToPawn(player);
	}

	// エネミー
	auto enemy_1 = Engine::Get().application()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
	if (enemy_1)
	{
		OnCollisionToPawn(enemy_1);
	}
	BeginOverlap(this);
}

void NormalBullet::OnCollisionToPawn(Pawn * Pawn)
{
	// 球同士の当たり判定を取る
	if (Intersect(m_BoxComponent->GetSphere3(), Pawn->vehicle().GetBoxComponent(0).GetSphere3()))
	{
		for (int i = 0; i < 3; i++)
		{
			if (Intersect(m_BoxComponent->GetOBB3(), Pawn->vehicle().GetBoxComponent(i).GetOBB3()))
			{
				Bullet::OnCollisionEnter();
				Pawn->OnCollisionEnter();
			}
		}
	}
}


