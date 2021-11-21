/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : �o���đ�

	��]

----------------------------------------------------------------*/
#include "Cpu.h"
#include "Vehicle.h"
#include "MoveComponent.h"
#include "Pivot.h"
#include "PanzerStateRotation.h"
#include "PanzerStateShot.h"
#include "PanzerStateStay.h"
#include "PanzerStateMove.h"
#include "Engine.h"
#include "Application.h"
#include "Player.h"
#include <cfenv>


#pragma region BodyRotation_method
State::BodyRotation::BodyRotation()
{
	
}

State::BodyRotation::~BodyRotation()
{
}

void State::BodyRotation::Update(Cpu * pCpu, float deltaTime)
{
	float dir = GetDirection(pCpu);

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

float State::BodyRotation::GetDirection(Cpu * pCpu)
{
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);	
	// �v���C���[�ƃG�l�~�[�̋����𑪂�
	D3DXVECTOR3 dist = pCpu->vehicle().bodyTransform().position() - player->vehicle().bodyTransform().position();
	D3DXVECTOR3 cross;
	// body�̑O�x�N�g����dist�̊O�ς����߂�
	D3DXVec3Cross(&cross, &pCpu->vehicle().bodyTransform().forward(), &dist);
	float t = cross.x - cross.y - cross.z;
	// t > 0.0f�Ȃ�E�ɂ���
	return t;
}
#pragma endregion BodyRotation���\�b�h

#pragma region TurretRotation_method
State::TurretRotation::TurretRotation()
{
}

State::TurretRotation::~TurretRotation()
{
}

void State::TurretRotation::Update(Cpu * pCpu, float deltaTime)
{
	// �E����
	if (GetDirection(pCpu) > 0.0f)
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
	// �����[�h�����������猂��
	if (pCpu->vehicle().status().finishReload() == true)
	{
		pCpu->ChangeState(std::make_unique<State::Shot>());
	}
}
float State::TurretRotation::GetDirection(Cpu * pCpu)
{
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	// �v���C���[�ƃG�l�~�[�̋����𑪂�
	D3DXVECTOR3 dist = pCpu->vehicle().bodyTransform().position() - player->vehicle().bodyTransform().position();
	D3DXVECTOR3 cross;
	// pivot�̑O�x�N�g����dist�̊O�ς����߂�
	D3DXVec3Cross(&cross, &pCpu->pivot().transform().forward(), &dist);
	float t = cross.x - cross.y - cross.z;
	// t > 0.0f�Ȃ�E�ɂ���
	return t;	
}
#pragma endregion TurretRotation���\�b�h

#pragma region GunRotation_method
State::GunRotation::GunRotation()
{
}

State::GunRotation::~GunRotation()
{
}

void State::GunRotation::Update(Cpu * pCpu, float deltaTime)
{
}
#pragma endregion GunRotation���\�b�h