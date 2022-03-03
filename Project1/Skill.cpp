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
	// �X�L���Q�[�W�����߂�
	case 0:
		Charge();
		break;
	// �X�L�������܂��āA��������
	case 1:
		// ��������
		m_AlreadyUseble = true;
		m_NowTime = 0;
		break;
	// �X�L�����g��
	case 2:
		Use(Status);
		break;
	// �X�L�����g���Ă����
	case 3:
		m_NowTime += Fps::Get().deltaTime;		
		if (m_Effect)
		{
			// �G�t�F�N�g�̈ʒu���Ԃɍ��킹��
			m_Effect->GetTransform().SetPosition(Position);
			// �A�j���[�V�������Đ�����
			PlayAnim();
		}
		// �T�b�ԗL��
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
	// �X�L���̃��Z�b�g
	for (size_t i = 0; i < m_UseSkill.size(); ++i)
	{
		m_UseSkill[i]->Reset(Status);
	}
	m_NowTime = 0.0f;
	m_Phase = 0;
	// �G�t�F�N�g������
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
	// ���łɃX�L�����g������
	if (m_AlreadyUseble)
	{
		m_Phase = 2;	
	}
}

/* �Q�b�^�[ */
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
#pragma endregion _private�֐�
#pragma endregion �X�L��
