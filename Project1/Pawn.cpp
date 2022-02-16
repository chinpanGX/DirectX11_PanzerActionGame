/*--------------------------------------------------------------
	
	[Pawn.cpp]
	Author : 出合翔太

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
	m_MoveComponent->Update(m_Vehicle->GetBodyTransform());

	auto ColliderPosition = m_Vehicle->GetBodyTransform().GetPosition();
	ColliderPosition.y = m_Vehicle->GetBodyTransform().GetPosition().y + 1.0f;
	m_Vehicle->ColiisionUpdate(0, ColliderPosition, m_Vehicle->GetBodyTransform());
	m_Vehicle->ColiisionUpdate(1, m_Pivot->GetTransform().GetPosition(), m_Pivot->GetTransform());
}

void Pawn::Event()
{
}

void Pawn::Draw()
{
	
}

Vehicle & Pawn::GetVehicle() const
{
	if (!m_Vehicle)
	{
		throw std::domain_error("null pointer"); // nullptrのとき例外エラー
	}
	return *m_Vehicle;
}

Pivot & Pawn::GetPivot() const
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
		throw std::domain_error("null");
	}
	return *m_MoveComponent;
}

void Pawn::CheckZeroHp(Pawn* Pawn)
{
	// 0以下になったら、ゲームマネージャーに知らせる
	if (m_Vehicle->GetStatus().GetHp() <= 0.0f)
	{
		Engine::Get().GetApplication()->GetScene()->GetGameObject<GameManager>(ELayer::LAYER_SYSTEM)->BeginEvent(Pawn, m_Type);
	}
}

void Pawn::SetStartPosition(Pawn * Pawn, const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot)
{
	m_Vehicle->SetStartPosition(Pawn, Pos, Rot);
	m_Pivot->SetStartPosition(Pos, Rot);
}

void Pawn::Create()
{
	// Vehicleを作成
	Factory::FVehicle fvehicle;
	m_Vehicle = fvehicle.Create(m_Type);
	// Pivotを作成
	Factory::FPivot fPivot;
	m_Pivot = fPivot.Create(*m_Vehicle);
	// 移動用コンポーネント
	m_MoveComponent = std::make_unique<MoveComponent>(m_Vehicle->GetStatus());	
}

void Pawn::BeginOverlap(Pawn* Pawn)
{
	// 壁との当たり判定
	auto wallFence = Engine::Get().GetApplication()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto w : wallFence)
	{
		if (Intersect(Pawn->GetVehicle().GetCollider(0).GetOBB3(), w->GetCollider().GetOBB3()))
		{
			D3DXVECTOR3 normal = w->OffsetLength(Pawn->GetVehicle().GetCollider(0).GetOBB3()) * 2.0f;
			D3DXVECTOR3 scratch = normal - Pawn->GetMoveComponent().velocity();
			Pawn->GetVehicle().GetBodyTransform().GetPosition() += scratch * Fps::Get().deltaTime;
		}		
	}
}
