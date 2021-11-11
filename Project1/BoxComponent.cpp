/*----------------------------------------------------------

	[BoxComponent.cpp]
	Author : 出合翔太

-----------------------------------------------------------*/
#include "Transform.h"
#include "BoxComponent.h"
#include <stdexcept>
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Player.h"
#include "Enemy.h"
#include "WallBox.h"
#include "NormalBullet.h"
#include "Fence.h"
#include "Target.h"

BoxComponent::BoxComponent()
{

}

BoxComponent::~BoxComponent()
{
	
}

// 位置の更新
void BoxComponent::Update(const Math::Vector3& Position, const Transform & t)
{
	if (m_sphere)
	{
		m_sphere->Update(Position);
	}
	if (m_aabb)
	{
		m_aabb->Update(Position);
	}
	if (m_obb)
	{
		m_obb->Update(Position, t);
	}
}

void BoxComponent::SystemDraw()
{
	// Debub用描画
	if (m_aabb)
	{
		m_aabb->SystemDraw();
	}
	if (m_obb)
	{
		m_obb->SystemDraw();
	}
}

void BoxComponent::SetSphere3(const Transform & t, const float & Radius)
{
	auto transform = t;
	m_sphere = std::make_unique<Sphere3>(transform.position(), Radius);
}

const Sphere3 & BoxComponent::GetSphere3() const
{
	if (!m_sphere)
	{
		throw std::domain_error("null pointer");
	}
	return *m_sphere;
}

void BoxComponent::SetAABB3(const Transform& t, const Math::Vector3 & Size)
{
	auto transform = t;
	m_aabb = std::make_unique<AABB3>(transform.position(), Size);
}

const AABB3& BoxComponent::GetAABB3() const
{
	if (!m_aabb)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_aabb;
}

void BoxComponent::SetOBB3(const Transform& t, const Math::Vector3 & Size)
{
	m_obb = std::make_unique<OBB3>(t, Size);
}

const OBB3 & BoxComponent::GetOBB3() const
{
	if (!m_obb)
	{
		throw std::domain_error("nullptr");
	}
	return *m_obb;
}

void CollisionTriggerEvent()
{
	auto scene = Engine::Get().application()->GetScene();
	auto player = scene->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	auto enemys = scene->GetGameObjects<Enemy>(ELayer::LAYER_3D_ACTOR);
	auto wallboxs = scene->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	auto fences = scene->GetGameObjects<Fence>(ELayer::LAYER_3D_STAGE);
	auto targets = scene->GetGameObjects<Target>(ELayer::LAYER_2D_EFFECT);
	auto bullets = scene->GetGameObjects<NormalBullet>(ELayer::LAYER_3D_ACTOR);

	// プレイヤー
	for (auto e : enemys)
	{
		// 戦車同士の当たり判定
		if (Intersect(player->GetVehicle().GetBoxComponent(0).GetSphere3(), e->GetVehicle().GetBoxComponent(0).GetSphere3()))
		{
			if (Intersect(player->GetVehicle().GetBoxComponent(0).GetOBB3(), e->GetVehicle().GetBoxComponent(0).GetOBB3()))
			{
				player->OnTriggerEvent();
				e->OnTriggerEvent();
			}
		}
	}

	// 弾
	for (auto b : bullets)
	{
		//　弾とプレイヤー
		if (Intersect(b->GetBoxComponent().GetSphere3(), player->GetVehicle().GetBoxComponent(0).GetSphere3()))
		{
			for (int i = 0; i < 3; i++)
			{
				if (Intersect(b->GetBoxComponent().GetOBB3(), player->GetVehicle().GetBoxComponent(i).GetOBB3()))
				{
					b->OnCollisionEnter();
					player->OnCollisionEnter();
				}
			}
		}

		// 弾とエネミー
		for (auto e : enemys)
		{
			if (Intersect(b->GetBoxComponent().GetSphere3(), e->GetVehicle().GetBoxComponent(0).GetSphere3()))
			{
				for (int i = 0; i < 3; i++)
				{
					if (Intersect(b->GetBoxComponent().GetOBB3(), e->GetVehicle().GetBoxComponent(i).GetOBB3()))
					{
						b->OnCollisionEnter();
						e->OnCollisionEnter();
					}
				}
			}
		}
	}
}
