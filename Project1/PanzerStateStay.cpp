/*------------------------------------------------------------

	[PanzerState.cpp]
	Author : �o���đ�

	�������Ȃ��X�e�[�g

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
	// ���������߂�
	const auto& cpuPosition = pCpu->vehicle().bodyTransform().position();
	const auto& playerPosition = m_Player->vehicle().bodyTransform().position();
	D3DXVECTOR3 length = cpuPosition - playerPosition;
	m_PlayerToDistance = D3DXVec3Length(&length);

	// �˒��͈͓�
	if (m_PlayerToDistance < m_ShotRange)
	{
		OutputDebugString("�˒��͈�\n");
		pCpu->ChangeState(std::make_unique<State::TurretRotation>());
	}
	// �T�[�`�͈͓�
	else if (m_PlayerToDistance < m_SearchRange)
	{
		OutputDebugString("�T�[�`�͈�\n");
		pCpu->ChangeState(std::make_unique<State::BodyRotation>());
	}
}

float FindTargetDirection(Player * pTarget, Cpu * pCpu, const D3DXVECTOR3& forward)
{
	// �v���C���[�ƃG�l�~�[�̋����𑪂�
	D3DXVECTOR3 dist = pCpu->vehicle().bodyTransform().position() - pTarget->vehicle().bodyTransform().position();
	D3DXVECTOR3 cross;
	// pivot�̑O�x�N�g����dist�̊O�ς����߂�
	D3DXVec3Cross(&cross, &forward, &dist);
	float t = cross.x - cross.y - cross.z;
	// t > 0.0f�Ȃ�E�ɂ���
	return t;
}
