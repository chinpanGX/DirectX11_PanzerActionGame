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
#include "SkillParticle.h"

#pragma region Skill_method
Skill::Skill()
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

void Skill::Begin(float timeToActivateSkill)
{
	m_TimeToActivateSkill = timeToActivateSkill;
}

void Skill::Update(Status& status, const D3DXVECTOR3& position)
{
	switch (m_Phase)
	{
	// �X�L���Q�[�W�����߂�
	case 0:
		// �X�L�����L������Ȃ�
		if (!m_AlreadyUseble)
		{
			// �X�L�������߂�
			m_NowTime += m_Amount * Fps::Get().deltaTime;
			// ���܂�����L���ɂ���
			if (m_NowTime > m_TimeToActivateSkill)
			{
				m_Phase = 1;
			}
		}
		break;
	// �X�L�������܂��āA��������
	case 1:
		// ��������
		m_AlreadyUseble = true;
		m_NowTime = 0;
		break;
	// �X�L�����g��
	case 2:
		m_AlreadyUseble = false;
		m_Use = true;
		for (size_t i = 0; i < m_UseSkill.size(); ++i)
		{
			m_UseSkill[i]->Use(status);
		}
		m_Phase = 3;
		break;
	// �X�L�����g���Ă����
	case 3:
		m_NowTime += Fps::Get().deltaTime;
		if (m_SkillEffect)
		{
			m_SkillEffect->transform().position(position);
		}
		// �T�b�ԗL��
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
	// ���łɃX�L�����g������
	if (m_AlreadyUseble)
	{
		m_Phase = 2;	
	}
}

void Skill::PlayEffect(Pawn* pawn)
{
	// �G�t�F�N�g�𔭐�����ʒu���Ԃ̈ʒu�ɂ���
	auto pos = pawn->vehicle().bodyTransform().position();
	// �G�t�F�N�g���Đ�����
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
#pragma endregion �X�L��
