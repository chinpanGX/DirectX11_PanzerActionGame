/*--------------------------------------------------------------

	[Status.cpp]
	Author : �o���đ�

	��Ԃ̃X�e�[�^�X

---------------------------------------------------------------*/
#include "Status.h"

Status::Status(Country country, float cost, float hp, float attack, float defence, float speed, float reloadTime, float rotSpeed)
	: m_FinishReload(true), m_GunUpMax(0.26f), m_GunDownMax(0.03f), m_MaxHp(hp), m_Country(country), m_Cost(cost), m_Hp(hp),
	m_Attack(attack), m_Defense(defence), m_Speed(speed), m_ReloadTime(reloadTime), m_RotSpeed(rotSpeed), m_Time(1.0f)
{
}

Status::~Status()
{
}

void Status::Update()
{
	const float time = m_ReloadTime * 60.0f; // �����[�h�������鎞��
	m_NowReloadTime += m_Time;
	// �����[�h�������Ԃ𒴂�����
	if (m_NowReloadTime >= time)
	{
		// �����[�h����
		m_FinishReload = true;
	}
}

void Status::ResetReloadTime()
{
	m_NowReloadTime = 0;
	m_FinishReload = false;
}

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
	// �}�b�N�X��葽���Ȃ�Ȃ��悤�ɂ���
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

void Status::SetAddForce(float force)
{
	m_AddForce = force;
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

void Status::SetReloadTime(float Time)
{
	m_Time = Time;
}

const float Status::GetReloadTime() const
{
	return m_ReloadTime;
}

const bool Status::GetFinishReload() const
{
	return m_FinishReload;
}
