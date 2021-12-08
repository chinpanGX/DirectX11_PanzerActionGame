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
	m_Reload->Update();
	m_Vehicle->Update();
	m_MoveComponent->Update();

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

Reload & Pawn::reload() const
{
	if (!m_Reload)
	{
		throw std::domain_error("null");
	}
	return *m_Reload;
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
	// 0以下になったら、ゲームマネージャーに知らせる
	if (m_Vehicle->status().hp() <= 0.0f)
	{
		Engine::Get().application()->GetScene()->GetGameObject<GameManager>(ELayer::LAYER_SYSTEM)->BeginEvent(pawn, m_Type);
		// スキルの状態をリセット
		m_Vehicle->skill().Reset(m_Vehicle->status());
		// HPを最大にする
		RespawnSetMaxHP();
	}
}

void Pawn::RespawnSetMaxHP()
{
	m_Vehicle->status().hp(m_Vehicle->status().maxHp());
}

void Pawn::SetStartPosition(Pawn * pawn, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	m_Vehicle->SetStartPosition(pawn, pos, rot);
	m_Pivot->SetStartPosition(pos, rot);
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
	m_MoveComponent = std::make_unique<MoveComponent>(m_Vehicle->status());	

	if (m_Type == 0)
	{
		m_Reload = std::make_unique<PlayerReload>();
	}
	else
	{
		m_Reload = std::make_unique<CpuReload>(m_Vehicle->status());
	}
}

void Pawn::BeginOverlap(Pawn* pPawn)
{
	// 壁との当たり判定
	auto wallFence = Engine::Get().application()->GetScene()->GetGameObjects<WallBox>(ELayer::LAYER_3D_STAGE);
	for (auto w : wallFence)
	{
		if (Intersect(pPawn->vehicle().collider(0).GetOBB3(), w->collider().GetOBB3()))
		{
			// 前進
			if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(InputCode::Forward))
			{
				pPawn->moveComponent().MoveBackward(pPawn->vehicle().bodyTransform(), Fps::Get().deltaTime);
			}					
			// 後退
			if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(InputCode::Backward))
			{
				pPawn->moveComponent().MoveForward(pPawn->vehicle().bodyTransform(), Fps::Get().deltaTime);
			}

			auto tmp = pPawn->vehicle().bodyTransform().position() + w->OffsetLength(pPawn->vehicle().collider(0).GetOBB3());
			pPawn->vehicle().bodyTransform().position(tmp);
		}		
	}
}
