/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : �o���đ�

	��]

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
	// �E����
	if (dir > 0.0f)
	{
		pCpu->moveComponent().RotRight(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// ������
	else
	{
		pCpu->moveComponent().RotLeft(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}

	// -0.5f �`�@0.5f�̊ԂɂȂ�����A�ړ��X�e�[�g��
	if (-0.5f < dir && dir < 0.5f)
	{
		pCpu->ChangeState(std::make_unique<State::Forward>());
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

void State::TurretRotation::Update(Cpu * pCpu, float deltaTime)
{
	float dir = FindTargetDirection(m_Player, pCpu, pCpu->pivot().transform().forward());
	// �E����
	if (dir > 0.0f)
	{
		pCpu->moveComponent().RotRight(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// ������
	else
	{
		pCpu->moveComponent().RotLeft(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}

	// �X�L�����g�����ԂȂ�A�g��
	if (pCpu->vehicle().skill().alreadyUseble())
	{
		pCpu->UseSkill();
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}

	// -0.5f �`�@0.5f�̊�
	if (-0.5f < dir && dir < 0.5f)
	{
		// �����[�h�����������猂��
		if (pCpu->reload().finishReload() == true)
		{
			pCpu->ChangeState(std::make_unique<State::Shot>());
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

void State::GunRotation::Update(Cpu * pCpu, float deltaTime)
{
}
#pragma endregion GunRotation���\�b�h