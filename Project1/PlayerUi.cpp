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
		m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
	}

	DrawSkill::~DrawSkill()
	{
	}

	void DrawSkill::Begin()
	{
		m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// 増加する量
		float t = m_Player->GetVehicle().GetSkill().timeToActivateSkill();
		m_AddAmount = m_MaxDrawSize / t * Fps::Get().deltaTime;
		
		// 減らす量
		m_TimeLimit = m_Player->GetVehicle().GetSkill().timeLimit();
		m_SubAmount = m_MaxDrawSize / m_TimeLimit * Fps::Get().deltaTime + 0.2f;

		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
		m_Time = 0.0f;
	}

	void DrawSkill::Update()
	{
		if (m_Pause->NowPausing()) { return; }
		
		// スキルを使ったかどうか
		m_Use = m_Player->GetVehicle().GetSkill().useSkillNow();
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

	void DrawSkill::Reset()
	{
		// 描画サイズを0にする
		m_DrawSize = 0.0f;
		m_Time = 0.0f;
		m_Color = D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f);
	}

#pragma region _privateFunction_
	void DrawSkill::AddGage()
	{
		// まだスキルが使える状態じゃない
		if (m_Player->GetVehicle().GetSkill().alreadyUseble() == false)
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
#pragma endregion _private関数_
#pragma endregion スキルゲージを描画する

#pragma region _Reload_
	Reload::Reload()
	{
		m_QuickReload = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Gage");
		m_ReloadIcon = std::make_unique<Renderer2D>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource(), "Reload");
		m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
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
		m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		m_Pause = Engine::Get().GetApplication()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);

		// リロード時間の取得
		float t = m_Player->GetVehicle().GetStatus().reloadTime();
		// 増える量を計算
		m_DefaultAmount = m_MaxSizeAmount / t * Fps::Get().deltaTime;

		m_QuickAmount = m_MaxSizeAmount / 0.5f * Fps::Get().deltaTime;
		
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
			m_Render->Draw(m_MaxSizeAmount, m_GagePosition, 15.0f, "Gage", color);

			if (m_DrawQuickGage)
			{
				color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.7f);				
				auto size = D3DXVECTOR2(160.0f, 30.0f);
				// 高速リロード有効範囲のマーク
				m_QuickReload->Draw(m_QuickRangePosition, size);
			}

			color = D3DXVECTOR4(1.0f, 0.5f, 0.7f, 0.5f);
			// ゲージ
			m_Render->Draw(m_NowGageAmount, m_GagePosition, 15.0f, "Gage", color);

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
		m_NowGageAmount = 0.0f;
		// ゲージの描画開始
		m_Draw = true;
		m_DrawQuickGage = true;
		m_MatchCount = true;
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
		m_IconPosition.x = m_GagePosition.x + m_MaxSizeAmount;
		m_NowGageAmount = m_MaxSizeAmount;
	}

	// リロードが有効かどうか
	const bool Reload::enableQuickReload() const
	{
		return m_EnableQuickReload;
	}

	void Reload::enableQuickReload(bool Flag)
	{
		m_MatchCount = Flag;
	}

#pragma region _privateFunction_
	// リロードの処理
	void Reload::NowReload()
	{		
		// クイックリロードの範囲内ならクイックリロードを有効にする
		if (m_IconPosition.x - 40.0f > m_QuickRangePosition.x - 80.0f && m_IconPosition.x + 40.0f < m_QuickRangePosition.x + 80.0f)
		{
			m_EnableQuickReload = true;
		}
		else
		{
			m_EnableQuickReload = false;
		}

		// ゲージをとアイコンの更新		
		// スキルを使用中
		if (m_Player->GetVehicle().GetSkill().useSkillNow())
		{
			AddGageAndMoveIcon(m_QuickAmount);
		}
		// スキルを使っていない
		else
		{
			AddGageAndMoveIcon(m_DefaultAmount);
		}
		
	}

	void Reload::AddGageAndMoveIcon(float amount)
	{
		m_NowGageAmount += amount;
		m_IconPosition.x += amount;
	}

	// リロード完了
	void Reload::Finish()
	{
		if (m_Player->GetReload().finishReload())
		{
			m_NowGageAmount = m_MaxSizeAmount;
			m_IconPosition.x = m_GagePosition.x + m_MaxSizeAmount;
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
			
			m_NowGageAmount = 0.0f;

			// 非表示にする
			m_Draw = false;
		}
	}

	// アイコンの描画
	void Reload::DrawIcon()
	{	
		auto size = D3DXVECTOR2(80.0f, 38.0f);
		auto min = D3DXVECTOR2(0.0f, 0.0f);
		auto max = D3DXVECTOR2(0.99f, 1.0f);
		D3DXVECTOR4 color;

		// デフォルトの設定
		Engine::Get().GetResource()->SetVertexShader("NoLighting");
		Engine::Get().GetResource()->SetInputLayout("NoLighting");
	
		// クイックリロードが有効 またはリロードしていないとき
		if (m_EnableQuickReload && m_MatchCount || m_NowReload == false)
		{			
			Engine::Get().GetResource()->SetPixelShader("NoLighting");
			color = D3DXVECTOR4(0.85f, 0.95f, 0.0f, 1.0);
		}	
		else
		{
			Engine::Get().GetResource()->SetPixelShader("GrayScaleTexture");
			color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0);
		}
		// アイコン
		m_ReloadIcon->Draw(m_IconPosition, size, min, max, color, false);
	}
#pragma endregion _privateFunction_
#pragma endregion _リロードゲージ_

#pragma region _HPGage_
	Hp::Hp()
	{
		m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
	}

	Hp::~Hp()
	{
	}

	void Hp::Begin()
	{
		m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
		// 実際のHPとMAXのサイズから描画する比率を求める
		m_DrawRatioAmount = m_MaxDrawSize / m_Player->GetVehicle().GetStatus().maxHp();
	}

	void Hp::Update()
	{
		// 現在のHP
		m_NowHpAmount = m_Player->GetVehicle().GetStatus().hp();
		// 更新前のHPと比較する
		if (m_OldHpAmount != m_NowHpAmount)
		{
			// 一致しなかったら、描画サイズを計算して前のHPを更新する

			// 現在のHP * 求めた比率
			m_DrawSizeAmount = m_NowHpAmount * m_DrawRatioAmount;
			m_OldHpAmount = m_NowHpAmount;
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
		m_Render->Draw(m_DrawSizeAmount, pos, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	}
#pragma endregion Hpゲージ
}
