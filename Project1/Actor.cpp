/*-------------------------------------------------------------
	
	[Actor.cpp]
	Author : �o���đ�

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
		throw std::domain_error("null pointer"); // nullptr�̂Ƃ���O�G���[
	}
	return *m_Transform;
}

Collider & Actor::GetCollider() const
{
	if (!m_Collider)
	{
		throw std::domain_error("null pointer"); // nullptr�̂Ƃ���O�G���[
	}
	return *m_Collider;
}

#pragma region proteced_method
// �R���W�����ʒu�̍X�V
void Actor::UpdateCollision(Collider & Collider)
{
	Collider.Update(m_Transform->GetPosition(), *m_Transform);
}

// �}�g���N�X�̍X�V
void Actor::UpdateMatrix(Transform & Transform)
{
	D3DXMATRIX world, scale, rot, trans;
	Math::Matrix::MatrixScaling(&scale, Transform.GetScale());
	Math::Matrix::MatrixRotationRollPitchYaw(&rot, Transform.GetRotation());
	Math::Matrix::MatrixTranslation(&trans, Transform.GetPosition());
	world = scale * rot * trans;
	Engine::Get().GetGraphics()->SetWorldMatrix(world);
}
#pragma endregion proteced���\�b�h