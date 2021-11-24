/*-----------------------------------------------------------

	[PlayerUi.cpp]
	Author : 出合翔太
	プレイヤー側に表示するUI

------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "Resource.h"
#include "Reload.h"
#include "Fps.h"
#include "Pause.h"
#include "Skill.h"
#include "Status.h"
#include "Vehicle.h"
#include "Pivot.h"
#include "Player.h"
#include "GameCamera.h"
#include "PlayerUi.h"

namespace PlayerUi
{
#pragma region DrawSkill_method
	DrawSkill::DrawSkill()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
	}

	DrawSkill::~DrawSkill()
	{
	}

	void DrawSkill::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);

		// ゲージを増加する量を計算
		float t = m_Player->vehicle().skill().timeToActivateSkill();
		m_Add = m_MaxDrawSize / t * Fps::Get().deltaTime;
	}

	void DrawSkill::Update()
	{
		if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }

		// まだスキルが使える状態じゃない
		if (m_Player->vehicle().skill().alreadyUseble() == false)
		{
			// ゲージを増やす
			m_DrawSize += m_Add;
		}
	}

	void DrawSkill::Event()
	{
	}

	void DrawSkill::Draw()
	{
		D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 940.0f);
		m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));
		m_Render->Draw(m_DrawSize, pos, D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f));
	}

	void DrawSkill::Reset()
	{
		// 描画サイズを０にする
		m_DrawSize = 0.0f;
	}
#pragma endregion スキルゲージを描画する

#pragma region _Reload_
	Reload::Reload()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
		m_Center = static_cast<float>(SCREEN_WIDTH / 2);
		m_GagePosition = D3DXVECTOR2((m_Center - 250.0f), 750.0f);		
		m_QuickRangePosition = D3DXVECTOR2((m_Center- 50.0f), 750.0f);
		m_IconPosition = D3DXVECTOR2((m_Center - 250.0f), 750.0f);
	}

	Reload::~Reload()
	{
	}

	void Reload::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		// リロード時間の取得
		float t = m_Player->vehicle().status().reloadTime();
		// 増える量を計算
		m_Amount = m_MaxSize / t * Fps::Get().deltaTime;
		m_NowStop = false;
	}

	void Reload::Update()
	{
		if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE)->NowPausing()) { return; }
		
		// リロード中
		if (m_NowReload && m_NowStop == false)
		{
				m_NowGage += m_Amount;
				m_IconPosition.x += m_Amount;
			// クイックリロードの範囲内ならクイックリロードを有効にする
			if (m_IconPosition.x - 25.0f > m_QuickRangePosition.x - 50.0f && m_IconPosition.x + 25.0f < m_QuickRangePosition.x + 50.0f)
			{
				m_EnableQuickReload = true;
			}
			else
			{
				m_EnableQuickReload = false;
			}

			// リロード完了
			if (m_Player->reload().finishReload())
			{
				m_EnableQuickReload = false;
				m_NowReload = false;
				m_IconPosition.x = m_Center - 250.0f;
			}			
		}
		// リロード終了
		else if(m_NowReload == false && m_NowStop == false)
		{			
			m_NowGage = 0.0f;		
		}
	}

	void Reload::Event()
	{
	}

	void Reload::Draw()
	{
		// リロード中のときに描画
		if (m_NowReload)
		{
			// 背景ゲージ
			m_Render->Draw(m_MaxSize, m_GagePosition, D3DXVECTOR4(0.0f, 0.35f, 0.55f, 0.35f));

			// 高速リロード有効範囲のマーク
			m_Render->Draw(100.0f, m_QuickRangePosition);

			// ゲージ
			m_Render->Draw(m_NowGage, m_GagePosition, D3DXVECTOR4(1.0f, 0.5f, 0.7f, 0.5f));

			// 有効かどうかで色を変える
			if (m_EnableQuickReload)
			{
				m_IconColor = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0);
			}
			else
			{
				m_IconColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0);
			}
			
			// アイコン 
			m_Render->Draw(50.0f, m_IconPosition, m_IconColor);
		}
	}
	// リロード開始
	void Reload::BeginReload()
	{
		m_NowReload = true;
	}

	void Reload::OnStop()
	{
		m_NowStop = true;
	}

	void Reload::OffStop()
	{
		m_NowStop = false;
	}

	// リロードが有効かどうか
	const bool Reload::enableQuickReload() const
	{
		return m_EnableQuickReload;
	}
#pragma endregion _リロードゲージ_

#pragma region _HPGage_
	Hp::Hp()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
	}

	Hp::~Hp()
	{
	}

	void Hp::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		// 実際のHPとMAXのサイズから描画する比率を求める
		m_DrawRatio = m_MaxDrawSize / m_Player->vehicle().status().maxHp();
	}

	void Hp::Update()
	{
		// 現在のHP
		m_NowHp = m_Player->vehicle().status().hp();
		// 更新前のHPと比較する
		if (m_OldHp != m_NowHp)
		{
			// 一致しなかったら、描画サイズを計算して前のHPを更新する

			// 現在のHP * 求めた比率
			m_DrawSize = m_NowHp * m_DrawRatio;
			m_OldHp = m_NowHp;
		}
	}

	void Hp::Event()
	{
	}

	void Hp::Draw()
	{
		// 描画位置を設定
		D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 900.0f);

		// MAX状態のHPバー
		m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));

		// 現在のHPバー
		m_Render->Draw(m_DrawSize, pos, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	}
#pragma endregion Hpゲージ
}
