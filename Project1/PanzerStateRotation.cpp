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
#include "Engine.h"
#include "Application.h"
#include "Player.h"

#pragma region Rotation_method
float State::Rotation::GetRightDirection(Cpu * pCpu)
{
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	D3DXVECTOR3 dist = pCpu->vehicle().bodyTransform().position() - player->vehicle().bodyTransform().position();
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &pCpu->pivot().transform().forward(), &dist);
	float t = cross.x - cross.y - cross.z;
	return t;
}
#pragma endregion Rotation���\�b�h

#pragma region BodyRotation_method
State::BodyRotation::BodyRotation()
{
	m_Random = myLib::Random::Rand_R(0, 2);
}

State::BodyRotation::~BodyRotation()
{
}

void State::BodyRotation::Update(Cpu * pCpu, float deltaTime)
{
	FrameCountDown();
	// �E����
	if (m_Random == 0)
	{
		pCpu->GetMoveComponent().RotRight(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().GetMoveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// ������
	else if(m_Random == 1)
	{
		pCpu->GetMoveComponent().RotLeft(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().GetMoveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}
	if (GetFrameZeroFlag() == true)
	{
		pCpu->ChangeState(std::make_unique<State::Stay>());
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

void State::TurretRotation::Update(Cpu * pCpu, float deltaTime)
{
	// �E����
	if (GetRightDirection(pCpu) > 0.0f)
	{
		pCpu->GetMoveComponent().RotRight(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().GetMoveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// ������
	else
	{
		pCpu->GetMoveComponent().RotLeft(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().GetMoveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}
	// �����[�h�����������猂��
	if (pCpu->vehicle().GetStatus().GetFinishReload() == true)
	{
		pCpu->ChangeState(std::make_unique<State::Shot>());
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

void State::GunRotation::Update(Cpu * pCpu, float deltaTime)
{
}
#pragma endregion GunRotation���\�b�h