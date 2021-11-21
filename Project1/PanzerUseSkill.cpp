/*-----------------------------------------------------------

	[PanzerUseSkill.h]
	Author : 出合翔太
	スキルを使う

------------------------------------------------------------*/
#include "Cpu.h"
#include "Vehicle.h"
#include "Skill.h"
#include "PanzerUseSkill.h"
#include "PanzerStateStay.h"

State::UseSkill::UseSkill()
{
}

State::UseSkill::~UseSkill()
{
}

void State::UseSkill::Update(Cpu * pCpu, float deltaTime)
{
	// スキルが使える状態なら、使う
	if (pCpu->vehicle().skill().alreadyUseble())
	{
		pCpu->UseSkill();
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}
}
