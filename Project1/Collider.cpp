/*----------------------------------------------------------

	[Collider.cpp]
	Author : 出合翔太

-----------------------------------------------------------*/
#include "Transform.h"
#include "Collider.h"
#include <stdexcept>
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Player.h"
#include "Enemy.h"
#include "WallBox.h"
#include "Fence.h"
#include "Target.h"

Collider::Collider()
{

}

Collider::~Collider()
{
	
}

// 位置の更新
void Collider::Update(const D3DXVECTOR3& Position, Transform & Transform)
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
		m_obb->Update(Position, Transform);
	}
}

void Collider::SystemDraw()
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

void Collider::SetSphere3(const Transform & t, const float & Radius)
{
	auto transform = t;
	m_sphere = std::make_unique<Sphere3>(transform.GetPosition(), Radius);
}

const Sphere3 & Collider::GetSphere3() const
{
	if (!m_sphere)
	{
		throw std::domain_error("null pointer");
	}
	return *m_sphere;
}

void Collider::SetAABB3(const Transform& t, const D3DXVECTOR3 & Size)
{
	auto transform = t;
	m_aabb = std::make_unique<AABB3>(transform.GetPosition(), Size);
}

const AABB3& Collider::GetAABB3() const
{
	if (!m_aabb)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_aabb;
}

void Collider::SetOBB3(const Transform& t, const D3DXVECTOR3 & Size)
{
	m_obb = std::make_unique<OBB3>(t, Size);
}

const OBB3 & Collider::GetOBB3() const
{
	if (!m_obb)
	{
		throw std::domain_error("nullptr");
	}
	return *m_obb;
}
