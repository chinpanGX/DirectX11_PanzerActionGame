/*------------------------------------------------------------

	[Cpu.cpp]
	�v���C���[�����삵�Ȃ��I�u�W�F�N�g
	Author : �o���đ�

--------------------------------------------------------------*/
#include "PanzerState.h"
#include "Vehicle.h"
#include "Skill.h"
#include "Cpu.h"

Cpu::Cpu() : Pawn(Factory::FVehicle::EType::E_CPU)
{
}

Cpu::~Cpu()
{
}

void Cpu::Begin()
{
}

void Cpu::Update()
{
}

void Cpu::Event()
{
}

void Cpu::Draw()
{
}

CpuStateRule & Cpu::cpuRule() const
{
	if (!m_CpuRule)
	{
		std::domain_error("Null");
	}
	return *m_CpuRule;
}

void Cpu::UseSkill()
{
	// �X�L�����g�p
	vehicle().skill().Enable(this);
	vehicle().skill().PlayEffect(this);	
}
