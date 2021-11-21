/*-------------------------------------------------------------
	
	[CpuStateRule.cpp]
	CPUの動きのルール、条件を定義して管理する
	Author : 出合翔太

--------------------------------------------------------------*/
#include "Cpu.h"
#include "Player.h"
#include "Skill.h"
#include "Vehicle.h"
#include "Body.h"
#include "Engine.h"
#include "Application.h"
#include "CpuStateRule.h"

CpuStateRule::CpuStateRule(Cpu * pCpu) : m_Cpu(pCpu)
{
}

CpuStateRule::~CpuStateRule()
{
}

void CpuStateRule::Update()
{
	// プレイヤーとの距離を測る
	PlayerToDistance();

	// 挙動を決める
	DecideBehavior();
}

void CpuStateRule::DecideBehavior()
{
	// 距離に応じて、条件分岐
	// 射程範囲内か？
	if (m_PlayerToDistance <= m_ShotRange)
	{
		m_Behavior = 0;
		OutputDebugString("射程範囲内\n");
		// スキルが使える状態か
		if (m_Cpu->vehicle().skill().alreadyUseble())
		{
			m_Cpu->UseSkill();
		}
	}
	// 索敵範囲ないか？
	else if (m_PlayerToDistance <= m_SearchRange)
	{
		m_Behavior = 1;
		OutputDebugString("索敵範囲内\n");		
	}	
	// 待機
	else
	{
		m_Behavior = 3;
		OutputDebugString("待機\n");
	}
}

const int32_t CpuStateRule::behavior() const
{
	return m_Behavior;
}

void CpuStateRule::PlayerToDistance()
{
	// エネミーとプレイヤーの距離を求める
	const auto& cpuPosition = m_Cpu->vehicle().bodyTransform().position();
	const auto& playerPosition = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->vehicle().bodyTransform().position();
	D3DXVECTOR3 length = cpuPosition - playerPosition;
	m_PlayerToDistance = D3DXVec3LengthSq(&length);
}
