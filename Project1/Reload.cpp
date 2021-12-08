/*-----------------------------------------------------------

	[Reload.h]
	リロード状態の管理
	Author : 出合翔太

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
#pragma endregion _リロード_

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
	// オブジェクトの取得
	m_Reload = Engine::Get().application()->GetScene()->GetGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	m_Command = Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
}

void PlayerReload::Begin()
{
	// 変数の初期化
	Reload::BeginReload();

	m_NowReloadTime = 0.0f;
	m_OnReloadStop = false;
	m_Time = 0.0f;
	m_Count = 0;
}

void PlayerReload::Update()
{
	// リロードが完了していない状態
	if(Reload::finishReload() == false && m_OnReloadStop == false)
	{
		// リロード完了する時間
		float finishReloadTime = m_Status.reloadTime() * 60.0f;

		// 時間を計測
		m_NowReloadTime += m_Status.addTime();
		
		// クイックリロードが有効中
		bool enableQuickReload = m_Reload->enableQuickReload();
		if (enableQuickReload)
		{
			// 左クリックをすると
			if (m_Command->GetNowInput(InputCode::Shot) && m_Count == QuickReload)
			{
				// リロードが終了する
				Reload::FinishReload();
				m_Reload->SuccessQuickReload();
			}
		}
		// 有効じゃないとき
		else
		{
			// 左クリックをするとリロードストップ
			if (m_Command->GetNowInput(InputCode::Shot))
			{				
				if(m_Count == QuickReload)
				{
					// リロードがストップする
					m_Reload->Stop();
					m_OnReloadStop = true;
				}
				m_Count++;
			}
		}
		// リロード時間を超えたとき
		if (m_NowReloadTime >= finishReloadTime)
		{
			// リロード完了
			Reload::FinishReload();
		}
	}
	// リロードストップ
	ReloadStop();
}

void PlayerReload::ReloadStop()
{
	// リロードストップ中
	if (m_OnReloadStop == true)
	{
		// ストップする時間
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
#pragma endregion _Cpuのリロード_