/*-----------------------------------------------------------

	[PanzerUseSkill.h]
	Author : �o���đ�
	�X�L�����g��

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
	// �X�L�����g�����ԂȂ�A�g��
	if (pCpu->vehicle().skill().alreadyUseble())
	{
		pCpu->UseSkill();
		pCpu->ChangeState(std::make_unique<State::Stay>());
	}
}
