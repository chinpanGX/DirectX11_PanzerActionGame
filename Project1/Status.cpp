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

void Status::Set(Country country, float cost, float hp, float attack, float defence, float speed, float reloadTime, float rotSpeed)
{
	m_Country = country;
	m_Cost = cost;
	m_MaxHp = hp;
	m_Hp = hp;
	m_Attack = attack;
	m_Defense = defence;
	m_Speed = speed;
	m_ReloadTime = reloadTime;
	m_RotSpeed = rotSpeed;
}

#pragma region _Getter&Setter_function_
const Status::Country & Status::country() const
{
	return m_Country;
}

const float Status::cost() const
{
	return m_Cost;
}

const float Status::maxHp() const
{
	return m_MaxHp;
}

void Status::hp(float Hp)
{
	float tmp = Hp;
	// マックスより多くならないようにする
	if (m_MaxHp < tmp)
	{
		tmp = m_MaxHp;
	}
	m_Hp = tmp;
}

const float Status::hp() const
{
	return m_Hp;
}

void Status::attack(float Attack)
{
	m_Attack = Attack;
}

const float Status::attack() const
{
	return m_Attack;
}

void Status::defence(float Defence)
{
	m_Defense = Defence;
}

const float Status::defence() const
{
	return m_Defense;
}

void Status::speed(float Speed)
{
	m_Speed = Speed;
}

const float Status::speed() const
{
	return m_Speed;
}

void Status::addForce(float force)
{
	m_AddForce = force;
}

const float Status::addForce() const
{
	return m_AddForce;
}

const float Status::rotSpeed() const
{
	return m_RotSpeed;
}

const float Status::gunAngleUpMax() const
{
	return m_GunUpMax;
}

const float Status::gunAngleDownMax() const
{
	return m_GunDownMax;
}

void Status::reloadAddTime(float AddTime)
{
	m_AddTime = AddTime;
}

const float Status::addTime() const
{
	return m_AddTime;
}

void Status::reloadTime(float time)
{
	m_ReloadTime = time;
}

const float Status::reloadTime() const
{
	return m_ReloadTime;
}
#pragma endregion _Getter/Setterの関数_