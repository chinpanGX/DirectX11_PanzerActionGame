/*------------------------------------------------------------

	[Cpu.cpp]
	プレイヤーが操作しないオブジェクト
	Author : 出合翔太

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

void Cpu::UseSkill()
{
	// スキルを使用
	vehicle().skill().Enable(this);
	vehicle().skill().PlayEffect(this);
}
