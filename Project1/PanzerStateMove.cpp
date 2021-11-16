/*-----------------------------------------------------------
	
	[State::.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Vehicle.h"
#include "MoveComponent.h"
#include "Enemy.h"
#include "PanzerStateMove.h"
#include "PanzerStateStay.h"
#include "Pivot.h"
#include "Reload.h"
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

void State::Forward::Update(Cpu * pCpu, float deltaTime)
{
	FrameCountDown();
	if (GetFrameZeroFlag() == true)
	{
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}
	pCpu->GetMoveComponent().MoveForward(pCpu->vehicle().bodyTransform(), deltaTime);
	pCpu->pivot().Move();
	// プレイヤーとの当たり判定を取る
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		if (Intersect(pCpu->vehicle().collider(0).GetSphere3(), player->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(pCpu->vehicle().collider(0).GetOBB3(), player->vehicle().collider(0).GetOBB3()))
			{
				pCpu->GetMoveComponent().MoveBackward(pCpu->vehicle().bodyTransform(), deltaTime);
				pCpu->pivot().Move();
				pCpu->ChangeState(std::make_unique<State::Stay>());
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

void State::Backward::Update(Cpu * pCpu, float deltaTime)
{
	FrameCountDown();
	if (GetFrameZeroFlag() == true)
	{
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}
	pCpu->GetMoveComponent().MoveBackward(pCpu->vehicle().bodyTransform(), deltaTime);
	pCpu->pivot().Move();
	// プレイヤーとの当たり判定
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		if (Intersect(pCpu->vehicle().collider(0).GetSphere3(), player->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(pCpu->vehicle().collider(0).GetOBB3(), player->vehicle().collider(0).GetOBB3()))
			{
				pCpu->GetMoveComponent().MoveForward(pCpu->vehicle().bodyTransform(), deltaTime);
				pCpu->pivot().Move();
				pCpu->ChangeState(std::make_unique<State::Stay>());
			}
		}
	}
}

