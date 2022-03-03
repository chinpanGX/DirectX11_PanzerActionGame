/*-------------------------------------------------------------
	
	[Actor.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Graphics.h"
#include "Resource.h"
#include "Engine.h"
#include "Actor.h"

Actor::Actor() : m_Transform(nullptr)
{
	
}

Actor::~Actor()
{
}

void Actor::Begin()
{
}

void Actor::Update()
{
}

void Actor::Event()
{
}

void Actor::Draw()
{
}

Transform & Actor::GetTransform() const
{
	if (!m_Transform)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_Transform;
}

Collider & Actor::GetCollider() const
{
	if (!m_Collider)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_Collider;
}

#pragma region proteced_method
// コリジョン位置の更新
void Actor::UpdateCollision(Collider & Collider)
{
	Collider.Update(m_Transform->GetPosition(), *m_Transform);
}

// マトリクスの更新
void Actor::UpdateMatrix(Transform & Transform)
{
	D3DXMATRIX world, scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, Transform.GetScale());
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, Transform.GetRotation());
	Math::Matrix::MatrixTranslation(&trans, Transform.GetPosition());
	world = scale * rot * trans;
	Engine::Get().GetGraphics()->SetWorldMatrix(world);
}
#pragma endregion protecedメソッド