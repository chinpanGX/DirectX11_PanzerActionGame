/*-------------------------------------------------------------

	[PlayerBulletAmount.cpp]
	Author : 出合翔太

	プレイヤーの弾数を描画する

--------------------------------------------------------------*/
#include "Player.h"
#include "PlayerBulletAmount.h"
#include "Engine.h"
#include "Application.h"

PlayerBulletAmount::PlayerBulletAmount() : DrawNumber(64.0f, 2)
{
}

PlayerBulletAmount::~PlayerBulletAmount()
{
}

void PlayerBulletAmount::Draw(int value)
{
	for (int32_t i = 0; i < Getdigit(); ++i)
	{
		int num = value % 10;
		value /= 10;
		NumberDraw(D3DXVECTOR2(1650.0f + ((GetSize() - 20.0f) * (Getdigit() - (i + 1))), 1000.0f), num);
	}
}

PlayerBulletAmountMax::PlayerBulletAmountMax() : DrawNumber(64.0f, 2)
{
}

PlayerBulletAmountMax::~PlayerBulletAmountMax()
{
}

void PlayerBulletAmountMax::Draw(int value)
{
	for (int32_t i = 0; i < Getdigit(); ++i)
	{
		int num = value % 10;
		value /= 10;
		NumberDraw(D3DXVECTOR2(1800.0f + ((GetSize() - 20.0f) * (Getdigit() - (i + 1))), 1000.0f), num);
	}
}

DrawSlash::DrawSlash()
{
}

DrawSlash::~DrawSlash()
{
}

void DrawSlash::Draw()
{
	
}

void PlayerUi::BulletAmount::Begin()
{
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);
	m_DrawBulletAmount.emplace_back(std::make_unique<PlayerBulletAmount>());
}

void PlayerUi::BulletAmount::Update()
{
	m_BulletsValue = m_Player->amountBullets();
}

void PlayerUi::BulletAmount::Event()
{
}

void PlayerUi::BulletAmount::Draw()
{
	m_DrawBulletAmount[0]->Draw(m_BulletsValue);
}
