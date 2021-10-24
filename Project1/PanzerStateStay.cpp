/*------------------------------------------------------------

	[PanzerState.cpp]
	Author : 出合翔太

	何もしないステート

--------------------------------------------------------------*/
#include "Enemy.h"
#include "Pawn.h"
#include "Vehicle.h"
#include "PanzerStateStay.h"
#include "PanzerStateMove.h"
#include "PanzerStateShot.h"
#include "PanzerStateRotation.h"

State::Stay::Stay()
{
}

State::Stay::~Stay()
{
}

void State::Stay::Update(Pawn * pPawn, float deltaTime)
{
	auto i = myLib::Random::Rand_R(0, 5);
	switch (i)
	{
	case 0:
		pPawn->ChangeState(std::make_unique<State::Forward>());
		break;
	case 1:
		pPawn->ChangeState(std::make_unique<State::Backward>());
		break;
	case 2:
		pPawn->ChangeState(std::make_unique<State::TurretRotation>());
		break;
	case 3:
	case 4:
		pPawn->ChangeState(std::make_unique<State::BodyRotation>());
	}
}
