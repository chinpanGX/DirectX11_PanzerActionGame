/*--------------------------------------------------------------

	[Controller.cpp]
	Author : 出合翔太

	プレイヤーのコントローラ

---------------------------------------------------------------*/
#include "MoveComponent.h"
#include "Pivot.h"
#include "Skill.h"
#include "Vehicle.h"
#include "Pawn.h"
#include "GameCamera.h"
#include "Controller.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Reload.h"

Controller::Controller(Pawn * pPawn, GameCamera * pCamera, Pivot* pPivot) : m_Pawn(pPawn), m_Camera(pCamera), m_Pivot(pPivot)
{
	
}

Controller::~Controller()
{
}

void Controller::ChangeCameraMode(bool Mode)
{
	m_Camera->ChangeCameraMode(Mode);
}

void Controller::MoveForward(float deltaTime)
{
	m_Pawn->GetMoveComponent().MoveForward(m_Pawn->GetVehicle().GetBodyTransform(), deltaTime);
	m_Pivot->Move();
}

void Controller::MoveBackward(float deltaTime)
{
	m_Pawn->GetMoveComponent().MoveBackward(m_Pawn->GetVehicle().GetBodyTransform(), deltaTime);
	m_Pivot->Move();
}

void Controller::RotRight(float deltaTime)
{
	m_Pawn->GetMoveComponent().RotRight(m_Pawn->GetVehicle().GetBodyTransform(), deltaTime);
	m_Pivot->GetMoveComponent().RotRight(m_Pivot->transform(), deltaTime);
}

void Controller::RotLeft(float deltaTime)
{
	m_Pawn->GetMoveComponent().RotLeft(m_Pawn->GetVehicle().GetBodyTransform(), deltaTime);
	m_Pivot->GetMoveComponent().RotLeft(m_Pivot->transform(), deltaTime);
}

void Controller::RotTurretRight(float deltaTime)
{
	m_Pawn->GetMoveComponent().RotRight(m_Pawn->GetVehicle().GetTurretTransform(), deltaTime);
	m_Pivot->GetMoveComponent().RotRight(m_Pivot->transform(), deltaTime);
}

void Controller::RotTurretLeft(float deltaTime)
{
	m_Pawn->GetMoveComponent().RotLeft(m_Pawn->GetVehicle().GetTurretTransform(), deltaTime);
	m_Pivot->GetMoveComponent().RotLeft(m_Pivot->transform(), deltaTime);
}

void Controller::RotMaingunUp(float deltaTime)
{
	m_Pawn->GetMoveComponent().GunUp(m_Pawn->GetVehicle().GetGunTransform(), deltaTime);
	m_Pivot->GetMoveComponent().GunUp(m_Pivot->transform(), deltaTime);
}

void Controller::RotMaingunDown(float deltaTime)
{
	m_Pawn->GetMoveComponent().GunDown(m_Pawn->GetVehicle().GetGunTransform(), deltaTime);
	m_Pivot->GetMoveComponent().GunDown(m_Pivot->transform(), deltaTime);
}

void Controller::Shot()
{
	if (m_Pawn->GetVehicle().GetStatus().GetFinishReload() == true)
	{
		m_Pawn->GetVehicle().Shot(m_Pivot->transform());
		Engine::Get().resource()->AudioPlay("Shot");
		auto effect = Engine::Get().application()->GetScene()->AddGameObject<Reload>(ELayer::LAYER_2D_EFFECT);
		Math::Vector3 offset = m_Pivot->transform().position() + Math::Vector3(0.0f, 3.0f, 0.0f);
		effect->transform().position(offset);
	}
}

void Controller::UseSkill()
{
	m_Pawn->GetVehicle().GetSkill().Enable(m_Pawn);
}
