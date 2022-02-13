/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : 出合翔太

	回転

----------------------------------------------------------------*/
#include "Enemy.h"
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

void State::BodyRotation::Update(Enemy* pEnemy, float deltaTime)
{
	float dir = FindTargetDirection(m_Player, pEnemy, pEnemy->GetVehicle().GetBodyTransform().forward());
	// 右旋回
	if (dir > 0.0f)
	{
		pEnemy->GetMoveComponent().RotRight(pEnemy->GetVehicle().GetBodyTransform(), deltaTime);
		pEnemy->GetPivot().GetMoveComponent().RotRight(pEnemy->GetPivot().GetTransform(), deltaTime);
	}
	// 左旋回
	else
	{
		pEnemy->GetMoveComponent().RotLeft(pEnemy->GetVehicle().GetBodyTransform(), deltaTime);
		pEnemy->GetPivot().GetMoveComponent().RotLeft(pEnemy->GetPivot().GetTransform(), deltaTime);
	}

	// -0.5f ～　0.5fの間になったら、移動ステートへ
	if (-0.5f < dir && dir < 0.5f)
	{
		pEnemy->ChangeState(std::make_unique<State::Forward>());
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

void State::TurretRotation::Update(Enemy* pEnemy, float deltaTime)
{
	float dir = FindTargetDirection(m_Player, pEnemy, pEnemy->GetPivot().GetTransform().forward());
	// 右旋回
	if (dir > 0.0f)
	{
		pEnemy->GetMoveComponent().RotRight(pEnemy->GetVehicle().GetTurretTransform(), deltaTime);
		pEnemy->GetPivot().GetMoveComponent().RotRight(pEnemy->GetPivot().GetTransform(), deltaTime);
	}
	// 左旋回
	else
	{
		pEnemy->GetMoveComponent().RotLeft(pEnemy->GetVehicle().GetTurretTransform(), deltaTime);
		pEnemy->GetPivot().GetMoveComponent().RotLeft(pEnemy->GetPivot().GetTransform(), deltaTime);
	}

	// スキルが使える状態なら、使う
	if (pEnemy->GetVehicle().GetSkill().alreadyUseble())
	{
		pEnemy->UseSkill();
		pEnemy->ChangeState(std::make_unique<State::Stay>());
	}

	// -0.5f ～　0.5fの間
	if (-0.5f < dir && dir < 0.5f)
	{
		// リロードが完了したら撃つ
		if (pEnemy->GetReload().finishReload() == true)
		{
			pEnemy->ChangeState(std::make_unique<State::Shot>());
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

void State::GunRotation::Update(Enemy* pEnemy, float deltaTime)
{
}
#pragma endregion GunRotationメソッド