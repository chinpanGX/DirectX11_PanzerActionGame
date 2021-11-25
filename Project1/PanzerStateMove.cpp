/*-----------------------------------------------------------
	
	[State::.cpp]
	Author : �o���đ�

-------------------------------------------------------------*/
#include "Vehicle.h"
#include "MoveComponent.h"
#include "Enemy.h"
#include "PanzerStateMove.h"
#include "PanzerStateRotation.h"
#include "PanzerStateStay.h"
#include "Pivot.h"
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "Engine.h"
#include "Application.h"
#include "Player.h"

State::Forward::Forward()
{
	
}


State::Forward::~Forward()
{
}

void State::Forward::Begin(Player * pPlayer)
{
	m_Player = pPlayer;
}

void State::Forward::Update(Cpu * pCpu, float deltaTime)
{
	pCpu->moveComponent().MoveForward(pCpu->vehicle().bodyTransform(), deltaTime);
	pCpu->pivot().Move();

	auto player = m_Player;
	if (player)
	{
		float dir = FindTargetDirection(player, pCpu, pCpu->vehicle().bodyTransform().forward());
		if (-5.0f > dir || dir > 5.0f)
		{
			pCpu->ChangeState(std::make_unique<State::BodyRotation>());
		}
		// �v���C���[��CPU�̋��������߂�
		D3DXVECTOR3 playerPosition = player->vehicle().bodyTransform().position();
		D3DXVECTOR3 cpuPosition = pCpu->vehicle().bodyTransform().position();
		D3DXVECTOR3 tmp = cpuPosition - playerPosition;
		float dist = D3DXVec3Length(&tmp);
		// �������߂��Ȃ�����,�X�e�[�g��ς���
		if (dist < 100.0f)
		{
			pCpu->ChangeState(std::make_unique<State::Stay>());
		}
	}
}

State::Backward::Backward()
{
}

State::Backward::~Backward()
{
}

void State::Backward::Begin(Player * pPlayer)
{
}

void State::Backward::Update(Cpu * pCpu, float deltaTime)
{
	FrameCountDown();
	if (GetFrameZeroFlag() == true)
	{
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}
	pCpu->moveComponent().MoveBackward(pCpu->vehicle().bodyTransform(), deltaTime);
	pCpu->pivot().Move();
	// �v���C���[�Ƃ̓����蔻��
	auto player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	if (player)
	{
		if (Intersect(pCpu->vehicle().collider(0).GetSphere3(), player->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(pCpu->vehicle().collider(0).GetOBB3(), player->vehicle().collider(0).GetOBB3()))
			{
				pCpu->moveComponent().MoveForward(pCpu->vehicle().bodyTransform(), deltaTime);
				pCpu->pivot().Move();
				pCpu->ChangeState(std::make_unique<State::Stay>());
			}
		}
	}
}

