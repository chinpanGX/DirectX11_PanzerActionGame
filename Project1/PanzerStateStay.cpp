/*------------------------------------------------------------

	[PanzerState.cpp]
	Author : �o���đ�

	�������Ȃ��X�e�[�g

--------------------------------------------------------------*/
#include "Enemy.h"
#include "Engine.h"
#include "Application.h"
#include "Vehicle.h"
#include "Reload.h"
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

void State::Stay::Begin(Player * Player)
{
	m_Player = Player;
}

void State::Stay::Update(Enemy* Enemy, float DeltaTime)
{
	// ���������߂�
	const auto& cpuPosition = Enemy->GetVehicle().GetBodyTransform().GetPosition();
	const auto& playerPosition = m_Player->GetVehicle().GetBodyTransform().GetPosition();
	D3DXVECTOR3 length = cpuPosition - playerPosition;
	m_PlayerToDistance = D3DXVec3Length(&length);


	// �˒��͈͓�
	if (m_PlayerToDistance < m_ShotRange)
	{

		Enemy->ChangeState(std::make_unique<State::TurretRotation>());
	}
	// �T�[�`�͈͓�
	else if (m_PlayerToDistance < m_SearchRange)
	{		
		Enemy->ChangeState(std::make_unique<State::BodyRotation>());		
	}
	else
	{
		Enemy->ChangeState(std::make_unique<State::Forward>());
	}
}

float FindTargetDirection(Player * pTarget, Enemy* Enemy, const D3DXVECTOR3& forward)
{
	// �v���C���[�ƃG�l�~�[�̋����𑪂�
	D3DXVECTOR3 dist = Enemy->GetVehicle().GetBodyTransform().GetPosition() - pTarget->GetVehicle().GetBodyTransform().GetPosition();
	D3DXVECTOR3 cross;
	// pivot�̑O�x�N�g����dist�̊O�ς����߂�
	D3DXVec3Cross(&cross, &forward, &dist);
	float t = cross.x - cross.y - cross.z;
	// t > 0.0f�Ȃ�E�ɂ���
	return t;
}
