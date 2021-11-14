/*--------------------------------------------------

	[SkillList.cpp]
	Author : oãÄ¾

	XLÌXg

---------------------------------------------------*/
#include "Pawn.h"
#include "Status.h"
#include "SkillList.h"

// {¦ðZbg
UseSkill::AttackUp::AttackUp(float mag) : m_Mag(mag)
{

}

void UseSkill::AttackUp::Use(Status& status)
{
	m_Defualt = status.GetAttack();
	float nowAttack = m_Defualt * m_Mag;
	status.SetAttack(nowAttack);
}

void UseSkill::AttackUp::Reset(Status & status)
{
	status.SetAttack(m_Defualt);
}

UseSkill::DefenceUp::DefenceUp(float mag) : m_Mag(mag)
{
	
}

void UseSkill::DefenceUp::Use(Status& status)
{
	m_Defualt = status.GetDefence();
	float nowDefence = m_Defualt * m_Mag;
	status.SetDefence(nowDefence);
}

void UseSkill::DefenceUp::Reset(Status & status)
{
	status.SetDefence(m_Defualt);
}

UseSkill::SpeedUp::SpeedUp(float mag) : m_Mag(mag)
{
}

void UseSkill::SpeedUp::Use(Status& status)
{
	m_DefualtSpeed = status.GetSpeed();
	m_DefualtAddForce = status.GetAddForce();
	float nowSpeed = m_DefualtSpeed * m_Mag;
	float addForceMag = 3.0f;
	status.SetSpeed(nowSpeed);
	status.SetAddForce(addForceMag);
}

void UseSkill::SpeedUp::Reset(Status & status)
{
	status.SetSpeed(m_DefualtSpeed);
	status.SetAddForce(m_DefualtAddForce);
}

void UseSkill::HealHp::Use(Status& status)
{
	// ñ·éÊðßé
	float heal = status.GetMaxHp() * m_AmountHeal;
	// ñµ½HP
	float nowHp = status.GetHp() + heal;
	status.SetHp(nowHp);
}

void UseSkill::HealHp::Reset(Status & status)
{
}
