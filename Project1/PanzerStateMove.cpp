/*-----------------------------------------------------------
	
	[State::.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Vehicle.h"
#include "MoveComponent.h"
#include "Enemy.h"
#include "PanzerStateMove.h"
#include "PanzerStateRotation.h"
#include "PanzerStateStay.h"
#include "Pivot.h"
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "Engine.h"
#include "Application.h"
#include "Player.h"

State::Forward::Forward()
{
	
}


State::Forward::~Forward()
{
}

void State::Forward::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::Forward::Update(Enemy* pEnemy, float deltaTime)
{
	{
		pEnemy->GetMoveComponent().MoveForward(pEnemy->GetVehicle().GetBodyTransform(), deltaTime);
		pEnemy->GetPivot().Move();
	}
	
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		// プレイヤーとCPUの距離を求める
		D3DXVECTOR3 playerPosition = player->GetVehicle().GetBodyTransform().GetPosition();
		D3DXVECTOR3 cpuPosition = pEnemy->GetVehicle().GetBodyTransform().GetPosition();
		D3DXVECTOR3 tmp = cpuPosition - playerPosition;
		float dist = Math::Abs(D3DXVec3Length(&tmp));
		// 距離が近くなったら,ステートを変える
		if (dist < 70.0f)
		{
			float dir = FindTargetDirection(player, pEnemy, pEnemy->GetVehicle().GetBodyTransform().forward());
			if (-5.0f > dir || dir > 5.0f)
			{
				pEnemy->ChangeState(std::make_unique<State::Stay>());
			}
		}

		if (Intersect(pEnemy->GetVehicle().GetCollider(0).GetSphere3(), player->GetVehicle().GetCollider(0).GetSphere3()))
		{
			if (Intersect(pEnemy->GetVehicle().GetCollider(0).GetOBB3(), player->GetVehicle().GetCollider(0).GetOBB3()))
			{
				pEnemy->GetMoveComponent().MoveBackward(pEnemy->GetVehicle().GetBodyTransform(), deltaTime);
				pEnemy->GetPivot().Move();
				pEnemy->ChangeState(std::make_unique<State::Backward>());
			}
		}
	}	
}

State::Backward::Backward()
{
}

State::Backward::~Backward()
{
}

void State::Backward::Begin(Player * pPlayer)
{
}

void State::Backward::Update(Enemy* pEnemy, float deltaTime)
{
	FrameCountDown();
	if (GetFrameZeroFlag() == true)
	{
		pEnemy->ChangeState(std::make_unique<State::Stay>());
	}
	pEnemy->GetMoveComponent().MoveBackward(pEnemy->GetVehicle().GetBodyTransform(), deltaTime);
	pEnemy->GetPivot().Move();
	// プレイヤーとの当たり判定
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		if (Intersect(pEnemy->GetVehicle().GetCollider(0).GetSphere3(), player->GetVehicle().GetCollider(0).GetSphere3()))
		{
			if (Intersect(pEnemy->GetVehicle().GetCollider(0).GetOBB3(), player->GetVehicle().GetCollider(0).GetOBB3()))
			{
				pEnemy->GetMoveComponent().MoveForward(pEnemy->GetVehicle().GetBodyTransform(), deltaTime);
				pEnemy->GetPivot().Move();
				pEnemy->ChangeState(std::make_unique<State::Stay>());
			}
		}
	}
}

