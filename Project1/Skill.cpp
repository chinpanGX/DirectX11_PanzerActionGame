/*---------------------------------------------------------------

	[Skill.cpp]
	Author : �o���đ�

	�X�L���Q�[�W��`��

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
	// �N���A
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
	// �X�L���Q�[�W�����߂�
	case 0:
		// �X�L�����L������Ȃ�
		if (!m_AlreadyUseble)
		{
			// �X�L�������߂�
			m_NowTime += m_Time * Fps::Get().deltaTime;
			// ���܂�����L���ɂ���
			if (m_EnableTime < m_NowTime)
			{
				m_AlreadyUseble = true;
				m_NowTime = 0.0f;
			}
		}
		break;
	// �X�L�����g��
	case 1:
		for (size_t i = 0; i < m_UseSkill.size(); ++i)
		{
			m_UseSkill[i]->Use(status);
		}
		m_Phase = 2;
		break;
	// �X�L�����g���Ă����
	case 2:
		m_NowTime++;
		// �T�b�ԗL��
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
	// ���łɃX�L�����g������
	if (m_AlreadyUseble)
	{
		m_Phase = 1;
		Engine::Get().application()->GetScene()->GetGameObject<GameBg::DrawSkill>(ELayer::LAYER_2D_UI)->Reset();
		// �G�t�F�N�g�𔭐�
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
	// �G�t�F�N�g�𔭐�����ʒu���Ԃ̈ʒu�ɂ���
	auto pos = pawn->vehicle().GetBodyTransform().position();
	// �G�t�F�N�g���Đ�����
	auto effect = Engine::Get().application()->GetScene()->AddGameObject<SkillParticle>(ELayer::LAYER_2D_EFFECT);
	effect->transform().position(pos);
}
#pragma endregion �X�L��
