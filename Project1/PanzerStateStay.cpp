/*------------------------------------------------------------

	[PanzerState.cpp]
	Author : 出合翔太

	何もしないステート

--------------------------------------------------------------*/
#include "Cpu.h"
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Player.h"
#include "PanzerStateStay.h"
#include "PanzerStateMove.h"
#include "PanzerStateShot.h"
#include "PanzerStateRotation.h"
#include "PanzerUseSkill.h"

State::Stay::Stay()
{
	
}

State::Stay::~Stay()
{
}

void State::Stay::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::Stay::Update(Cpu * pCpu, float deltaTime)
{
	// 距離を求める
	const auto& cpuPosition = pCpu->vehicle().bodyTransform().position();
	const auto& playerPosition = m_Player->vehicle().bodyTransform().position();
	D3DXVECTOR3 length = cpuPosition - playerPosition;
	m_PlayerToDistance = D3DXVec3Length(&length);

	// 射程範囲内
	if (m_PlayerToDistance < m_ShotRange)
	{
		OutputDebugString("射程範囲\n");
		pCpu->ChangeState(std::make_unique<State::TurretRotation>());
	}
	// サーチ範囲内
	else if (m_PlayerToDistance < m_SearchRange)
	{
		OutputDebugString("サーチ範囲\n");
		pCpu->ChangeState(std::make_unique<State::BodyRotation>());
	}
}

float FindTargetDirection(Player * pTarget, Cpu * pCpu, const D3DXVECTOR3& forward)
{
	// プレイヤーとエネミーの距離を測る
	D3DXVECTOR3 dist = pCpu->vehicle().bodyTransform().position() - pTarget->vehicle().bodyTransform().position();
	D3DXVECTOR3 cross;
	// pivotの前ベクトルとdistの外積を求める
	D3DXVec3Cross(&cross, &forward, &dist);
	float t = cross.x - cross.y - cross.z;
	// t > 0.0fなら右にいる
	return t;
}
