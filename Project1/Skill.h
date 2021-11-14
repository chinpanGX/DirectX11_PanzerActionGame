/*---------------------------------------------------------------

	[Skill.h]
	Author : 出合翔太

	スキルを管理する

----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

class Pawn;
class Status;
class IUseSkill;
class Skill
{
public:
	Skill();
	~Skill();
	// スキルを設定する(設定するスキル)
	void SetSkill(std::unique_ptr<IUseSkill> useSkill);
	// スキル発動(発動するまでの時間)
	void Begin(float enableTime); 
	void Update(Status& status, const D3DXVECTOR3& position);

	// スキルゲージがたまる時間
	void SetTime(float time); //　進める時間
	void Enable(Pawn* pawn);
	const int32_t GetPhase() const;
	const float GetEnableTime() const;
	const bool GetAlreadyUseble() const;
private:
	// エフェクトの再生
	void PlayEffect(Pawn* pawn);

	std::vector<std::unique_ptr<IUseSkill>> m_UseSkill;
	class SkillParticle* m_SkillEffect;

	int32_t m_Phase = 0;	// フェーズ
	float m_EnableTime = 30.0f;		// スキルを有効にする時間
	float m_Time = 1.0f;	// 進める時間
	float m_NowTime = 0.0f;
	bool m_AlreadyUseble = false; // スキルが使える状態かどうか

};