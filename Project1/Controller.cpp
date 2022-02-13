/*--------------------------------------------------------------

	[Controller.cpp]
	Author : 出合翔太

	プレイヤーのコントローラ

---------------------------------------------------------------*/
#include "MoveComponent.h"
#include "Pivot.h"
#include "Skill.h"
#include "Vehicle.h"
#include "Player.h"
#include "GameCamera.h"
#include "Controller.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "PlayerUi.h"

Controller::Controller(Player * Player, GameCamera * Camera, Pivot* Pivot) : m_Player(Player), m_Camera(Camera), m_Pivot(Pivot)
{
	
}

Controller::~Controller()
{
}

void Controller::FpsCameraMode(bool FpsMode)
{
	m_Camera->EnableFpsMode(FpsMode);
}

void Controller::MoveForward(float DeltaTime)
{
	m_Player->GetMoveComponent().MoveForward(m_Player->GetVehicle().GetBodyTransform(), DeltaTime);
	m_Pivot->Move();
}

void Controller::MoveBackward(float DeltaTime)
{
	m_Player->GetMoveComponent().MoveBackward(m_Player->GetVehicle().GetBodyTransform(), DeltaTime);
	m_Pivot->Move();
}

void Controller::RotRight(float DeltaTime)
{
	m_Player->GetMoveComponent().RotRight(m_Player->GetVehicle().GetBodyTransform(), DeltaTime);
	m_Pivot->GetMoveComponent().RotRight(m_Pivot->GetTransform(), DeltaTime);
}

void Controller::RotLeft(float DeltaTime)
{
	m_Player->GetMoveComponent().RotLeft(m_Player->GetVehicle().GetBodyTransform(), DeltaTime);
	m_Pivot->GetMoveComponent().RotLeft(m_Pivot->GetTransform(), DeltaTime);
}

void Controller::RotTurretRight(float DeltaTime)
{
	m_Player->GetMoveComponent().RotRight(m_Player->GetVehicle().GetTurretTransform(), DeltaTime);
	m_Pivot->GetMoveComponent().RotRight(m_Pivot->GetTransform(), DeltaTime);
}

void Controller::RotTurretLeft(float DeltaTime)
{
	m_Player->GetMoveComponent().RotLeft(m_Player->GetVehicle().GetTurretTransform(), DeltaTime);
	m_Pivot->GetMoveComponent().RotLeft(m_Pivot->GetTransform(), DeltaTime);
}

void Controller::RotMaingunUp(float DeltaTime)
{
	m_Player->GetMoveComponent().GunUp(m_Player->GetVehicle().GetGunTransform(), DeltaTime);
	m_Pivot->GetMoveComponent().GunUp(m_Pivot->GetTransform(), DeltaTime);
}

void Controller::RotMaingunDown(float DeltaTime)
{
	m_Player->GetMoveComponent().GunDown(m_Player->GetVehicle().GetGunTransform(), DeltaTime);
	m_Pivot->GetMoveComponent().GunDown(m_Pivot->GetTransform(), DeltaTime);
}

void Controller::Shot()
{
	// リロードが完了しているかチェックする
	m_Player->Shot();
}

void Controller::UseSkill()
{
	m_Player->UseSkill();
}

bool Controller::ReplenishBullet()
{
	// 補給範囲に入っているか && 弾数が上限ではない
	if (m_Player->GetEnterSupplyPoint() && m_Player->GetIsBulletsUpperLimit() == false)
	{
		m_Player->ReplenishBullets();
		return true;
	}
	return false;
}
