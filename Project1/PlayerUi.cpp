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
		m_Pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// 増加する量
		float t = m_Player->vehicle().skill().timeToActivateSkill();
		m_AddAmount = m_MaxDrawSize / t * Fps::Get().deltaTime;
		
		// 減らす量
		m_TimeLimit = m_Player->vehicle().skill().timeLimit();
		m_SubAmount = m_MaxDrawSize / m_TimeLimit * Fps::Get().deltaTime + 0.2f;

		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
		m_Time = 0.0f;
	}

	void DrawSkill::Update()
	{
		if (m_Pause->NowPausing()) { return; }
		
		// スキルを使ったかどうか
		m_Use = m_Player->vehicle().skill().useSkillNow();
		// ゲージを増やす
		AddGage();
		Use();
	}

	void DrawSkill::Event()
	{
	}

	void DrawSkill::Draw()
	{
		// ゲージの背景
		D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 940.0f);
		m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));

		// 実際のゲージ
		m_Render->Draw(m_DrawSize, pos, m_Color);
	}

#pragma region _privateFunction_
	void DrawSkill::AddGage()
	{
		// まだスキルが使える状態じゃない
		if (m_Player->vehicle().skill().alreadyUseble() == false)
		{
			// ゲージを増やす
			m_DrawSize += m_AddAmount;
			// ゲージの量の調整
			if (m_DrawSize > m_MaxDrawSize)
			{
				m_DrawSize = m_MaxDrawSize;
			}
		}
	}

	void DrawSkill::Use()
	{
		// スキルを使っている状態
		if (m_Use)
		{
			// 色の変更
			m_Color = D3DXVECTOR4(0.7f, 0.1f, 1.0f, 1.0f);

			// 時間計測
			m_Time += Fps::Get().deltaTime;

			// ゲージを減らす
			m_DrawSize -= m_SubAmount;

			// ゲージ量の調整
			if (0.0f > m_DrawSize)
			{
				m_DrawSize = 0.0f;
			}
			
			// ゲージリセット
			if (m_Time > m_TimeLimit)
			{
				Reset();
			}
		}
	}

	void DrawSkill::Reset()
	{
		// 描画サイズを0にする
		m_DrawSize = 0.0f;
		m_Time = 0.0f;
		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
	}
#pragma endregion _private関数_
#pragma endregion スキルゲージを描画する

#pragma region _Reload_
	Reload::Reload()
	{
		m_QuickReload = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Gage");
		m_ReloadIcon = std::make_unique<Renderer2D>(*Engine::Get().graphics(), *Engine::Get().resource(), "Reload");
		m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
		float center = static_cast<float>(SCREEN_WIDTH / 2);
		m_GagePosition = D3DXVECTOR2((center - 300.0f), 750.0f);		
		m_QuickRangePosition = D3DXVECTOR2(center, 750.0f);
		m_IconPosition = D3DXVECTOR2((center - 300.0f), 750.0f);
	}

	Reload::~Reload()
	{
	}

	void Reload::Begin()
	{
		m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// リロード時間の取得
		float t = m_Player->vehicle().status().reloadTime();
		// 増える量を計算
		m_Amount = m_MaxSize / t * Fps::Get().deltaTime;
		
		// 変数の初期化
		m_NowStop = false;
		m_Time = 0.0f;
	}

	void Reload::Update()
	{
		if (m_Pause->NowPausing()) { return; }
		
		// リロード中
		if (m_NowReload && m_NowStop == false)
		{
			// リロード中の処理
			NowReload();
			// リロード完了
			Finish();
		}
		// リロード終了
		else if(m_NowReload == false && m_NowStop == false)
		{
			// 描画の切り替え
			SwitchNotDraw();			
		}

	}

	void Reload::Event()
	{
	}

	void Reload::Draw()
	{
		// リロード中のときに描画
		if (m_Draw)
		{
			auto color = D3DXVECTOR4(0.0f, 0.35f, 0.55f, 0.35f);
			// 背景ゲージ
			m_Render->Draw(m_MaxSize, m_GagePosition, 15.0f, "Gage", color);

			if (m_DrawQuickGage)
			{
				color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.7f);				
				auto size = D3DXVECTOR2(160.0f, 30.0f);
				// 高速リロード有効範囲のマーク
				m_QuickReload->Draw(m_QuickRangePosition, size);
				//m_Render->Draw(150.0f, m_QuickRangePosition, 15.0f, "Gage", color);
			}

			color = D3DXVECTOR4(1.0f, 0.5f, 0.7f, 0.5f);
			// ゲージ
			m_Render->Draw(m_NowGage, m_GagePosition, 15.0f, "Gage", color);

			// アイコンの描画
			DrawIcon();
		}
	}

	// リロード開始
	void Reload::BeginReload()
	{
		m_NowReload = true;
		m_Time = 0.0f;
		m_IconPosition.x = m_GagePosition.x;
		m_NowGage = 0.0f;
		// ゲージの描画開始
		m_Draw = true;
		m_DrawQuickGage = true;
	}

	void Reload::Stop()
	{
		m_NowStop = true;
		m_DrawQuickGage = false;
	}

	void Reload::Restart()
	{
		m_NowStop = false;
	}

	// クイックリロード成功
	void Reload::SuccessQuickReload()
	{
		m_EnableQuickReload = false;
		m_NowReload = false;
		m_IconPosition.x = m_GagePosition.x + m_MaxSize;
		m_NowGage = m_MaxSize;
	}

	// リロードが有効かどうか
	const bool Reload::enableQuickReload() const
	{
		return m_EnableQuickReload;
	}

#pragma region _privateFunction_
	// リロード優の処理
	void Reload::NowReload()
	{
		// ゲージをとアイコンの更新
		m_NowGage += m_Amount;
		m_IconPosition.x += m_Amount;

		// クイックリロードの範囲内ならクイックリロードを有効にする
		if (m_IconPosition.x - 40.0f > m_QuickRangePosition.x - 80.0f && m_IconPosition.x + 40.0f < m_QuickRangePosition.x + 80.0f)
		{
			m_EnableQuickReload = true;
		}
		else
		{
			m_EnableQuickReload = false;
		}
	}
	// リロード完了
	void Reload::Finish()
	{
		if (m_Player->reload().finishReload())
		{
			m_EnableQuickReload = false;
			m_NowReload = false;
		}
	}

	// 非表示にする
	void Reload::SwitchNotDraw()
	{
		// リロードが完了したあと、表示する時間を設定
		float drawTime = 0.1f;

		// 時間更新
		m_Time += Fps::Get().deltaTime;
		
		if (m_Time > drawTime)
		{
			// ゲージを元に戻す
			m_IconPosition.x = m_GagePosition.x;
			m_NowGage = 0.0f;

			// 非表示にする
			m_Draw = false;
		}
	}

	// アイコンの描画
	void Reload::DrawIcon()
	{		
		// クイックリロードが有効
		if (m_EnableQuickReload && m_DrawQuickGage)
		{
			Engine::Get().graphics()->SetBlendStateSub();
			//m_IconColor = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0);
		}
		else
		{
			m_IconColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0);
		}

		// アイコン
		m_ReloadIcon->Draw(m_IconPosition, D3DXVECTOR2(80.0f, 40.0f), D3DXVECTOR2(0.0f,0.0f), D3DXVECTOR2(0.99f, 1.0f), m_IconColor);

		Engine::Get().graphics()->SetBlendStateDefault();
	}
#pragma endregion _privateFunction_
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
