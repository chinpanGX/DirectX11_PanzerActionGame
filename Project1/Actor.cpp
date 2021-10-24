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
	BoxComponent.Update(m_Transform->GetPosition(), *m_Transform);
}

void Actor::UpdateMatrix(Transform & Transform)
{
	DirectX::XMMATRIX world, scale, rot, trans;
	scale = Math::Matrix::MatrixScaling(m_Transform->GetScale());
	rot = Math::Matrix::MatrixRotationQuatrnionRollPitchYaw(m_Transform->GetRotation());
	trans = Math::Matrix::MatrixTranslation(m_Transform->GetPosition());
	world = scale * rot * trans;
	Engine::Get().GetGraphics()->SetWorldMatrix(world);
}
#pragma endregion protecedメソッド