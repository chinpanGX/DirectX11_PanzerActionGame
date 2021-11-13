/*------------------------------------------------------------

	[Player.h]
	Author : 出合翔太

	プレイヤーの処理

-------------------------------------------------------------*/
#include "Input.h"
#include "PanzerState.h"
#include "MoveComponent.h"
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
#include "OnComponentEvent.h"
#include "Player.h"

Player::Player() : Pawn(Factory::FVehicle::EType::E_PLAYER), m_Resource(*Engine::Get().resource())
{
	Pawn::Create();
	AddComponentEvent<OnComponentEventWallBox>();
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
	auto pause = Engine::Get().application()->GetScene()->GetGameObject<Pause>(ELayer::LAYER_2D_BG)->GetEnable();
	if (pause) { return; }
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
			vehicle().CalcuateDamege(e);
			ResetCollisionEnter();
		}
	}
	Pawn::CheckZeroHp(this);
}

void Player::Draw()
{
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	if (!camera->IsDrawObject(pivot().transform().position(), vehicle().GetBoxComponent(0).GetSphere3().GetRadius()))
	{
		OutputDebugString("Player NoRendering\n");
		return;
	}
	m_Resource.SetShader("SpotLight");
	vehicle().Draw();
}

void Player::ChangeState(std::unique_ptr<PanzerState> State)
{
	
}

void Player::Respawn(const D3DXVECTOR3& pos)
{
	Pawn::SetStartPosition(this, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Pawn::RespawnSetMaxHP();
	Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA)->Update();
	this->Update();
}

void Player::OnCollision()
{
	// 敵との当たり判定
	if(TrigerEvent())
	{
		if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(0))
		{
			GetMoveComponent().MoveBackward(vehicle().bodyTransform(), Fps::Get().deltaTime);
		}
		if (Engine::Get().application()->GetScene()->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM)->GetNowInput(1))
		{
			GetMoveComponent().MoveForward(vehicle().bodyTransform(), Fps::Get().deltaTime);
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
