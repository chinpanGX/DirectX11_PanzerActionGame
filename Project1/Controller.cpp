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
	// リロードが完了しているかチェックする
	if (m_Player->vehicle().status().finishReload() == true)
	{
		// リロードが完了している
		// 射撃
		m_Player->vehicle().Shot(m_Pivot->transform());
		// オーディオ
		Engine::Get().resource()->AudioPlay("Shot");
		// リロードエフェクト
		auto effect = Engine::Get().application()->GetScene()->AddGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_EFFECT);
		D3DXVECTOR3 offset = m_Pivot->transform().position() + D3DXVECTOR3(0.0f, 3.0f, 0.0f) + (m_Pivot->transform().forward() * 5.0f);
		effect->transform().position(offset);
	}
}

void Controller::UseSkill()
{
	m_Player->UseSkill();
}
