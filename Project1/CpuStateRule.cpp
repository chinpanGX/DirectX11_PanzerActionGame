/*-------------------------------------------------------------
	
	[CpuStateRule.cpp]
	CPUの動きのルール、条件を定義して管理する
	Author : 出合翔太

--------------------------------------------------------------*/
#include "Player.h"
#include "Vehicle.h"
#include "Body.h"
#include "Engine.h"
#include "Application.h"
#include "CpuStateRule.h"


CpuStateRule::CpuStateRule()
{
}

CpuStateRule::~CpuStateRule()
{
}

void CpuStateRule::DecideBehavior()
{
	// 距離に応じて、条件分岐
	// 射程範囲内か？
	if (m_PlayerToDistance <= m_ShotRange)
	{
		m_Behavior = 0;
	}
	// 索敵範囲ないか？
	else if (m_PlayerToDistance <= m_SearchRange)
	{
		m_Behavior = 1;
	}
	// ランダムで動く
	else
	{
		m_Behavior = 2;
	}
}

const int32_t CpuStateRule::behavior() const
{
	return m_Behavior;
}

void CpuStateRule::PlayerToDistance(Cpu * Cpu)
{
	// エネミーとプレイヤーの距離を求める
	//const auto& enemyPosition = Cpu->vehicle().bodyTransform().position();
	//const auto& playerPosition = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->vehicle().bodyTransform().position();
	//D3DXVECTOR3 length = enemyPosition - playerPosition;
	//m_PlayerToDistance = D3DXVec3LengthSq(&length);
}
