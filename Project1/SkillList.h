/*--------------------------------------------------

	[SkillList.h]
	Author : �o���đ�

	�X�L���̃��X�g

---------------------------------------------------*/
#pragma once
#include "IUseSkill.h"

class Status;
namespace UseSkill
{
	// �U���̓A�b�v
	class AttackUp : public IUseSkill
	{
	public:
		AttackUp() = delete;
		AttackUp(float mag);
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_Defualt;
		float m_Mag; // �{��
	};

	// ���b�l�A�b�v
	class DefenceUp : public IUseSkill
	{
	public:
		DefenceUp() = delete;
		DefenceUp(float mag);
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_Defualt;
		float m_Mag; // �{��
	};

	// ���x�A�b�v
	class SpeedUp final : public IUseSkill
	{
	public:
		SpeedUp() = delete;
		SpeedUp(float mag);
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_DefualtSpeed;
		float m_DefualtAddForce;
		float m_Mag; // �{��
	};

	// MAXHP��20%��
	class HealHp final : public IUseSkill
	{
	public:
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_AmountHeal = 0.2f; // �񕜂��銄�� = 20%
	};

	class QuickReload final : public IUseSkill
	{
	public:
		void Use(Status& status)override;
		void Reset(Status & status)override;
	private:
		float m_DefualtReloadTime;
	};
}
#if 0
// �����̃X�L���Q�[�W�����߂�
class UseSkillAddGage
{

};
#endif


