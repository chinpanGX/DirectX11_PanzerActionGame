/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : �o���đ�

	��]

----------------------------------------------------------------*/
#include "Vehicle.h"
#include "MoveComponent.h"
#include "PanzerPilot.h"
#include "PanzerStateRotation.h"
#include "PanzerStateShot.h"
#include "PanzerStateStay.h"
#include "Engine.h"
#include "Application.h"
#include "Player.h"

#pragma region Rotation_method
float State::Rotation::GetRightDirection(Pawn * pPawn)
{
	auto player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	Math::Vector3 dist = pPawn->GetVehicle().GetBodyTransform().position() - player->GetVehicle().GetBodyTransform().position();
	Math::Vector3 cross = Math::Vector3::Cross(pPawn->GetPilot().GetTransform().GetVector(Transform::Vector::Forward), dist);
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

void State::BodyRotation::Update(Pawn * pPawn, float deltaTime)
{
	FrameCountDown();
	// �E����
	if (m_Random == 0)
	{
		pPawn->GetMoveComponent().RotRight(pPawn->GetVehicle().GetBodyTransform(), deltaTime);
		pPawn->GetPilot().GetMoveComponent().RotRight(pPawn->GetPilot().GetTransform(), deltaTime);
	}
	// ������
	else if(m_Random == 1)
	{
		pPawn->GetMoveComponent().RotLeft(pPawn->GetVehicle().GetBodyTransform(), deltaTime);
		pPawn->GetPilot().GetMoveComponent().RotLeft(pPawn->GetPilot().GetTransform(), deltaTime);
	}
	if (GetFrameZeroFlag() == true)
	{
		pPawn->ChangeState(std::make_unique<State::Stay>());
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

void State::TurretRotation::Update(Pawn * pPawn, float deltaTime)
{
	// �E����
	if (GetRightDirection(pPawn) > 0.0f)
	{
		pPawn->GetMoveComponent().RotRight(pPawn->GetVehicle().GetTurretTransform(), deltaTime);
		pPawn->GetPilot().GetMoveComponent().RotRight(pPawn->GetPilot().GetTransform(), deltaTime);
	}
	// ������
	else
	{
		pPawn->GetMoveComponent().RotLeft(pPawn->GetVehicle().GetTurretTransform(), deltaTime);
		pPawn->GetPilot().GetMoveComponent().RotLeft(pPawn->GetPilot().GetTransform(), deltaTime);
	}
	// �����[�h�����������猂��
	if (pPawn->GetVehicle().GetStatus().GetFinishReload() == true)
	{
		pPawn->ChangeState(std::make_unique<State::Shot>());
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

void State::GunRotation::Update(Pawn * pPawn, float deltaTime)
{
}
#pragma endregion GunRotation���\�b�h