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

void State::BodyRotation::Begin(Player * Player)
{
	m_Player = Player;
}

void State::BodyRotation::Update(Enemy* Enemy, float DeltaTime)
{
	float dir = FindTargetDirection(m_Player, Enemy, Enemy->GetVehicle().GetBodyTransform().forward());
	// 右旋回
	if (dir > 0.0f)
	{
		Enemy->GetMoveComponent().RotRight(Enemy->GetVehicle().GetBodyTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotRight(Enemy->GetPivot().GetTransform(), DeltaTime);
	}
	// 左旋回
	else
	{
		Enemy->GetMoveComponent().RotLeft(Enemy->GetVehicle().GetBodyTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotLeft(Enemy->GetPivot().GetTransform(), DeltaTime);
	}

	// -0.5f ～　0.5fの間になったら、移動ステートへ
	if (-0.5f < dir && dir < 0.5f)
	{
		Enemy->ChangeState(std::make_unique<State::Forward>());
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

void State::TurretRotation::Begin(Player * Player)
{
	m_Player = Player;
}

void State::TurretRotation::Update(Enemy* Enemy, float DeltaTime)
{
	float dir = FindTargetDirection(m_Player, Enemy, Enemy->GetPivot().GetTransform().forward());
	// 右旋回
	if (dir > 0.0f)
	{
		Enemy->GetMoveComponent().RotRight(Enemy->GetVehicle().GetTurretTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotRight(Enemy->GetPivot().GetTransform(), DeltaTime);
	}
	// 左旋回
	else
	{
		Enemy->GetMoveComponent().RotLeft(Enemy->GetVehicle().GetTurretTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotLeft(Enemy->GetPivot().GetTransform(), DeltaTime);
	}

	// スキルが使える状態なら、使う
	if (Enemy->GetVehicle().GetSkill().GetAlreadyUseble())
	{
		Enemy->UseSkill();
		Enemy->ChangeState(std::make_unique<State::Stay>());
	}

	// -0.5f ～　0.5fの間
	if (-0.5f < dir && dir < 0.5f)
	{
		// リロードが完了したら撃つ
		if (Enemy->GetReload().GetFinishReload() == true)
		{
			Enemy->ChangeState(std::make_unique<State::Shot>());
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

void State::GunRotation::Begin(Player * Player)
{
}

void State::GunRotation::Update(Enemy* Enemy, float DeltaTime)
{
}
#pragma endregion GunRotationメソッド