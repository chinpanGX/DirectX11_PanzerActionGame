/*---------------------------------------------------------------

	[Skill.h]
	Author : 出合翔太

	スキルを管理する

----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

namespace Billboard
{
	class SkillParticle;
}
class Pawn;
class Status;
class IUseSkill;
class Skill
{
public:
	Skill();
	~Skill();
	// スキルを設定する(設定するスキル)
	void SetSkill(std::unique_ptr<IUseSkill> UseSkill);
	// スキル発動(発動するまでの時間)
	void Begin(float TimeToActivateSkill); 
	void Update(Status& Status, const D3DXVECTOR3& Position);

	// エフェクトの再生
	void PlayEffect(Pawn* Pawn);

	// スキルゲージがたまる時間
	void SetTime(float Smount); //　進める時間
	// スキルを使う
	void Enable(Pawn* Pawn);
	// リセット
	void Reset(Status& Status);	  

	// ゲッター
	const D3DXVECTOR4& GetTexUV() const;
	const int32_t GetPhase() const;
	const float GetTimeToActivateSkill() const;
	const float GetTimeLimit() const;
	// スキルが使える状態かどうか
	const bool GetAlreadyUseble() const;
	
	// スキルを使っているかどうか
	const bool GetUseSkillNow() const;
private:	
	void Charge();				// スキルをためる
	void Use(Status& Status);	// スキルを使う
	void PlayAnim();			// トゥーンアニメーション用の設定

	std::vector<std::unique_ptr<IUseSkill>> m_UseSkill;
	D3DXVECTOR4 m_UvParam;

	Billboard::SkillParticle* m_Effect = nullptr;

	int32_t m_Phase = 0;					// フェーズ
	float m_TimeToActivateSkill = 30.0f;	// スキルを有効にする時間
	float m_TimeLimit = 5.0f;				// スキルが使える時間
	float m_Amount = 1.0f;					// 増やす量
	float m_NowTime = 0.0f;
	bool m_AlreadyUseble = false;			// スキルが使える状態かどうか
	bool m_NowUse = false;					// スキルを使用したか
};