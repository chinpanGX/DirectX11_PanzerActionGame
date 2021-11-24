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

namespace
{
	int count = 0;
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
	count = 0;
}

void PlayerReload::Update()
{
	// �����[�h���������Ă��Ȃ����
	if(Reload::finishReload() == false && m_OnReloadStop == false)
	{
		// ���Ԃ��v��
		const float time = m_Status.reloadTime() * 60.0f; // �����[�h�������鎞��
		m_NowReloadTime += m_Status.addTime();
		
		// �N�C�b�N�����[�h���L����
		bool enableQuickReload = m_Reload->enableQuickReload();
		if (enableQuickReload)
		{
			// ���N���b�N�������
			bool isInput = m_Command->GetNowInput(Input::Shot);
			if (isInput)
			{
				// �����[�h���I������
				Reload::FinishReload();
			}
		}
		// �L������Ȃ��Ƃ�
		else
		{
			// ���N���b�N������ƃ����[�h�X�g�b�v
			bool isInput = m_Command->GetNowInput(Input::Shot);
			if (isInput)
			{
				if (count == 0)
				{
					m_OnReloadStop = false;
					count++;
				}
				else
				{

					// �����[�h���I������
					m_Reload->OnStop();
					m_OnReloadStop = true;
				}
			}
		}
		// �����[�h�������Ԃ𒴂�����
		if (m_NowReloadTime >= time)
		{
			// �����[�h����
			Reload::FinishReload();
		}
	}

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
