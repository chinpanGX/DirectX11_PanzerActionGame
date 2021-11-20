/*--------------------------------------------------------------

	[Status.h]
	Author : �o���đ�

	��Ԃ̃X�e�[�^�X

---------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

class Status
{
public:
	enum Country : int32_t
	{
		DE, // �h�C�c
		UK, // �C�M���X
		US, // �A�����J
		RU, // ���V�A
	};

	Status() = delete;
	// param = ���AHp�A�U���́A�h��́A�ړ����x�A���U���ԁA��]���x
	Status(Country country, float cost, float hp, float attack, float defence, float speed, float reloadTime, float rotSpeed);
	~Status();
	
	void Update();
	void RereloadTime();

	// ��
	const Country& country() const;

	// �R�X�g
	const float cost() const;

	// HP
	const float maxHp()const;
	void hp(float Hp);
	const float hp() const;

	// �U����
	void attack(float Attack);
	const float attack()const;

	// �h���
	void defence(float Defence);
	const float defence()const;

	// �ړ����x
	void speed(float Speed);
	const float speed() const;
	
	// �����x
	void addForce(float force);
	const float addForce() const;

	// ��]���x
	const float rotSpeed() const;
	
	// ��C�̍ő�p�x
	const float gunAngleUpMax() const;
	const float gunAngleDownMax() const;

	void reloadTime(float Time);
	// �����[�h�͊������Ă��邩
	const float reloadTime()const;
	const bool finishReload() const;
private:
	Country m_Country;
	const float m_MaxHp; // Max�l
	const float m_ReloadTime; // �����[�h�ɕK�v�ȕb��
	
	float m_Cost; // ��Ԃ̃R�X�g
	float m_Hp;		// Hp
	float m_Attack; // �U����
	float m_Defense;  // �h���

	float m_Time; // �����[�h�����鎞��
	float m_NowReloadTime; // �����[�h���Ԓ�

	float m_Speed; // �ړ����x
	float m_AddForce = 0.1f; // �����x
	float m_RotSpeed; // ��]���x

	// ��C�̍ő�l
	const float m_GunUpMax;
	const float m_GunDownMax;

	bool m_FinishReload;  // true�Ō����Ƃ��ł���
};

