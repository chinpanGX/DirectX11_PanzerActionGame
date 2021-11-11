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
#include "DrawSkill.h"
#include "SkillParticle.h"

#pragma region Skill_method
Skill::Skill() : m_AlreadyUseble(false)
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

void Skill::Begin(float enableTime)
{
	m_EnableTime = enableTime;
}

void Skill::Update(Status& status)
{
	switch (m_Phase)
	{
	// スキルゲージをためる
	case 0:
		// スキルが有効じゃない
		if (!m_AlreadyUseble)
		{
			// スキルをためる
			m_NowTime += m_Time * Fps::Get().deltaTime;
			// たまったら有効にする
			if (m_EnableTime < m_NowTime)
			{
				m_AlreadyUseble = true;
				m_NowTime = 0.0f;
			}
		}
		break;
	// スキルを使う
	case 1:
		for (size_t i = 0; i < m_UseSkill.size(); ++i)
		{
			m_UseSkill[i]->Use(status);
		}
		m_Phase = 2;
		break;
	// スキルを使っている間
	case 2:
		m_NowTime++;
		// ５秒間有効
		if (m_NowTime > 5.0f)
		{
			for (size_t i = 0; i < m_UseSkill.size(); ++i)
			{
				m_UseSkill[i]->Reset(status);
			}
			m_AlreadyUseble = false;
			m_NowTime = 0.0f;
		}
		break;
	}
}

void Skill::SetTime(float time)
{
	m_Time = time;
}

void Skill::Enable(Pawn* pawn)
{
	// すでにスキルが使える状態
	if (m_AlreadyUseble)
	{
		m_Phase = 1;
		Engine::Get().application()->GetScene()->GetGameObject<GameBg::DrawSkill>(ELayer::LAYER_2D_UI)->Reset();
		// エフェクトを発生
		PlayEffect(pawn);
	}
}

const int32_t Skill::GetPhase() const
{
	return m_Phase;
}

const float Skill::GetEnableTime() const
{
	return m_EnableTime;
}

const bool Skill::GetAlreadyUseble() const
{
	return m_AlreadyUseble;
}

// private_Function
void Skill::PlayEffect(Pawn* pawn)
{
	// エフェクトを発生する位置を戦車の位置にする
	auto pos = pawn->vehicle().GetBodyTransform().position();
	// エフェクトを再生する
	auto effect = Engine::Get().application()->GetScene()->AddGameObject<SkillParticle>(ELayer::LAYER_2D_EFFECT);
	effect->transform().position(pos);
}
#pragma endregion スキル
