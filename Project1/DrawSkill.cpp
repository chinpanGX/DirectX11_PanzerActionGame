/*---------------------------------------------------------------

	[DrawSkill.cpp]
	Author : 出合翔太

	スキルゲージを描画

----------------------------------------------------------------*/
#include "Renderer2D.h"
#include "Engine.h"
#include "Graphics.h"
#include "Application.h"
#include "Resource.h"
#include "Skill.h"
#include "Vehicle.h"
#include "Player.h"
#include "DrawSkill.h"
#include "Fps.h"
#include "Pause.h"

#pragma region DrawSkill_method
GameBg::DrawSkill::DrawSkill()
{
	m_Render = std::make_unique<Render>(*Engine::Get().graphics(), *Engine::Get().resource());
}

GameBg::DrawSkill::~DrawSkill()
{
}

void GameBg::DrawSkill::Begin()
{
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);

	// ゲージを増加する量を計算
	float t = m_Player->vehicle().GetSkill().GetEnableTime();
	m_Add = m_MaxDrawSize / t * Fps::Get().deltaTime;
}

void GameBg::DrawSkill::Update()
{
	if (Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->NowPausing()) { return; }

	// まだスキルが使える状態じゃない
	if (m_Player->vehicle().GetSkill().GetAlreadyUseble() == false)
	{
		// ゲージを増やす
		m_DrawSize += m_Add; 
	}
}

void GameBg::DrawSkill::Event()
{
}

void GameBg::DrawSkill::Draw()
{
	D3DXVECTOR2 pos = D3DXVECTOR2(1450.0f, 940.0f);
	m_Render->Draw(m_MaxDrawSize, pos, D3DXVECTOR4(0.35f, 0.35f, 0.35f, 0.75f));
	m_Render->Draw(m_DrawSize, pos, D3DXVECTOR4(0.7f, 0.7f, 0.1f, 1.0f));
}

void GameBg::DrawSkill::Reset()
{
	// 描画サイズを０にする
	m_DrawSize = 0.0f;
}
#pragma endregion スキルゲージを描画する