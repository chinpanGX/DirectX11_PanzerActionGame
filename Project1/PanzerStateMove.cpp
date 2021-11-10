/*-----------------------------------------------------------
	
	[State::.cpp]
	Author : o‡ãÄ‘¾

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
	pPawn->GetMoveComponent().MoveForward(pPawn->GetVehicle().GetBodyTransform(), deltaTime);
	pPawn->GetPilot().Move();
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (Intersect(pPawn->GetVehicle().GetBoxComponent(0).GetSphere3(), player->GetVehicle().GetBoxComponent(0).GetSphere3()))
	{
		pPawn->GetMoveComponent().MoveBackward(pPawn->GetVehicle().GetBodyTransform(), deltaTime);
		pPawn->GetPilot().Move();
		pPawn->ChangeState(std::make_unique<State::Stay>());
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
	pPawn->GetMoveComponent().MoveBackward(pPawn->GetVehicle().GetBodyTransform(), deltaTime);
	pPawn->GetPilot().Move();
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (Intersect(pPawn->GetVehicle().GetBoxComponent(0).GetSphere3(), player->GetVehicle().GetBoxComponent(0).GetSphere3()))
	{
		pPawn->GetMoveComponent().MoveForward(pPawn->GetVehicle().GetBodyTransform(), deltaTime);
		pPawn->GetPilot().Move();
		pPawn->ChangeState(std::make_unique<State::Stay>());
	}
}

