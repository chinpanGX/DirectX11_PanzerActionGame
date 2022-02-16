/*--------------------------------------------------

	[SkillList.cpp]
	Author : 出合翔太

	スキルのリスト

---------------------------------------------------*/
#include "Pawn.h"
#include "Status.h"
#include "SkillList.h"

// 倍率をセット
UseSkill::AttackUp::AttackUp(float Mag) : m_Mag(Mag)
{

}

void UseSkill::AttackUp::Use(Status& Status)
{
	m_Defualt = Status.GetAttack();
	float nowAttack = m_Defualt * m_Mag;
	Status.SetAttack(nowAttack);
}

void UseSkill::AttackUp::Reset(Status & Status)
{
	Status.SetAttack(m_Defualt);
}

UseSkill::DefenceUp::DefenceUp(float Mag) : m_Mag(Mag)
{
	
}

void UseSkill::DefenceUp::Use(Status& Status)
{
	m_Defualt = Status.GetDefence();
	float nowDefence = m_Defualt * m_Mag;
	Status.SetDefence(nowDefence);
}

void UseSkill::DefenceUp::Reset(Status & Status)
{
	Status.SetDefence(m_Defualt);
}

UseSkill::SpeedUp::SpeedUp(float Mag) : m_Mag(Mag)
{
}

void UseSkill::SpeedUp::Use(Status& Status)
{
	m_DefualtSpeed = Status.GetSpeed();
	m_DefualtAddForce = Status.GetAddForce();
	float nowSpeed = m_DefualtSpeed * m_Mag;
	float addForceMag = 3.0f;
	Status.SetSpeed(nowSpeed);
	Status.SetAddForce(addForceMag);
}

void UseSkill::SpeedUp::Reset(Status & Status)
{
	Status.SetSpeed(m_DefualtSpeed);
	Status.SetAddForce(m_DefualtAddForce);
}

void UseSkill::HealHp::Use(Status& Status)
{
	// 回復する量を求める
	float heal = Status.GetMaxHp() * m_AmountHeal;
	// 回復したHP
	float nowHp = Status.GetHp() + heal;
	Status.SetHp(nowHp);
}

void UseSkill::HealHp::Reset(Status & Status)
{
}

void UseSkill::QuickReload::Use(Status & Status)
{
	m_DefualtReloadTime = Status.GetReloadTime();
	Status.SetReloadTime(0.5f);
}

void UseSkill::QuickReload::Reset(Status & Status)
{
	Status.SetReloadTime(m_DefualtReloadTime);
}
