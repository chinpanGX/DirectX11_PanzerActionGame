/*--------------------------------------------------------------

	[Enemy.cpp]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#include "PanzerState.h"
#include "PanzerContainer.h"
#include "Engine.h"
#include "Application.h"
#include "Pivot.h"
#include "Fps.h"
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "PanzerStateStay.h"
#include "Factory.h"
#include "Pause.h"
#include "Player.h"
#include "Vehicle.h"
#include "Command.h"
#include "MoveComponent.h"
#include "OnComponentEvent.h"
#include "Enemy.h"

Enemy::Enemy() : Pawn(Factory::FVehicle::EType::E_CPU)
{
	Pawn::Create();
	AddComponentEvent<OnComponentEventWallBox>();
}

Enemy::~Enemy()
{
}

void Enemy::Begin()
{
	float rand_x = (float)myLib::Random::Rand_R(-100, 100);
	Pawn::SetStartPosition(this, Math::Vector3(rand_x, 0.0f, 100.0f), Math::Vector3(0.0f, Math::ToRadians(180.0f), 0.0f));
	m_State = std::make_unique<State::Stay>();
}

void Enemy::Update()
{
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
	m_State->Update(this, Fps::Get().deltaTime);
	Pawn::Update();
	OnCollision();
}

void Enemy::Event()
{
	if (CollisionEnter())
	{
		auto player = Engine::Get().application()->GetScene()->GetGameObjects<Player>(ELayer::LAYER_3D_ACTOR);
		for (auto p : player)
		{
			GetVehicle().CalcuateDamege(p);
			ResetCollisionEnter();
		}
	}
	Pawn::CheckZeroHp(this);
}

void Enemy::Draw()
{
	GetVehicle().Draw();
}

void Enemy::ChangeState(std::unique_ptr<PanzerState> State)
{
	m_State = std::move(State);
}

void Enemy::Respawn(const Math::Vector3 & pos)
{
	Pawn::SetStartPosition(this, pos, Math::Vector3(0.0f, Math::ToRadians(180.0f), 0.0f));
	Pawn::RespawnSetMaxHP();
	this->ChangeState(std::make_unique<State::Stay>());
	this->Update();
}

void Enemy::OnCollision()
{
	BeginOverlap(this);
}
