/*--------------------------------------------------------------

	[Controller.cpp]
	Author : �o���đ�

	�v���C���[�̃R���g���[��

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

Controller::Controller(Player * pPlayer, GameCamera * pCamera, Pivot* pPivot) : m_Player(pPlayer), m_Camera(pCamera), m_Pivot(pPivot)
{
	
}

Controller::~Controller()
{
}

void Controller::FpsCameraMode(bool fpsMode)
{
	m_Camera->EnableFpsMode(fpsMode);
}

void Controller::MoveForward(float deltaTime)
{
	m_Player->moveComponent().MoveForward(m_Player->vehicle().bodyTransform(), deltaTime);
	m_Pivot->Move();
}

void Controller::MoveBackward(float deltaTime)
{
	m_Player->moveComponent().MoveBackward(m_Player->vehicle().bodyTransform(), deltaTime);
	m_Pivot->Move();
}

void Controller::RotRight(float deltaTime)
{
	m_Player->moveComponent().RotRight(m_Player->vehicle().bodyTransform(), deltaTime);
	m_Pivot->moveComponent().RotRight(m_Pivot->transform(), deltaTime);
}

void Controller::RotLeft(float deltaTime)
{
	m_Player->moveComponent().RotLeft(m_Player->vehicle().bodyTransform(), deltaTime);
	m_Pivot->moveComponent().RotLeft(m_Pivot->transform(), deltaTime);
}

void Controller::RotTurretRight(float deltaTime)
{
	m_Player->moveComponent().RotRight(m_Player->vehicle().turretTransform(), deltaTime);
	m_Pivot->moveComponent().RotRight(m_Pivot->transform(), deltaTime);
}

void Controller::RotTurretLeft(float deltaTime)
{
	m_Player->moveComponent().RotLeft(m_Player->vehicle().turretTransform(), deltaTime);
	m_Pivot->moveComponent().RotLeft(m_Pivot->transform(), deltaTime);
}

void Controller::RotMaingunUp(float deltaTime)
{
	m_Player->moveComponent().GunUp(m_Player->vehicle().gunTransform(), deltaTime);
	m_Pivot->moveComponent().GunUp(m_Pivot->transform(), deltaTime);
}

void Controller::RotMaingunDown(float deltaTime)
{
	m_Player->moveComponent().GunDown(m_Player->vehicle().gunTransform(), deltaTime);
	m_Pivot->moveComponent().GunDown(m_Pivot->transform(), deltaTime);
}

void Controller::Shot()
{
	// �����[�h���������Ă��邩�`�F�b�N����
	m_Player->Shot();
}

void Controller::UseSkill()
{
	m_Player->UseSkill();
}

void Controller::ReplenishBullet()
{
	if (m_Player->enterSupplyPoint())
	{
		m_Player->ReplenishBullets();
	}
}
