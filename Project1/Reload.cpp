/*-----------------------------------------------------------

	[Reload.h]
	�����[�h��Ԃ̊Ǘ�
	Author : �o���đ�

------------------------------------------------------------*/
#include "Status.h"
#include "Reload.h"

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

PlayerReload::PlayerReload(const Status & status) : m_Status(status)
{

}

PlayerReload::~PlayerReload()
{
}

void PlayerReload::Begin()
{
	Reload::BeginReload();
	m_NowReloadTime = 0.0f;
}

void PlayerReload::Update()
{
	// �����[�h���������Ă��Ȃ����
	if(Reload::finishReload() == false)
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


CpuReload::CpuReload(const Status & status) : m_Status(status)
{

}

CpuReload::~CpuReload()
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
