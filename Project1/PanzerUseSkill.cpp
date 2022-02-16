/*-----------------------------------------------------------

	[PanzerUseSkill.h]
	Author : 出合翔太
	スキルを使う

------------------------------------------------------------*/
#include "Enemy.h"
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

void State::UseSkill::Begin(Player * Player)
{
}

void State::UseSkill::Update(Enemy* Enemy, float DeltaTime)
{
	// スキルを使う
	Enemy->UseSkill();
	Enemy->ChangeState(std::make_unique<State::Stay>());
}
