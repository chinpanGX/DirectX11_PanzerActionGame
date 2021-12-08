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
#include "Player.h" 
#include "Enemy.h"
#include "Fence.h"
#include "WallBox.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet() : m_Resource(*Engine::Get().resource())
{
	
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
	Actor::UpdateCollision(*m_Collider);
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
}

void NormalBullet::Create(const D3DXVECTOR3& Position, const D3DXVECTOR3 & Vector)
{
	// インスタンス生成
	Bullet::SetStatus(Vector, 300.0f, 240);
	m_Transform = Actor::AddComponent<Transform>();
	m_Transform->position(Position);
	m_Transform->scale(1.5f);

	// コンポーネントの設定
	m_Collider = Actor::AddComponent<Collider>();
	D3DXVECTOR3 scale = m_Transform->scale() * 0.5f;
	m_Collider->SetSphere3(*m_Transform, 1.0f);
	m_Collider->SetAABB3(*m_Transform, scale);
	m_Collider->SetOBB3(*m_Transform, scale);
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
	
	// フェンス
	std::vector<Fence*> fences = Engine::Get().application()->GetScene()->GetGameObjects<Fence>(ELayer::LAYER_3D_STAGE);
	for (Fence* fence : fences)
	{
		if (Intersect(m_Collider->GetAABB3(), fence->collider().GetAABB3()))
		{
			Bullet::OnCollisionEnter();
			fence->OnCollisionEnter();
		}
	}

	// 壁
	auto walls = Engine::Get().application()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto i : walls)
	{
		if (Intersect(m_Collider->GetAABB3(), i->collider().GetAABB3()))
		{
			Bullet::OnCollisionEnter();
			i->OnCollisionEnter();
		}
	}
}

void NormalBullet::OnCollisionToPawn(Pawn * Pawn)
{
	// 球同士の当たり判定を取る
	if (Intersect(m_Collider->GetSphere3(), Pawn->vehicle().collider(0).GetSphere3()))
	{
		// 戦車が持つコライダー文ループ
		for (int i = 0; i < Pawn->vehicle().colliderNum(); i++)
		{
			if (Intersect(m_Collider->GetOBB3(), Pawn->vehicle().collider(i).GetOBB3()))
			{
				Bullet::OnCollisionEnter();
				Pawn->OnCollisionEnter();
				// 当たったらループを抜ける
				break;
			}
		}
	}
}


