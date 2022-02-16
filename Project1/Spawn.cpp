/*--------------------------------------------------------------

	[Spwan.cpp]
	Author : 出合翔太

	スポーンをする

--------------------------------------------------------------*/
#include "Input.h"
#include "GameManager.h"
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Player.h"
#include "Enemy.h"
#include "SPawn.h"

Respawn::Respawn()
{
	m_SPawn.emplace_back(std::make_unique<PlayerSPawn>());
	m_SPawn.emplace_back(std::make_unique<EnemySPawn>());
}

Respawn::~Respawn()
{
}

void Respawn::Begin()
{
}

void Respawn::Update(GameManager * Manager, Pawn * Pawn, int32_t Type)
{
	if (!Manager->GetGameEnd()) // falseならゲーム終了ではないので、リスポーンする
	{
		switch (Type)
		{
		case ID::E_Player:
			m_SPawn[ID::E_Player]->SetSPawn();
			break;
		case ID::E_Enemy1:
			m_SPawn[ID::E_Enemy1]->SetSPawn();
			break;
		}
	}
}

const bool Respawn::GetResPawn() const
{
	return m_IsResPawn;
}

PlayerSPawn::PlayerSPawn()
{
}

PlayerSPawn::~PlayerSPawn()
{
}

void PlayerSPawn::SetSPawn()
{
	float x = static_cast<float>(myLib::Random::Rand_R(-200, 200));
	Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->Respawn(D3DXVECTOR3(x, 0.0f, -220.0f));
}

EnemySPawn::EnemySPawn()
{
}

EnemySPawn::~EnemySPawn()
{
}

void EnemySPawn::SetSPawn()
{
	float x = static_cast<float>(myLib::Random::Rand_R(-200, 200));
	Engine::Get().GetApplication()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR)->Respawn(D3DXVECTOR3(x, 0.0f, 180.0f));
}
