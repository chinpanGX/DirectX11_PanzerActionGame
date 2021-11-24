/*-----------------------------------------------------------

	[Reload.h]
	�����[�h��Ԃ̊Ǘ�
	Author : �o���đ�

------------------------------------------------------------*/
#include "Application.h"
#include "Engine.h"
#include "Command.h"
#include "PlayerUi.h"
#include "Status.h"
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

const bool Reload::finishReload() const
{
	return m_FinishReload;
}
#pragma endregion _�����[�h_

namespace
{
	const int QuickReload = 1;
}

PlayerReload::PlayerReload(const Status & status) : m_Status(status)
{

}

PlayerReload::~PlayerReload()
{
}

void PlayerReload::Init()
{
	// �I�u�W�F�N�g�̎擾
	m_Reload = Engine::Get().application()->GetScene()->GetGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	m_Command = Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
}

void PlayerReload::Begin()
{
	// �ϐ��̏�����
	Reload::BeginReload();

	m_FinishReloadTime = m_Status.reloadTime() * 60.0f; // �����[�h�������鎞��

	m_NowReloadTime = 0.0f;
	m_OnReloadStop = false;
	m_Time = 0.0f;
	m_Count = 0;
}

void PlayerReload::Update()
{
	// �����[�h���������Ă��Ȃ����
	if(Reload::finishReload() == false && m_OnReloadStop == false)
	{
		// ���Ԃ��v��
		m_NowReloadTime += m_Status.addTime();
		
		// �N�C�b�N�����[�h���L����
		bool enableQuickReload = m_Reload->enableQuickReload();
		if (enableQuickReload)
		{
			// ���N���b�N�������
			if (m_Command->GetNowInput(Input::Shot) && m_Count == QuickReload)
			{
				// �����[�h���I������
				Reload::FinishReload();
				m_Reload->SuccessQuickReload();
			}
		}
		// �L������Ȃ��Ƃ�
		else
		{
			// ���N���b�N������ƃ����[�h�X�g�b�v
			if (m_Command->GetNowInput(Input::Shot))
			{				
				if(m_Count == QuickReload)
				{
					// �����[�h���X�g�b�v����
					m_Reload->OnStop();
					m_OnReloadStop = true;
				}
				m_Count++;
			}
		}
		// �����[�h���Ԃ𒴂����Ƃ�
		OverReloadTime();
	}
	// �����[�h�X�g�b�v
	ReloadStop();
}

void PlayerReload::OverReloadTime()
{
	// �����[�h�������Ԃ𒴂�����
	if (m_NowReloadTime >= m_FinishReloadTime)
	{
		// �����[�h����
		Reload::FinishReload();
	}
}

void PlayerReload::ReloadStop()
{
	// �����[�h�X�g�b�v��
	if (m_OnReloadStop == true)
	{
		m_Time += Fps::Get().deltaTime;
		if (m_Time > 3)
		{
			m_OnReloadStop = false;
			m_Reload->OffStop();
		}
	}
}

#pragma region _CpuReload_
CpuReload::CpuReload(const Status & status) : m_Status(status)
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
	m_NowReloadTime = 0.0f;
}

void CpuReload::Update()
{
	// �����[�h���������Ă��Ȃ����
	if (Reload::finishReload() == false)
	{
		const float time = m_Status.reloadTime() * 60.0f; // �����[�h�������鎞��
		m_NowReloadTime += m_Status.addTime();
		// �����[�h�������Ԃ𒴂�����
		if (m_NowReloadTime >= time)
		{
			// �����[�h����
			Reload::FinishReload();
		}
	}
}
#pragma endregion _Cpu�̃����[�h_