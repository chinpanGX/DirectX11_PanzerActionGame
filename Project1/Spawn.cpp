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
#include "Spawn.h"

Respawn::Respawn()
{
	m_Spawn.emplace_back(std::make_unique<PlayerSpawn>());
	m_Spawn.emplace_back(std::make_unique<EnemySpawn>());
}

Respawn::~Respawn()
{
}

void Respawn::Begin()
{
}

void Respawn::Update(GameManager * manager, Pawn * pawn, int32_t Type)
{
	if (!manager->GetGameEnd()) // falseならゲーム終了ではないので、リスポーンする
	{
		switch (Type)
		{
		case ID::E_Player:
			m_Spawn[ID::E_Player]->SetSpawn();
			break;
		case ID::E_Enemy1:
			m_Spawn[ID::E_Enemy1]->SetSpawn();
			break;
		}
	}
}

const bool Respawn::GetRespawn() const
{
	return m_IsRespawn;
}

PlayerSpawn::PlayerSpawn()
{
}

PlayerSpawn::~PlayerSpawn()
{
}

void PlayerSpawn::SetSpawn()
{
	float x = static_cast<float>(myLib::Random::Rand_R(-200, 200));
	Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->Respawn(D3DXVECTOR3(x, 0.0f, -220.0f));
}

EnemySpawn::EnemySpawn()
{
}

EnemySpawn::~EnemySpawn()
{
}

void EnemySpawn::SetSpawn()
{
	float x = static_cast<float>(myLib::Random::Rand_R(-200, 200));
	Engine::Get().application()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR)->Respawn(D3DXVECTOR3(x, 0.0f, 180.0f));
}
