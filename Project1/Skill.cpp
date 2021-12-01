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
		Charge();
		break;
	// スキルが溜まって、準備完了
	case 1:
		// 準備完了
		m_AlreadyUseble = true;
		m_NowTime = 0;
		break;
	// スキルを使う
	case 2:
		Use(status);
		break;
	// スキルを使っている間
	case 3:
		m_NowTime += Fps::Get().deltaTime;		
		// エフェクトの位置を戦車に合わせる
		m_Effect->transform().position(position);
		// アニメーションを再生する
		PlayAnim();		
		// ５秒間有効
		if (m_NowTime > m_TimeLimit)
		{
			Reset(status);
		}
		break;
	}
}

void Skill::PlayEffect(Pawn * pawn)
{
	auto pos = pawn->vehicle().bodyTransform().position();
	m_Effect = Engine::Get().application()->GetScene()->AddGameObject<SkillParticle>(ELayer::LAYER_2D_EFFECT);
	m_Effect->transform().position(pos);
}

void Skill::Reset(Status & status)
{
	m_NowUse = false;
	for (size_t i = 0; i < m_UseSkill.size(); ++i)
	{
		m_UseSkill[i]->Reset(status);
	}
	m_NowTime = 0.0f;
	m_Phase = 0;
	if (m_Effect != nullptr)
	{
		m_Effect->OnDestroy();
	}
	m_UvParam = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	
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

/* ゲッター */
const D3DXVECTOR4 & Skill::uv() const
{
	return m_UvParam;
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

const bool Skill::useSkillNow() const
{
	return m_NowUse;
}

#pragma region _privateFunction_
void Skill::Charge()
{
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
}

void Skill::Use(Status & status)
{
	m_AlreadyUseble = false;
	m_NowUse = true;
	for (size_t i = 0; i < m_UseSkill.size(); ++i)
	{
		m_UseSkill[i]->Use(status);
	}
	m_Phase = 3;
}

void Skill::PlayAnim()
{
	m_UvParam.x += 0.01f;
	m_UvParam.y = 0.5f;
}
#pragma endregion _private関数
#pragma endregion スキル
