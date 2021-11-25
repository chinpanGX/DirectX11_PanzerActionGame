/*---------------------------------------------------------------

	[Skill.cpp]
	Author : 出合翔太

	スキルゲージを描画

----------------------------------------------------------------*/
#include "myLib.h"
#include "Status.h"
#include "IUseSkill.h"
#include "Pawn.h"
#include "Vehicle.h"
#include "Skill.h"
#include "Fps.h"
#include "Engine.h"
#include "Application.h"
#include "SkillParticle.h"

#pragma region Skill_method
Skill::Skill()
{
}

Skill::~Skill()
{
	// クリア
	m_UseSkill.clear();
}

void Skill::SetSkill(std::unique_ptr<IUseSkill> useSkill)
{
	m_UseSkill.emplace_back(std::move(useSkill));
}

void Skill::Begin(float timeToActivateSkill)
{
	m_TimeToActivateSkill = timeToActivateSkill;
}

void Skill::Update(Status& status, const D3DXVECTOR3& position)
{
	switch (m_Phase)
	{
	// スキルゲージをためる
	case 0:
		// スキルが有効じゃない
		if (!m_AlreadyUseble)
		{
			// スキルをためる
			m_NowTime += m_Amount * Fps::Get().deltaTime;
			// たまったら有効にする
			if (m_NowTime > m_TimeToActivateSkill)
			{
				m_Phase = 1;
			}
		}
		break;
	// スキルが溜まって、準備完了
	case 1:
		// 準備完了
		m_AlreadyUseble = true;
		m_NowTime = 0;
		break;
	// スキルを使う
	case 2:
		m_AlreadyUseble = false;
		m_Use = true;
		for (size_t i = 0; i < m_UseSkill.size(); ++i)
		{
			m_UseSkill[i]->Use(status);
		}
		m_Phase = 3;
		break;
	// スキルを使っている間
	case 3:
		m_NowTime += Fps::Get().deltaTime;
		if (m_SkillEffect)
		{
			m_SkillEffect->transform().position(position);
		}
		// ５秒間有効
		if (m_NowTime > m_TimeLimit)
		{
			Reset(status);
		}
		break;
	}
}

void Skill::Reset(Status & status)
{
	m_Use = false;
	for (size_t i = 0; i < m_UseSkill.size(); ++i)
	{
		m_UseSkill[i]->Reset(status);
	}
	m_NowTime = 0.0f;
	m_Phase = 0;
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->OnDestroy();
		m_SkillEffect = nullptr;
	}
}

void Skill::SetTime(float amount)
{
	m_Amount = amount;
}

void Skill::Enable(Pawn* pawn)
{
	// すでにスキルが使える状態
	if (m_AlreadyUseble)
	{
		m_Phase = 2;	
	}
}

void Skill::PlayEffect(Pawn* pawn)
{
	// エフェクトを発生する位置を戦車の位置にする
	auto pos = pawn->vehicle().bodyTransform().position();
	// エフェクトを再生する
	m_SkillEffect = Engine::Get().application()->GetScene()->AddGameObject<SkillParticle>(ELayer::LAYER_2D_EFFECT);
	m_SkillEffect->transform().position(pos);
}

const int32_t Skill::phase() const
{
	return m_Phase;
}

const float Skill::timeToActivateSkill() const
{
	return m_TimeToActivateSkill;
}

const float Skill::timeLimit() const
{
	return m_TimeLimit;
}

const bool Skill::alreadyUseble() const
{
	return m_AlreadyUseble;
}

const bool Skill::Use() const
{
	return m_Use;
}
#pragma endregion スキル
