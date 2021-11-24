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
	count = 0;
}

void PlayerReload::Update()
{
	// リロードが完了していない状態
	if(Reload::finishReload() == false && m_OnReloadStop == false)
	{
		// 時間を計測
		const float time = m_Status.reloadTime() * 60.0f; // リロード完了する時間
		m_NowReloadTime += m_Status.addTime();
		
		// クイックリロードが有効中
		bool enableQuickReload = m_Reload->enableQuickReload();
		if (enableQuickReload)
		{
			// 左クリックをすると
			bool isInput = m_Command->GetNowInput(Input::Shot);
			if (isInput)
			{
				// リロードが終了する
				Reload::FinishReload();
			}
		}
		// 有効じゃないとき
		else
		{
			// 左クリックをするとリロードストップ
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

					// リロードが終了する
					m_Reload->OnStop();
					m_OnReloadStop = true;
				}
			}
		}
		// リロード完了時間を超えたら
		if (m_NowReloadTime >= time)
		{
			// リロード完了
			Reload::FinishReload();
		}
	}

	// リロードストップ中
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
