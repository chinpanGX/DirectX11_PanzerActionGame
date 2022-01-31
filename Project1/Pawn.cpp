/*--------------------------------------------------------------
	
	[Pawn.cpp]
	Author : �o���đ�

---------------------------------------------------------------*/
#include "Vehicle.h"
#include "Reload.h"
#include "Status.h"
#include "Skill.h"
#include "Pivot.h"
#include "MoveComponent.h"
#include "Engine.h"
#include "Application.h"
#include "GameManager.h"
#include "GameCamera.h"
#include "WallBox.h"
#include "Fps.h"
#include "Command.h"
#include "Pawn.h"

Pawn::Pawn()
{
	
}

Pawn::Pawn(int32_t Type) : m_Type(Type)
{
	
}

Pawn::~Pawn()
{
	
}

void Pawn::Begin()
{
}

void Pawn::Update()
{
	m_Vehicle->Update();
	m_MoveComponent->Update(m_Vehicle->bodyTransform());

	auto colliderPosition = m_Vehicle->bodyTransform().position();
	colliderPosition.y = m_Vehicle->bodyTransform().position().y + 1.0f;
	m_Vehicle->ColiisionUpdate(0, colliderPosition, m_Vehicle->bodyTransform());
	m_Vehicle->ColiisionUpdate(1, m_Pivot->transform().position(), m_Pivot->transform());
}

void Pawn::Event()
{
}

void Pawn::Draw()
{
	
}

Vehicle & Pawn::vehicle() const
{
	if (!m_Vehicle)
	{
		throw std::domain_error("null pointer"); // nullptr�̂Ƃ���O�G���[
	}
	return *m_Vehicle;
}

Pivot & Pawn::pivot() const
{
	if (!m_Pivot)
	{
		throw std::domain_error("null pointer");
	}
	return *m_Pivot;
}

MoveComponent & Pawn::moveComponent() const
{
	if (!m_MoveComponent)
	{
		throw std::domain_error("null");
	}
	return *m_MoveComponent;
}

void Pawn::CheckZeroHp(Pawn* pawn)
{
	// 0�ȉ��ɂȂ�����A�Q�[���}�l�[�W���[�ɒm�点��
	if (m_Vehicle->status().hp() <= 0.0f)
	{
		Engine::Get().application()->GetScene()->GetGameObject<GameManager>(ELayer::LAYER_SYSTEM)->BeginEvent(pawn, m_Type);
	}
}

void Pawn::SetStartPosition(Pawn * pawn, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	m_Vehicle->SetStartPosition(pawn, pos, rot);
	m_Pivot->SetStartPosition(pos, rot);
}

void Pawn::Create()
{
	// Vehicle���쐬
	Factory::FVehicle fvehicle;
	m_Vehicle = fvehicle.Create(m_Type);
	// Pivot���쐬
	Factory::FPivot fPivot;
	m_Pivot = fPivot.Create(*m_Vehicle);
	// �ړ��p�R���|�[�l���g
	m_MoveComponent = std::make_unique<MoveComponent>(m_Vehicle->status());	
}

void Pawn::BeginOverlap(Pawn* pPawn)
{
	// �ǂƂ̓����蔻��
	auto wallFence = Engine::Get().application()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto w : wallFence)
	{
		if (Intersect(pPawn->vehicle().collider(0).GetOBB3(), w->collider().GetOBB3()))
		{
			D3DXVECTOR3 normal = w->OffsetLength(pPawn->vehicle().collider(0).GetOBB3()) * 2.0f;
			D3DXVECTOR3 scratch = normal - pPawn->moveComponent().velocity();
			pPawn->vehicle().bodyTransform().position() += scratch * Fps::Get().deltaTime;
		}		
	}
}
