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

void Skill::SetSkill(std::unique_ptr<IUseSkill> UseSkill)
{
	m_UseSkill.emplace_back(std::move(UseSkill));
}

void Skill::Begin(float TimeToActivateSkill)
{
	m_TimeToActivateSkill = TimeToActivateSkill;
}

void Skill::Update(Status& Status, const D3DXVECTOR3& Position)
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
		Use(Status);
		break;
	// スキルを使っている間
	case 3:
		m_NowTime += Fps::Get().deltaTime;		
		if (m_Effect)
		{
			// エフェクトの位置を戦車に合わせる
			m_Effect->GetTransform().SetPosition(Position);
			// アニメーションを再生する
			PlayAnim();
		}
		// ５秒間有効
		if (m_NowTime > m_TimeLimit)
		{
			Reset(Status);
		}
		break;
	}
}

void Skill::PlayEffect(Pawn * Pawn)
{
	auto pos = Pawn->GetVehicle().GetBodyTransform().GetPosition();
	m_Effect = Engine::Get().GetApplication()->GetScene()->AddGameObject<Billboard::SkillParticle>(ELayer::LAYER_2D_EFFECT);
	m_Effect->GetTransform().SetPosition(pos);
}

void Skill::Reset(Status & Status)
{
	m_AlreadyUseble = false;
	m_NowUse = false;
	// スキルのリセット
	for (size_t i = 0; i < m_UseSkill.size(); ++i)
	{
		m_UseSkill[i]->Reset(Status);
	}
	m_NowTime = 0.0f;
	m_Phase = 0;
	// エフェクトを消す
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

void Skill::Enable(Pawn* Pawn)
{
	// すでにスキルが使える状態
	if (m_AlreadyUseble)
	{
		m_Phase = 2;	
	}
}

/* ゲッター */
const D3DXVECTOR4 & Skill::GetTexUV() const
{
	return m_UvParam;
}

const int32_t Skill::GetPhase() const
{
	return m_Phase;
}

const float Skill::GetTimeToActivateSkill() const
{
	return m_TimeToActivateSkill;
}

const float Skill::GetTimeLimit() const
{
	return m_TimeLimit;
}

const bool Skill::GetAlreadyUseble() const
{
	return m_AlreadyUseble;
}

const bool Skill::GetUseSkillNow() const
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

void Skill::Use(Status & Status)
{
	m_AlreadyUseble = false;
	m_NowUse = true;
	for (size_t i = 0; i < m_UseSkill.size(); ++i)
	{
		m_UseSkill[i]->Use(Status);
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
