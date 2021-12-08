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
		// �����[�h�������鎞��
		float finishReloadTime = m_Status.reloadTime() * 60.0f;

		// ���Ԃ��v��
		m_NowReloadTime += m_Status.addTime();
		
		// �N�C�b�N�����[�h���L����
		bool enableQuickReload = m_Reload->enableQuickReload();
		if (enableQuickReload)
		{
			// ���N���b�N�������
			if (m_Command->GetNowInput(InputCode::Shot) && m_Count == QuickReload)
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
			if (m_Command->GetNowInput(InputCode::Shot))
			{				
				if(m_Count == QuickReload)
				{
					// �����[�h���X�g�b�v����
					m_Reload->Stop();
					m_OnReloadStop = true;
				}
				m_Count++;
			}
		}
		// �����[�h���Ԃ𒴂����Ƃ�
		if (m_NowReloadTime >= finishReloadTime)
		{
			// �����[�h����
			Reload::FinishReload();
		}
	}
	// �����[�h�X�g�b�v
	ReloadStop();
}

void PlayerReload::ReloadStop()
{
	// �����[�h�X�g�b�v��
	if (m_OnReloadStop == true)
	{
		// �X�g�b�v���鎞��
		float stopTime = 3.0;
		m_Time += Fps::Get().deltaTime;
		if (m_Time > stopTime)
		{
			m_OnReloadStop = false;
			m_Reload->Restart();
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