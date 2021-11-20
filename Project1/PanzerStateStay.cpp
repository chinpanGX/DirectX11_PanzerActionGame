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
	switch(pCpu->cpuRule().behavior())
	{
	// 射程範囲ない
	case 0:
		pCpu->ChangeState(std::make_unique<State::TurretRotation>());
		break;
	// 索敵範囲内
	case 1:
		pCpu->ChangeState(std::make_unique<State::BodyRotation>());
		break;	
	case 2:
		break;
	}

}
