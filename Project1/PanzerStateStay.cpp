/*------------------------------------------------------------

	[PanzerState.cpp]
	Author : �o���đ�

	�������Ȃ��X�e�[�g

--------------------------------------------------------------*/
#include "Cpu.h"
#include "Vehicle.h"
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

void State::Stay::Update(Cpu * pCpu, float deltaTime)
{
	switch(pCpu->cpuRule().behavior())
	{
	// �˒��͈͂Ȃ�
	case 0:
		pCpu->ChangeState(std::make_unique<State::TurretRotation>());
		break;
	// ���G�͈͓�
	case 1:
		pCpu->ChangeState(std::make_unique<State::BodyRotation>());
		break;	
	//�@�X�L�����g��
	case 2:
		pCpu->ChangeState(std::make_unique<State::UseSkill>());
		break;
	}

}
