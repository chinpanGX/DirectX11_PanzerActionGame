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
	FrameCountDown();
	if (GetFrameZeroFlag() == true)
	{
		pEnemy->ChangeState(std::make_unique<State::Stay>());
	}
	//for (int i = 0; i < 10; i++)
	{
		pEnemy->moveComponent().MoveForward(pEnemy->vehicle().bodyTransform(), deltaTime);
		pEnemy->pivot().Move();
	}
	
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		// プレイヤーとCPUの距離を求める
		D3DXVECTOR3 playerPosition = player->vehicle().bodyTransform().position();
		D3DXVECTOR3 cpuPosition = pEnemy->vehicle().bodyTransform().position();
		D3DXVECTOR3 tmp = cpuPosition - playerPosition;
		float dist = D3DXVec3Length(&tmp);
		// 距離が近くなったら,ステートを変える
		if (dist < 100.0f)
		{
			float dir = FindTargetDirection(player, pEnemy, pEnemy->vehicle().bodyTransform().forward());
			if (-5.0f > dir || dir > 5.0f)
			{
				pEnemy->ChangeState(std::make_unique<State::Stay>());
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
	pEnemy->moveComponent().MoveBackward(pEnemy->vehicle().bodyTransform(), deltaTime);
	pEnemy->pivot().Move();
	// プレイヤーとの当たり判定
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		if (Intersect(pEnemy->vehicle().collider(0).GetSphere3(), player->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(pEnemy->vehicle().collider(0).GetOBB3(), player->vehicle().collider(0).GetOBB3()))
			{
				pEnemy->moveComponent().MoveForward(pEnemy->vehicle().bodyTransform(), deltaTime);
				pEnemy->pivot().Move();
				pEnemy->ChangeState(std::make_unique<State::Stay>());
			}
		}
	}
}

