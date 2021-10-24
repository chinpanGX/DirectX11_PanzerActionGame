/*--------------------------------------------------------------
	
	[Hp.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Renderer2D.h"
#include "Status.h"
#include "Vehicle.h"
#include "Player.h"
#include "Hp.h"
#include "Engine.h"
#include "Application.h"

GameBg::Hp::Hp()
{
	m_Render = std::make_unique<Render>(*Engine::Get().GetGraphics(), *Engine::Get().GetResource());
}

GameBg::Hp::~Hp()
{
}

void GameBg::Hp::Begin()
{
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	// 実際のHPとMAXのサイズから描画する比率を求める
	m_DrawRatio = m_MaxDrawSize / m_Player->GetVehicle().GetStatus().GetMaxHp();
}

void GameBg::Hp::Update()
{
	// 現在のHP
	m_NowHp = m_Player->GetVehicle().GetStatus().GetHp();
	// 更新前のHPと比較する
	if (m_OldHp != m_NowHp)
	{
		// 一致しなかったら、描画サイズを計算して前のHPを更新する

		// 現在のHP * 求めた比率
		m_DrawSize = m_NowHp * m_DrawRatio;
		m_OldHp = m_NowHp;
	}
}

void GameBg::Hp::Event()
{
}

void GameBg::Hp::Draw()
{
	// 描画位置を設定
	Math::Vector2 pos = Math::Vector2(1450.0f, 900.0f);
	
	// MAX状態のHPバー
	m_Render->Draw(m_MaxDrawSize, pos, Math::Vector4(0.35f, 0.35f, 0.35f, 0.75f));

	// 現在のHPバー
	m_Render->Draw(m_DrawSize, pos, Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}
