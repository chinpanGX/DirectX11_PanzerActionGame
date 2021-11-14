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

Transform & Actor::transform() const
{
	if (!m_Transform)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_Transform;
}

Collider & Actor::collider() const
{
	if (!m_Collider)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_Collider;
}

#pragma region proteced_method
void Actor::UpdateCollision(Collider & Collider)
{
	Collider.Update(m_Transform->position(), *m_Transform);
}

void Actor::UpdateMatrix(Transform & Transform)
{
	D3DXMATRIX world, scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, Transform.scale());
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, Transform.rotation());
	Math::Matrix::MatrixTranslation(&trans, Transform.position());
	world = scale * rot * trans;
	Engine::Get().graphics()->SetWorldMatrix(world);
}
#pragma endregion protecedメソッド