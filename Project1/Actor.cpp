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

BoxComponent & Actor::GetBoxComponent() const
{
	if (!m_BoxComponent)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_BoxComponent;
}

#pragma region proteced_method
void Actor::UpdateCollision(BoxComponent & BoxComponent)
{
	BoxComponent.Update(m_Transform->position(), *m_Transform);
}

void Actor::UpdateMatrix(Transform & Transform)
{
	DirectX::XMMATRIX world, scale, rot, trans;
	scale = Math::Matrix::MatrixScaling(m_Transform->scale());
	rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->rotation());
	trans = Math::Matrix::MatrixTranslation(m_Transform->position());
	world = scale * rot * trans;
	Engine::Get().graphics()->SetWorldMatrix(world);
}
#pragma endregion protecedメソッド