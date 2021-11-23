/*-----------------------------------------------------------

	[Reload.h]
	リロード状態の管理
	Author : 出合翔太

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
	// リロードが完了していない状態
	if(Reload::finishReload() == false)
	{
		const float time = m_Status.reloadTime() * 60.0f; // リロード完了する時間
		m_NowReloadTime += m_Status.addTime();
		// リロード完了時間を超えたら
		if (m_NowReloadTime >= time)
		{
			// リロード完了
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
	// リロードが完了していない状態
	if (Reload::finishReload() == false)
	{
		const float time = m_Status.reloadTime() * 60.0f; // リロード完了する時間
		m_NowReloadTime += m_Status.addTime();
		// リロード完了時間を超えたら
		if (m_NowReloadTime >= time)
		{
			// リロード完了
			Reload::FinishReload();
		}
	}
}
