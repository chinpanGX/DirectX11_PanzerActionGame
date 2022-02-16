/*-----------------------------------------------------------

	[Reload.h]
	リロード状態の管理
	Author : 出合翔太

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
#pragma endregion _リロード_

PlayerReload::PlayerReload()
{

}

PlayerReload::~PlayerReload()
{
}

void PlayerReload::Init()
{
	// オブジェクトの取得
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_Reload = Engine::Get().GetApplication()->GetScene()->GetGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	m_Command = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
}

void PlayerReload::Begin()
{
	// 変数の初期化
	Reload::BeginReload();
	m_NowReloadTime = 0.0f;
	// 今スキルを使っているかどうか
	m_UseSkill = m_Player->GetVehicle().GetSkill().GetUseSkillNow();
	m_FinishReloadTime = m_Player->GetVehicle().GetStatus().GetReloadTime() * 60.0f;
	m_OnReloadStop = false;
	m_Time = 0.0f;
	m_Count = 0;
}

void PlayerReload::Update()
{
	// リロードが完了していない状態
	if(Reload::GetFinishReload() == false && m_OnReloadStop == false)
	{
		// 開始時点でスキルまだ使っていない
		if (m_UseSkill == false)
		{
			// 途中でスキルを使う可能性があるので、更新してみる
			m_UseSkill = m_Player->GetVehicle().GetSkill().GetUseSkillNow();
			m_FinishReloadTime = m_Player->GetVehicle().GetStatus().GetReloadTime() * 60.0f;
		}		

		// 時間を計測
		m_NowReloadTime += m_Player->GetVehicle().GetStatus().GetAddTime();
		
		// クイックリロードが有効中
		bool enableQuickReload = m_Reload->GetEnableQuickReload();
		if (enableQuickReload)
		{
			// 左クリックをすると
			if (m_Command->GetNowInput(InputCode::Shot) && m_Count == m_EnableQuickReloadCount)
			{
				// リロードが終了する
				Reload::FinishReload();
				m_Reload->SuccessQuickReload();
				Engine::Get().GetResource()->AudioPlay("Reload");
			}
		}
		// 有効じゃないとき
		else
		{
			// 左クリックをするとリロードストップ
			if (m_Command->GetNowInput(InputCode::Shot))
			{				
				// クイックリロードが有効なカウント && スキルを使っていないとき
				if(m_Count == m_EnableQuickReloadCount && m_UseSkill == false)
				{					
					m_Reload->SetEnableQuickReload(false);
					// リロードがストップする
					m_Reload->Stop();
					m_OnReloadStop = true;
				}
				// クリックしたカウントを数えておく
				m_Count++;
			}
		}
		// リロード時間を超えたとき
		if (m_NowReloadTime >= m_FinishReloadTime)
		{
			// リロード完了
			Reload::FinishReload();
		}
	}
	else
	{
		// リロードストップ
		ReloadStop();
	}
}

void PlayerReload::ReloadStop()
{
	// リロードストップ中
	if (m_OnReloadStop == true)
	{
		// ストップする時間
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
	// リロードの時間⇒4秒固定
	const float ReloadTime = 4.0f;
	m_FinishReloadTime = ReloadTime * 60.0f;
	m_NowReloadTime = 0.0f;
}

void CpuReload::Update()
{
	// リロードが完了していない状態
	if (Reload::GetFinishReload() == false)
	{
		m_NowReloadTime += 1.0f;
		// リロード完了時間を超えたら
		if (m_NowReloadTime >= m_FinishReloadTime)
		{
			// リロード完了
			Reload::FinishReload();
		}
	}
}
#pragma endregion _Cpuのリロード_