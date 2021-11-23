/*------------------------------------------------------------

	[Player.h]
	Author : 出合翔太

	プレイヤーの処理

-------------------------------------------------------------*/
#include "Input.h"
#include "MoveComponent.h"
#include "Skill.h"
#include "Vehicle.h"
#include "PanzerContainer.h"
#include "Engine.h"
#include "Resource.h"
#include "Application.h"
#include "Command.h"
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "Factory.h"
#include "Pause.h"
#include "Fps.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Pivot.h"
#include "Player.h"
#include "PlayerUi.h"

Player::Player() : Pawn(Factory::FVehicle::EType::E_PLAYER), m_Resource(*Engine::Get().resource())
{
	Pawn::Create();
}

Player::~Player()
{
	m_Audioplay = false;
}

void Player::Begin()
{
	Pawn::SetStartPosition(this, D3DXVECTOR3(0.0f, 0.0f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

void Player::Update()
{
	if(Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->NowPausing()) { return; }
	OnSound();
	Pawn::Update();
	OnCollision();
}

void Player::Event()
{
	if (CollisionEnter())
	{
		auto enemy = Engine::Get().application()->GetScene()->GetGameObjects<Enemy>(ELayer::LAYER_3D_ACTOR);
		for (auto e : enemy)
		{
			// ダメージ計算
			vehicle().CalcuateDamege(e);
			ResetCollisionEnter();
		}
	}
	Pawn::CheckZeroHp(this);
}

void Player::Draw()
{
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	if (camera->NotDrawObject(pivot().transform().position(), vehicle().collider(0).GetSphere3().GetRadius()))
	{
		//OutputDebugString("Player NoRendering\n");
		return;
	}
	m_Resource.SetShader("PixelLighting");
	vehicle().Draw();
}

void Player::Respawn(const D3DXVECTOR3& pos)
{
	Pawn::SetStartPosition(this, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Pawn::RespawnSetMaxHP();
	Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA)->Update();
	this->Update();
}

void Player::UseSkill()
{
	vehicle().skill().Enable(this);
	if (vehicle().skill().alreadyUseble())
	{		
		// ゲージをリセットする
		Engine::Get().application()->GetScene()->GetGameObject<PlayerUi::DrawSkill>(ELayer::LAYER_2D_UI)->Reset();
		// スキルエフェクトを発生
		vehicle().skill().PlayEffect(this);
	}
}

void Player::Shot()
{
	// 射撃
	vehicle().Shot(pivot().transform());
	// オーディオ
	Engine::Get().resource()->AudioPlay("Shot");
	// リロードエフェクト
	auto effect = Engine::Get().application()->GetScene()->AddGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_EFFECT);
	D3DXVECTOR3 offset = pivot().transform().position() + D3DXVECTOR3(0.0f, 3.0f, 0.0f) + (pivot().transform().forward() * 5.0f);
	effect->transform().position(offset);
}

void Player::OnCollision()
{
	// 敵との当たり判定
	auto enemy = Engine::Get().application()->GetScene()->GetGameObject<Enemy>(ELayer::LAYER_3D_ACTOR);
	if (enemy)
	{
		if (Intersect(vehicle().collider(0).GetSphere3(), enemy->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(vehicle().collider(0).GetOBB3(), enemy->vehicle().collider(0).GetOBB3()))
			{
				if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(0))
				{
					moveComponent().MoveBackward(vehicle().bodyTransform(), Fps::Get().deltaTime);
				}
				if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(1))
				{
					moveComponent().MoveForward(vehicle().bodyTransform(), Fps::Get().deltaTime);
				}
			}
		}
	}
	BeginOverlap(this);
}

// サウンドを鳴らす
void Player::OnSound()
{
	bool nowInput = false;
	for (int32_t i = 0; i < 2; i++)
	{
		nowInput = Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(i);
		if (nowInput == true)
		{
			break;
		}
	}
	myLib::Timeline audioVolume(0.1f, 1.0f, 0.01f);
	// タイムラインの設定
	/// 入力中かどうか調べる
	if (nowInput == true)
	{
		// エンジン音をあげる
		audioVolume.Start(m_Volume);
	}
	else if (nowInput == false)
	{
		// エンジン音を下げる
		audioVolume.Reverce(m_Volume);
	}
	if (m_Audioplay == false)
	{
		m_Resource.AudioPlay("Idel");
		m_Audioplay = true;
	}
	m_Resource.AudioSetVolume("Idel", m_Volume);
}
