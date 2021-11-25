/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : 出合翔太

	回転

----------------------------------------------------------------*/
#include "Cpu.h"
#include "Vehicle.h"
#include "Skill.h"
#include "Reload.h"
#include "MoveComponent.h"
#include "Pivot.h"
#include "PanzerStateRotation.h"
#include "PanzerStateShot.h"
#include "PanzerStateStay.h"
#include "PanzerStateMove.h"
#include "Engine.h"
#include "Application.h"
#include "Player.h"

#pragma region BodyRotation_method
State::BodyRotation::BodyRotation()
{
	
}

State::BodyRotation::~BodyRotation()
{
}

void State::BodyRotation::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::BodyRotation::Update(Cpu * pCpu, float deltaTime)
{
	float dir = FindTargetDirection(m_Player, pCpu, pCpu->vehicle().bodyTransform().forward());
	// 右旋回
	if (dir > 0.0f)
	{
		pCpu->moveComponent().RotRight(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// 左旋回
	else
	{
		pCpu->moveComponent().RotLeft(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}

	// -0.5f ～　0.5fの間になったら、移動ステートへ
	if (-0.5f < dir && dir < 0.5f)
	{
		pCpu->ChangeState(std::make_unique<State::Forward>());
	}	
}
#pragma endregion BodyRotationメソッド

#pragma region TurretRotation_method
State::TurretRotation::TurretRotation()
{
	
}

State::TurretRotation::~TurretRotation()
{
}

void State::TurretRotation::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::TurretRotation::Update(Cpu * pCpu, float deltaTime)
{
	float dir = FindTargetDirection(m_Player, pCpu, pCpu->pivot().transform().forward());
	// 右旋回
	if (dir > 0.0f)
	{
		pCpu->moveComponent().RotRight(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// 左旋回
	else
	{
		pCpu->moveComponent().RotLeft(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}

	// スキルが使える状態なら、使う
	if (pCpu->vehicle().skill().alreadyUseble())
	{
		pCpu->UseSkill();
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}

	// -0.5f ～　0.5fの間
	if (-0.5f < dir && dir < 0.5f)
	{
		// リロードが完了したら撃つ
		if (pCpu->reload().finishReload() == true)
		{
			pCpu->ChangeState(std::make_unique<State::Shot>());
		}
	}
}

#pragma endregion TurretRotationメソッド

#pragma region GunRotation_method
State::GunRotation::GunRotation()
{
}

State::GunRotation::~GunRotation()
{
}

void State::GunRotation::Begin(Player * pPlayer)
{
}

void State::GunRotation::Update(Cpu * pCpu, float deltaTime)
{
}
#pragma endregion GunRotationメソッド