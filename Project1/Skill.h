/*---------------------------------------------------------------

	[Skill.h]
	Author : 出合翔太

	スキルを管理する

----------------------------------------------------------------*/
#pragma once
#include <memory>
#include <vector>

class SkillParticle;
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
	void Begin(float timeToActivateSkill); 
	void Update(Status& status, const D3DXVECTOR3& position);

	// エフェクトの再生
	void PlayEffect(Pawn* pawn);

	// スキルゲージがたまる時間
	void SetTime(float amount); //　進める時間
	// スキルを使う
	void Enable(Pawn* pawn);
	// リセット
	void Reset(Status& status);	  

	// ゲッター
	const D3DXVECTOR4& uv() const;
	const int32_t phase() const;
	const float timeToActivateSkill() const;
	const float timeLimit() const;
	// スキルが使える状態かどうか
	const bool alreadyUseble() const;
	
	// スキルを使っているかどうか
	const bool useSkillNow() const;
private:	
	void Charge();				// スキルをためる
	void Use(Status& status);	// スキルを使う
	void PlayAnim();			// トゥーンアニメーション用の設定

	std::vector<std::unique_ptr<IUseSkill>> m_UseSkill;
	D3DXVECTOR4 m_UvParam;

	SkillParticle* m_Effect = nullptr;

	int32_t m_Phase = 0;					// フェーズ
	float m_TimeToActivateSkill = 30.0f;	// スキルを有効にする時間
	float m_TimeLimit = 5.0f;				// スキルが使える時間
	float m_Amount = 1.0f;					// 増やす量
	float m_NowTime = 0.0f;
	bool m_AlreadyUseble = false;			// スキルが使える状態かどうか
	bool m_NowUse = false;					// スキルを使用したか
};