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

void State::BodyRotation::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::BodyRotation::Update(Enemy* pEnemy, float deltaTime)
{
	float dir = FindTargetDirection(m_Player, pEnemy, pEnemy->vehicle().bodyTransform().forward());
	// �E����
	if (dir > 0.0f)
	{
		pEnemy->moveComponent().RotRight(pEnemy->vehicle().bodyTransform(), deltaTime);
		pEnemy->pivot().moveComponent().RotRight(pEnemy->pivot().transform(), deltaTime);
	}
	// ������
	else
	{
		pEnemy->moveComponent().RotLeft(pEnemy->vehicle().bodyTransform(), deltaTime);
		pEnemy->pivot().moveComponent().RotLeft(pEnemy->pivot().transform(), deltaTime);
	}

	// -0.5f �`�@0.5f�̊ԂɂȂ�����A�ړ��X�e�[�g��
	if (-0.5f < dir && dir < 0.5f)
	{
		pEnemy->ChangeState(std::make_unique<State::Forward>());
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

void State::TurretRotation::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::TurretRotation::Update(Enemy* pEnemy, float deltaTime)
{
	float dir = FindTargetDirection(m_Player, pEnemy, pEnemy->pivot().transform().forward());
	// �E����
	if (dir > 0.0f)
	{
		pEnemy->moveComponent().RotRight(pEnemy->vehicle().turretTransform(), deltaTime);
		pEnemy->pivot().moveComponent().RotRight(pEnemy->pivot().transform(), deltaTime);
	}
	// ������
	else
	{
		pEnemy->moveComponent().RotLeft(pEnemy->vehicle().turretTransform(), deltaTime);
		pEnemy->pivot().moveComponent().RotLeft(pEnemy->pivot().transform(), deltaTime);
	}

	// �X�L�����g�����ԂȂ�A�g��
	if (pEnemy->vehicle().skill().alreadyUseble())
	{
		pEnemy->UseSkill();
		pEnemy->ChangeState(std::make_unique<State::Stay>());
	}

	// -0.5f �`�@0.5f�̊�
	if (-0.5f < dir && dir < 0.5f)
	{
		// �����[�h�����������猂��
		if (pEnemy->reload().finishReload() == true)
		{
			pEnemy->ChangeState(std::make_unique<State::Shot>());
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

void State::GunRotation::Begin(Player * pPlayer)
{
}

void State::GunRotation::Update(Enemy* pEnemy, float deltaTime)
{
}
#pragma endregion GunRotation���\�b�h