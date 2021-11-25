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
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
}

State::Stay::~Stay()
{
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