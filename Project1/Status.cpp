/*--------------------------------------------------------------

	[Status.cpp]
	Author : 出合翔太

	戦車のステータス

---------------------------------------------------------------*/
#include "Status.h"

Status::Status() : m_GunUpMax(0.26f), m_GunDownMax(0.03f), m_AddTime(1.0f)
{

}

Status::~Status()
{
}

void Status::Set(Country country, float cost, float hp, float SetAttack, float SetDefence, float speed, float reloadTime, float rotSpeed)
{
	m_Country = country;
	m_Cost = cost;
	m_MaxHp = hp;
	m_Hp = hp;
	m_defaltAttack = SetAttack;
	m_Attack = SetAttack;
	m_defaultDefence = SetDefence;
	m_Defense = SetDefence;
	m_defaultSpeed = speed;
	m_Speed = speed;
	m_defaultReloadTime = reloadTime;
	m_ReloadTime = reloadTime;
	m_RotSpeed = rotSpeed;
}

void Status::Reset()
{
	m_Hp = m_MaxHp;
	m_Attack = m_defaltAttack;
	m_Defense = m_defaultDefence;
	m_Speed = m_defaultSpeed;
	m_ReloadTime = m_defaultReloadTime;
}

#pragma region _Getter&Setter_function_
const Status::Country & Status::GetCountry() const
{
	return m_Country;
}

const float Status::GetCost() const
{
	return m_Cost;
}

const float Status::GetMaxHp() const
{
	return m_MaxHp;
}

void Status::SetHp(float Hp)
{
	float tmp = Hp;
	// マックスより多くならないようにする
	if (m_MaxHp < tmp)
	{
		tmp = m_MaxHp;
	}
	m_Hp = tmp;
}

const float Status::GetHp() const
{
	return m_Hp;
}

void Status::SetAttack(float Attack)
{
	m_Attack = Attack;
}

const float Status::GetAttack() const
{
	return m_Attack;
}

void Status::SetDefence(float Defence)
{
	m_Defense = Defence;
}

const float Status::GetDefence() const
{
	return m_Defense;
}

void Status::SetSpeed(float Speed)
{
	m_Speed = Speed;
}

const float Status::GetSpeed() const
{
	return m_Speed;
}

void Status::SetAddForce(float Force)
{
	m_AddForce = Force;
}

const float Status::GetAddForce() const
{
	return m_AddForce;
}

const float Status::GetRotSpeed() const
{
	return m_RotSpeed;
}

const float Status::GetGunAngleUpMax() const
{
	return m_GunUpMax;
}

const float Status::GetGunAngleDownMax() const
{
	return m_GunDownMax;
}

void Status::SetAddTime(float AddTime)
{
	m_AddTime = AddTime;
}

const float Status::GetAddTime() const
{
	return m_AddTime;
}

void Status::SetReloadTime(float Time)
{
	m_ReloadTime = Time;
}

const float Status::GetReloadTime() const
{
	return m_ReloadTime;
}
#pragma endregion _Getter/Setterの関数_