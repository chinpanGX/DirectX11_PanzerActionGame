/*---------------------------------------------------------------

	[Skill.h]
	Author : 出合翔太

	スキルを管理する

----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

class Status;
class IUseSkill;
class Skill
{
public:
	Skill();
	~Skill();
	void SetSkill(std::unique_ptr<IUseSkill> useSkill);
	void Begin(float enableTime);
	void Update(Status& status);
	void SetTime(float time); //　進める時間
	void Enable();
	const int32_t GetPhase() const;
	const float GetEnableTime() const;
	const bool GetAlreadyUseble() const;
private:
	std::vector<std::unique_ptr<IUseSkill>> m_UseSkill;
	int32_t m_Phase = 0;	// フェーズ
	float m_EnableTime = 30.0f;		// スキルを有効にする時間
	float m_Time = 1.0f;	// 進める時間
	float m_NowTime = 0.0f;
	bool m_AlreadyUseble = false; // スキルが使える状態かどうか
};