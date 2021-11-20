/*------------------------------------------------------------

	[Cpu.cpp]
	プレイヤーが操作しないオブジェクト
	Author : 出合翔太

--------------------------------------------------------------*/
#include "PanzerState.h"
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
