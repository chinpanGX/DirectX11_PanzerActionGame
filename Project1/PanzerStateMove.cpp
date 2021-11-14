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

void State::Forward::Update(Pawn * pPawn, float deltaTime)
{
	FrameCountDown();
	if (GetFrameZeroFlag() == true)
	{
		pPawn->ChangeState(std::make_unique<State::Stay>());
	}
	pPawn->GetMoveComponent().MoveForward(pPawn->vehicle().bodyTransform(), deltaTime);
	pPawn->pivot().Move();
	// プレイヤーとの当たり判定を取る
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		if (Intersect(pPawn->vehicle().collider(0).GetSphere3(), player->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(pPawn->vehicle().collider(0).GetOBB3(), player->vehicle().collider(0).GetOBB3()))
			{
				pPawn->GetMoveComponent().MoveBackward(pPawn->vehicle().bodyTransform(), deltaTime);
				pPawn->pivot().Move();
				pPawn->ChangeState(std::make_unique<State::Stay>());
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

void State::Backward::Update(Pawn * pPawn, float deltaTime)
{
	FrameCountDown();
	if (GetFrameZeroFlag() == true)
	{
		pPawn->ChangeState(std::make_unique<State::Stay>());
	}
	pPawn->GetMoveComponent().MoveBackward(pPawn->vehicle().bodyTransform(), deltaTime);
	pPawn->pivot().Move();
	// プレイヤーとの当たり判定
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		if (Intersect(pPawn->vehicle().collider(0).GetSphere3(), player->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(pPawn->vehicle().collider(0).GetOBB3(), player->vehicle().collider(0).GetOBB3()))
			{
				pPawn->GetMoveComponent().MoveForward(pPawn->vehicle().bodyTransform(), deltaTime);
				pPawn->pivot().Move();
				pPawn->ChangeState(std::make_unique<State::Stay>());
			}
		}
	}
}

