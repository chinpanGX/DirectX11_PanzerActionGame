/*--------------------------------------------------------------

	[PanzerStateRotation.cpp]
	Author : 出合翔太

	回転

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

	// 右旋回
	if (dir > 0.0f)
	{
		pCpu->moveComponent().RotRight(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// 左旋回
	else
	{
		pCpu->moveComponent().RotLeft(pCpu->vehicle().bodyTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}

	// -0.5f ～　0.5fの間になったら、移動ステートへ
	if (-0.5f < dir && dir < 0.5f)
	{
		pCpu->ChangeState(std::make_unique<State::Forward>());
	}	
}

float State::BodyRotation::GetDirection(Cpu * pCpu)
{
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);	
	// プレイヤーとエネミーの距離を測る
	D3DXVECTOR3 dist = pCpu->vehicle().bodyTransform().position() - player->vehicle().bodyTransform().position();
	D3DXVECTOR3 cross;
	// bodyの前ベクトルとdistの外積を求める
	D3DXVec3Cross(&cross, &pCpu->vehicle().bodyTransform().forward(), &dist);
	float t = cross.x - cross.y - cross.z;
	// t > 0.0fなら右にいる
	return t;
}
#pragma endregion BodyRotationメソッド

#pragma region TurretRotation_method
State::TurretRotation::TurretRotation()
{
}

State::TurretRotation::~TurretRotation()
{
}

void State::TurretRotation::Update(Cpu * pCpu, float deltaTime)
{
	// 右旋回
	if (GetDirection(pCpu) > 0.0f)
	{
		pCpu->moveComponent().RotRight(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotRight(pCpu->pivot().transform(), deltaTime);
	}
	// 左旋回
	else
	{
		pCpu->moveComponent().RotLeft(pCpu->vehicle().turretTransform(), deltaTime);
		pCpu->pivot().moveComponent().RotLeft(pCpu->pivot().transform(), deltaTime);
	}
	// リロードが完了したら撃つ
	if (pCpu->vehicle().status().finishReload() == true)
	{
		pCpu->ChangeState(std::make_unique<State::Shot>());
	}
}
float State::TurretRotation::GetDirection(Cpu * pCpu)
{
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	// プレイヤーとエネミーの距離を測る
	D3DXVECTOR3 dist = pCpu->vehicle().bodyTransform().position() - player->vehicle().bodyTransform().position();
	D3DXVECTOR3 cross;
	// pivotの前ベクトルとdistの外積を求める
	D3DXVec3Cross(&cross, &pCpu->pivot().transform().forward(), &dist);
	float t = cross.x - cross.y - cross.z;
	// t > 0.0fなら右にいる
	return t;	
}
#pragma endregion TurretRotationメソッド

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
#pragma endregion GunRotationメソッド