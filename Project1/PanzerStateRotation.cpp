/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : �o���đ�

	��]

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
	// �E����
	if (dir > 0.0f)
	{
		Enemy->GetMoveComponent().RotRight(Enemy->GetVehicle().GetBodyTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotRight(Enemy->GetPivot().GetTransform(), DeltaTime);
	}
	// ������
	else
	{
		Enemy->GetMoveComponent().RotLeft(Enemy->GetVehicle().GetBodyTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotLeft(Enemy->GetPivot().GetTransform(), DeltaTime);
	}

	// -0.5f �`�@0.5f�̊ԂɂȂ�����A�ړ��X�e�[�g��
	if (-0.5f < dir && dir < 0.5f)
	{
		Enemy->ChangeState(std::make_unique<State::Forward>());
	}	
}
#pragma endregion BodyRotation���\�b�h

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
	// �E����
	if (dir > 0.0f)
	{
		Enemy->GetMoveComponent().RotRight(Enemy->GetVehicle().GetTurretTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotRight(Enemy->GetPivot().GetTransform(), DeltaTime);
	}
	// ������
	else
	{
		Enemy->GetMoveComponent().RotLeft(Enemy->GetVehicle().GetTurretTransform(), DeltaTime);
		Enemy->GetPivot().GetMoveComponent().RotLeft(Enemy->GetPivot().GetTransform(), DeltaTime);
	}

	// �X�L�����g�����ԂȂ�A�g��
	if (Enemy->GetVehicle().GetSkill().GetAlreadyUseble())
	{
		Enemy->UseSkill();
		Enemy->ChangeState(std::make_unique<State::Stay>());
	}

	// -0.5f �`�@0.5f�̊�
	if (-0.5f < dir && dir < 0.5f)
	{
		// �����[�h�����������猂��
		if (Enemy->GetReload().GetFinishReload() == true)
		{
			Enemy->ChangeState(std::make_unique<State::Shot>());
		}
	}
}

#pragma endregion TurretRotation���\�b�h

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
#pragma endregion GunRotation���\�b�h