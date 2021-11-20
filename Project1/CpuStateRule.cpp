/*-------------------------------------------------------------
	
	[CpuStateRule.cpp]
	CPU�̓����̃��[���A�������`���ĊǗ�����
	Author : �o���đ�

--------------------------------------------------------------*/
#include "Cpu.h"
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

void CpuStateRule::Update(Cpu * pCpu)
{
	// �v���C���[�Ƃ̋����𑪂�
	PlayerToDistance(pCpu);

	// ���������߂�
	DecideBehavior();
}

void CpuStateRule::DecideBehavior()
{
	// �����ɉ����āA��������
	// �˒��͈͓����H
	if (m_PlayerToDistance <= m_ShotRange)
	{
		m_Behavior = 0;
		OutputDebugString("�˒��͈͓�\n");
	}
	// ���G�͈͂Ȃ����H
	else if (m_PlayerToDistance <= m_SearchRange)
	{
		m_Behavior = 1;
		OutputDebugString("���G�͈͓�\n");
		
	}	
	// �ҋ@
	else
	{
		m_Behavior = 3;
		OutputDebugString("�ҋ@\n");
	}
}

const int32_t CpuStateRule::behavior() const
{
	return m_Behavior;
}

void CpuStateRule::PlayerToDistance(Cpu * pCpu)
{
	// �G�l�~�[�ƃv���C���[�̋��������߂�
	const auto& cpuPosition = pCpu->vehicle().bodyTransform().position();
	const auto& playerPosition = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR)->vehicle().bodyTransform().position();
	D3DXVECTOR3 length = cpuPosition - playerPosition;
	m_PlayerToDistance = D3DXVec3LengthSq(&length);
}
