/*--------------------------------------------------

	[SkillList.cpp]
	Author : 出合翔太

	スキルのリスト

---------------------------------------------------*/
#include "Pawn.h"
#include "Status.h"
#include "SkillList.h"

// 倍率をセット
UseSkill::AttackUp::AttackUp(float mag) : m_Mag(mag)
{

}

void UseSkill::AttackUp::Use(Status& status)
{
	m_Defualt = status.attack();
	float nowAttack = m_Defualt * m_Mag;
	status.attack(nowAttack);
}

void UseSkill::AttackUp::Reset(Status & status)
{
	status.attack(m_Defualt);
}

UseSkill::DefenceUp::DefenceUp(float mag) : m_Mag(mag)
{
	
}

void UseSkill::DefenceUp::Use(Status& status)
{
	m_Defualt = status.defence();
	float nowDefence = m_Defualt * m_Mag;
	status.defence(nowDefence);
}

void UseSkill::DefenceUp::Reset(Status & status)
{
	status.defence(m_Defualt);
}

UseSkill::SpeedUp::SpeedUp(float mag) : m_Mag(mag)
{
}

void UseSkill::SpeedUp::Use(Status& status)
{
	m_DefualtSpeed = status.speed();
	m_DefualtAddForce = status.addForce();
	float nowSpeed = m_DefualtSpeed * m_Mag;
	float addForceMag = 3.0f;
	status.speed(nowSpeed);
	status.addForce(addForceMag);
}

void UseSkill::SpeedUp::Reset(Status & status)
{
	status.speed(m_DefualtSpeed);
	status.addForce(m_DefualtAddForce);
}

void UseSkill::HealHp::Use(Status& status)
{
	// 回復する量を求める
	float heal = status.maxHp() * m_AmountHeal;
	// 回復したHP
	float nowHp = status.hp() + heal;
	status.hp(nowHp);
}

void UseSkill::HealHp::Reset(Status & status)
{
}
