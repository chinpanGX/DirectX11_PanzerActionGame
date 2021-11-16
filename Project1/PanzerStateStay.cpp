/*------------------------------------------------------------

	[PanzerState.cpp]
	Author : 出合翔太

	何もしないステート

--------------------------------------------------------------*/
#include "Enemy.h"
#include "Cpu.h"
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

void State::Stay::Update(Cpu * pCpu, float deltaTime)
{
	auto i = myLib::Random::Rand_R(0, 5);
	switch (i)
	{
	case 0:
		pCpu->ChangeState(std::make_unique<State::Forward>());
		break;
	case 1:
		pCpu->ChangeState(std::make_unique<State::Backward>());
		break;
	case 2:
		pCpu->ChangeState(std::make_unique<State::TurretRotation>());
		break;
	case 3:
	case 4:
		pCpu->ChangeState(std::make_unique<State::BodyRotation>());
	}
}
