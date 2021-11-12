/*--------------------------------------------------------------
	
	[Pawn.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Vehicle.h"
#include "Status.h"
#include "Pivot.h"
#include "MoveComponent.h"
#include "Engine.h"
#include "Application.h"
#include "GameManager.h"
#include "OnComponentEvent.h"
#include "GameCamera.h"
#include "Pawn.h"

Pawn::Pawn()
{
}

Pawn::Pawn(int32_t Type) : m_Type(Type)
{
	
}

Pawn::~Pawn()
{
	m_ComponentEvent.clear();
}

void Pawn::Begin()
{
}

void Pawn::Update()
{
	m_Vehicle->Update();
	m_MoveComponent->Update();
	m_Vehicle->ColiisionUpdate(0, m_Vehicle->bodyTransform().position(), m_Vehicle->bodyTransform());
	m_Vehicle->ColiisionUpdate(1, m_Pivot->transform().position(), m_Pivot->transform());
	m_Vehicle->ColiisionUpdate(2, Math::Vector3(m_Pivot->transform().position().x, m_Pivot->transform().position().y,
		m_Pivot->transform().position().z + 3.0f), m_Pivot->transform());
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
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
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

MoveComponent & Pawn::GetMoveComponent() const
{
	if (!m_MoveComponent)
	{
		std::domain_error("null");
	}
	return *m_MoveComponent;
}

void Pawn::CheckZeroHp(Pawn* pawn)
{
	// 0以下になったら、ゲームマネージャーに知らせる
	if (m_Vehicle->GetStatus().GetHp() <= 0.0f)
	{
		Engine::Get().application()->GetScene()->GetGameObject<GameManager>(ELayer::LAYER_SYSTEM)->BeginEvent(pawn, m_Type);
	}
}

void Pawn::RespawnSetMaxHP()
{
	m_Vehicle->GetStatus().SetHp(m_Vehicle->GetStatus().GetMaxHp());
}

void Pawn::SetStartPosition(Pawn * pawn, const Math::Vector3& pos, const Math::Vector3& rot)
{
	m_Vehicle->SetStartPosition(pawn, pos, rot);
	m_Pivot->SetStartPosition(pos, rot);
}

void Pawn::Create()
{
	Factory::FVehicle fvehicle;
	m_Vehicle = fvehicle.Create(m_Type);
	Factory::FPivot fPivot;
	m_Pivot = fPivot.Create(*m_Vehicle);
	m_MoveComponent = std::make_unique<MoveComponent>(m_Vehicle->GetStatus());	
}

void Pawn::BeginOverlap(Pawn* pPawn)
{
	for (size_t i = 0; i < m_ComponentEvent.size(); ++i)
	{
		m_ComponentEvent[i]->BeginOverlap(pPawn);
	}
}
