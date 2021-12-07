/*--------------------------------------------------------------

	[Status.h]
	Author : 出合翔太

	戦車のステータス

---------------------------------------------------------------*/
#pragma once
#include "stdafx.h"

class Status
{
public:
	enum Country : int32_t
	{
		DE, // ドイツ
		UK, // イギリス
		US, // アメリカ
		RU, // ロシア
	};

	Status() = delete;
	// param = 国、Hp、攻撃力、防御力、移動速度、装填時間、回転速度
	Status(Country country, float cost, float hp, float attack, float defence, float speed, float reloadTime, float rotSpeed);
	~Status();
	
	// 国
	const Country& country() const;

	// コスト
	const float cost() const;

	// HP
	const float maxHp()const;
	void hp(float Hp);
	const float hp() const;

	// 攻撃力
	void attack(float Attack);
	const float attack()const;

	// 防御力
	void defence(float Defence);
	const float defence()const;

	// 移動速度
	void speed(float Speed);
	const float speed() const;
	
	// 加速度
	void addForce(float force);
	const float addForce() const;

	// 回転速度
	const float rotSpeed() const;
	
	// 主砲の最大角度
	const float gunAngleUpMax() const;
	const float gunAngleDownMax() const;

	// リロード関係
	void reloadAddTime(float AddTime);	
	const float addTime()const;

	void reloadTime(float time);
	const float reloadTime()const;
private:
	Country m_Country;
	const float m_MaxHp; // Max値
	float m_ReloadTime; // リロードに必要な秒数
	
	float m_Cost; // 戦車のコスト
	float m_Hp;		// Hp
	float m_Attack; // 攻撃力
	float m_Defense;  // 防御力

	float m_AddTime; // リロードをする時間

	float m_Speed; // 移動速度
	float m_AddForce = 0.1f; // 加速度
	float m_RotSpeed; // 回転速度

	// 主砲の最大値
	const float m_GunUpMax;
	const float m_GunDownMax;
};

