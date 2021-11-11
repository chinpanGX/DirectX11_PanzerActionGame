/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : 出合翔太

	回転

----------------------------------------------------------------*/
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
float State::Rotation::GetRightDirection(Pawn * pPawn)
{
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	Math::Vector3 dist = pPawn->vehicle().GetBodyTransform().position() - player->vehicle().GetBodyTransform().position();
	Math::Vector3 cross = Math::Vector3::Cross(pPawn->pivot().transform().GetVector(Transform::Vector::Forward), dist);
	float t = cross.x - cross.y - cross.z;
	return t;
}
#pragma endregion Rotationメソッド

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
	// 右旋回
	if (m_Random == 0)
	{
		pPawn->GetMoveComponent().RotRight(pPawn->vehicle().GetBodyTransform(), deltaTime);
		pPawn->pivot().GetMoveComponent().RotRight(pPawn->pivot().transform(), deltaTime);
	}
	// 左旋回
	else if(m_Random == 1)
	{
		pPawn->GetMoveComponent().RotLeft(pPawn->vehicle().GetBodyTransform(), deltaTime);
		pPawn->pivot().GetMoveComponent().RotLeft(pPawn->pivot().transform(), deltaTime);
	}
	if (GetFrameZeroFlag() == true)
	{
		pPawn->ChangeState(std::make_unique<State::Stay>());
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

void State::TurretRotation::Update(Pawn * pPawn, float deltaTime)
{
	// 右旋回
	if (GetRightDirection(pPawn) > 0.0f)
	{
		pPawn->GetMoveComponent().RotRight(pPawn->vehicle().GetTurretTransform(), deltaTime);
		pPawn->pivot().GetMoveComponent().RotRight(pPawn->pivot().transform(), deltaTime);
	}
	// 左旋回
	else
	{
		pPawn->GetMoveComponent().RotLeft(pPawn->vehicle().GetTurretTransform(), deltaTime);
		pPawn->pivot().GetMoveComponent().RotLeft(pPawn->pivot().transform(), deltaTime);
	}
	// リロードが完了したら撃つ
	if (pPawn->vehicle().GetStatus().GetFinishReload() == true)
	{
		pPawn->ChangeState(std::make_unique<State::Shot>());
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

void State::GunRotation::Update(Pawn * pPawn, float deltaTime)
{
}
#pragma endregion GunRotationメソッド