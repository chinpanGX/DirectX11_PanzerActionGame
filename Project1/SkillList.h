/*--------------------------------------------------

	[SkillList.h]
	Author : 出合翔太

	スキルのリスト

---------------------------------------------------*/
#pragma once
#include "IUseSkill.h"

class Status;
namespace UseSkill
{
	// 攻撃力アップ
	class AttackUp : public IUseSkill
	{
	public:
		AttackUp() = delete;
		AttackUp(float Mag);
		void Use(Status& Status)override;
		void Reset(Status & Status)override;
	private:
		float m_Defualt;
		float m_Mag; // 倍率
	};

	// 装甲値アップ
	class DefenceUp : public IUseSkill
	{
	public:
		DefenceUp() = delete;
		DefenceUp(float Mag);
		void Use(Status& Status)override;
		void Reset(Status & Status)override;
	private:
		float m_Defualt;
		float m_Mag; // 倍率
	};

	// 速度アップ
	class SpeedUp final : public IUseSkill
	{
	public:
		SpeedUp() = delete;
		SpeedUp(float Mag);
		void Use(Status& Status)override;
		void Reset(Status & Status)override;
	private:
		float m_DefualtSpeed;
		float m_DefualtAddForce;
		float m_Mag; // 倍率
	};

	// MAXHPの20%回復
	class HealHp final : public IUseSkill
	{
	public:
		void Use(Status& Status)override;
		void Reset(Status & Status)override;
	private:
		float m_AmountHeal = 0.2f; // 回復する割合 = 20%
	};

	class QuickReload final : public IUseSkill
	{
	public:
		void Use(Status& Status)override;
		void Reset(Status & Status)override;
	private:
		float m_DefualtReloadTime;
	};
}
#if 0
// 味方のスキルゲージをためる
class UseSkillAddGage
{

};
#endif


