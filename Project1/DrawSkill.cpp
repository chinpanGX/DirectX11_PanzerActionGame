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
	float t = m_Player->GetVehicle().GetSkill().GetEnableTime();
	m_Add = m_MaxDrawSize / t * Fps::Get().deltaTime;
}

void GameBg::DrawSkill::Update()
{
	// まだスキルが使える状態じゃない
	if (m_Player->GetVehicle().GetSkill().GetAlreadyUseble() == false)
	{
		m_DrawSize += m_Add;
	}
}

void GameBg::DrawSkill::Event()
{
}

void GameBg::DrawSkill::Draw()
{
	Math::Vector2 pos = Math::Vector2(1450.0f, 940.0f);
	m_Render->Draw(m_MaxDrawSize, pos, Math::Vector4(0.35f, 0.35f, 0.35f, 0.75f));
	m_Render->Draw(m_DrawSize, pos, Math::Vector4(0.7f, 0.7f, 0.1f, 1.0f));
}

void GameBg::DrawSkill::Reset()
{
	m_DrawSize = 0.0f;
}
#pragma endregion スキルゲージを描画する