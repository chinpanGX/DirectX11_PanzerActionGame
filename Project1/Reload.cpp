/*-----------------------------------------------------------

	[Reload.h]
	�����[�h��Ԃ̊Ǘ�
	Author : �o���đ�

------------------------------------------------------------*/
#include "Application.h"
#include "Resource.h"
#include "Engine.h"
#include "Command.h"
#include "PlayerUi.h"
#include "Status.h"
#include "Vehicle.h"
#include "Player.h"
#include "Skill.h"
#include "Reload.h"
#include "Fps.h"

#pragma region _Reload_
void Reload::BeginReload()
{
	m_FinishReload = false;
}

void Reload::FinishReload()
{
	m_FinishReload = true;
}

const bool Reload::GetFinishReload() const
{
	return m_FinishReload;
}
#pragma endregion _�����[�h_

PlayerReload::PlayerReload()
{

}

PlayerReload::~PlayerReload()
{
}

void PlayerReload::Init()
{
	// �I�u�W�F�N�g�̎擾
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_Reload = Engine::Get().GetApplication()->GetScene()->GetGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	m_Command = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
}

void PlayerReload::Begin()
{
	// �ϐ��̏�����
	Reload::BeginReload();
	m_NowReloadTime = 0.0f;
	// ���X�L�����g���Ă��邩�ǂ���
	m_UseSkill = m_Player->GetVehicle().GetSkill().GetUseSkillNow();
	m_FinishReloadTime = m_Player->GetVehicle().GetStatus().GetReloadTime() * 60.0f;
	m_OnReloadStop = false;
	m_Time = 0.0f;
	m_Count = 0;
}

void PlayerReload::Update()
{
	// �����[�h���������Ă��Ȃ����
	if(Reload::GetFinishReload() == false && m_OnReloadStop == false)
	{
		// �J�n���_�ŃX�L���܂��g���Ă��Ȃ�
		if (m_UseSkill == false)
		{
			// �r���ŃX�L�����g���\��������̂ŁA�X�V���Ă݂�
			m_UseSkill = m_Player->GetVehicle().GetSkill().GetUseSkillNow();
			m_FinishReloadTime = m_Player->GetVehicle().GetStatus().GetReloadTime() * 60.0f;
		}		

		// ���Ԃ��v��
		m_NowReloadTime += m_Player->GetVehicle().GetStatus().GetAddTime();
		
		// �N�C�b�N�����[�h���L����
		bool enableQuickReload = m_Reload->GetEnableQuickReload();
		if (enableQuickReload)
		{
			// ���N���b�N�������
			if (m_Command->GetNowInput(InputCode::Shot) && m_Count == m_EnableQuickReloadCount)
			{
				// �����[�h���I������
				Reload::FinishReload();
				m_Reload->SuccessQuickReload();
				Engine::Get().GetResource()->AudioPlay("Reload");
			}
		}
		// �L������Ȃ��Ƃ�
		else
		{
			// ���N���b�N������ƃ����[�h�X�g�b�v
			if (m_Command->GetNowInput(InputCode::Shot))
			{				
				// �N�C�b�N�����[�h���L���ȃJ�E���g && �X�L�����g���Ă��Ȃ��Ƃ�
				if(m_Count == m_EnableQuickReloadCount && m_UseSkill == false)
				{					
					m_Reload->SetEnableQuickReload(false);
					// �����[�h���X�g�b�v����
					m_Reload->Stop();
					m_OnReloadStop = true;
				}
				// �N���b�N�����J�E���g�𐔂��Ă���
				m_Count++;
			}
		}
		// �����[�h���Ԃ𒴂����Ƃ�
		if (m_NowReloadTime >= m_FinishReloadTime)
		{
			// �����[�h����
			Reload::FinishReload();
		}
	}
	else
	{
		// �����[�h�X�g�b�v
		ReloadStop();
	}
}

void PlayerReload::ReloadStop()
{
	// �����[�h�X�g�b�v��
	if (m_OnReloadStop == true)
	{
		// �X�g�b�v���鎞��
		float stopTime = 3.0f;
		m_Time += Fps::Get().deltaTime;
		if (m_Time > stopTime)
		{
			m_OnReloadStop = false;
			m_Reload->Restart();
		}
	}
}

#pragma region _CpuReload_
CpuReload::CpuReload()
{
}

CpuReload::~CpuReload()
{
}

void CpuReload::Init()
{
}

void CpuReload::Begin()
{
	Reload::BeginReload();
	// �����[�h�̎��ԁ�4�b�Œ�
	const float ReloadTime = 4.0f;
	m_FinishReloadTime = ReloadTime * 60.0f;
	m_NowReloadTime = 0.0f;
}

void CpuReload::Update()
{
	// �����[�h���������Ă��Ȃ����
	if (Reload::GetFinishReload() == false)
	{
		m_NowReloadTime += 1.0f;
		// �����[�h�������Ԃ𒴂�����
		if (m_NowReloadTime >= m_FinishReloadTime)
		{
			// �����[�h����
			Reload::FinishReload();
		}
	}
}
#pragma endregion _Cpu�̃����[�h_