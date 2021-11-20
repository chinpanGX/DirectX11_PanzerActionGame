/*--------------------------------------------------

	[SkillList.cpp]
	Author : �o���đ�

	�X�L���̃��X�g

---------------------------------------------------*/
#include "Pawn.h"
#include "Status.h"
#include "SkillList.h"

// �{�����Z�b�g
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
	// �񕜂���ʂ����߂�
	float heal = status.maxHp() * m_AmountHeal;
	// �񕜂���HP
	float nowHp = status.hp() + heal;
	status.hp(nowHp);
}

void UseSkill::HealHp::Reset(Status & status)
{
}
