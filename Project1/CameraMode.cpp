/*-----------------------------------------------------------

	[CameraMode.cpp]
	Author : �o���đ�

	FPS�J�����ATPS�J�����̏�Ԃ�؂�ւ���

-------------------------------------------------------------*/
#include "GameCamera.h"
#include "CameraMode.h"
#include "Engine.h"
#include "Application.h"
#include "PanzerPilot.h"

#pragma region TpsCameraMode_method
TpsCameraMode::TpsCameraMode() {}

TpsCameraMode::~TpsCameraMode() {}

void TpsCameraMode::Update(GameCamera * Camera, PanzerPilot* Panzer)
{
	// ���[�h�`�F���W
	if (Camera->GetChageMode() == true)
	{
		Camera->ChangeMode(std::make_unique<FpsCameraMode>());
	}
	
	Math::Vector3& CameraPosition = Camera->GetTransform().position();
	auto offset = Math::Vector3(0.0f, 5.0f, 0.0f);
	CameraPosition = Panzer->GetTransform().position() + (Panzer->GetTransform().GetVector(Transform::Vector::Backward) * Panzer->GetTpsOffset()) + offset;
	Math::Vector3 target = Panzer->GetTransform().position() + (Panzer->GetTransform().GetVector(Transform::Vector::Forward) * Panzer->GetTargetOffset());
	Camera->SetTarget(target);
}
#pragma endregion TpsCameraMode�̃��\�b�h

#pragma region FpsCameraMode_method
FpsCameraMode::FpsCameraMode() {}

FpsCameraMode::~FpsCameraMode() {}

void FpsCameraMode::Update(GameCamera * Camera, PanzerPilot* Panzer)
{
	if (Camera->GetChageMode() == false)
	{
		Camera->ChangeMode(std::make_unique<TpsCameraMode>());
	}

	Math::Vector3& CameraPosition = Camera->GetTransform().position();
	CameraPosition = Panzer->GetTransform().position() + (Panzer->GetTransform().GetVector(Transform::Vector::Forward) * Panzer->GetFpsOffset());
	Math::Vector3 target = Panzer->GetTransform().position() + (Panzer->GetTransform().GetVector(Transform::Vector::Forward) * Panzer->GetTargetOffset());

	Camera->SetTarget(target);
}
#pragma endregion TpsCameraMode�̃��\�b�h
