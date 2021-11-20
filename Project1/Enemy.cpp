/*--------------------------------------------------------------

	[Enemy.cpp]
	Author : èoçá„ƒëæ

---------------------------------------------------------------*/
#include "PanzerState.h"
#include "PanzerContainer.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
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
#include "GameCamera.h"
#include "Enemy.h"

Enemy::Enemy() : Cpu(), m_Resource(*Engine::Get().resource())
{
	Pawn::Create();	
}

Enemy::~Enemy()
{
}

void Enemy::Begin()
{
	float rand_x = (float)myLib::Random::Rand_R(-100, 100);
	Pawn::SetStartPosition(this, D3DXVECTOR3(rand_x, 0.0f, 70.0f), D3DXVECTOR3(0.0f, Math::ToRadians(180.0f), 0.0f));
	m_CpuRule = std::make_unique<CpuStateRule>();
	m_State = std::make_unique<State::Stay>();
}

void Enemy::Update()
{
	if(Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->NowPausing()) { return; }	
	m_CpuRule->Update(this);
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
			vehicle().CalcuateDamege(p);
			ResetCollisionEnter();
		}
	}
	Pawn::CheckZeroHp(this);
}

void Enemy::Draw()
{
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	if (camera->NotDrawObject(pivot().transform().position(), vehicle().collider(0).GetSphere3().GetRadius()))
	{
		//OutputDebugString("Enemy NoRendering\n");
		return;
	}
	m_Resource.SetShader("PixelLighting");
	vehicle().Draw();
}

void Enemy::ChangeState(std::unique_ptr<PanzerState> State)
{
	m_State = std::move(State);
}

void Enemy::Respawn(const D3DXVECTOR3 & pos)
{
	Pawn::SetStartPosition(this, pos, D3DXVECTOR3(0.0f, Math::ToRadians(180.0f), 0.0f));
	Pawn::RespawnSetMaxHP();
	this->ChangeState(std::make_unique<State::Stay>());
	this->Update();
}

void Enemy::OnCollision()
{
	BeginOverlap(this);
}
