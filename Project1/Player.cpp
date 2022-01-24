/*------------------------------------------------------------

	[Player.h]
	Author : 出合翔太

	プレイヤーの処理

-------------------------------------------------------------*/
#include "Input.h"
#include "MoveComponent.h"
#include "Skill.h"
#include "Reload.h"
#include "Vehicle.h"
#include "PanzerContainer.h"
#include "Engine.h"
#include "Resource.h"
#include "Graphics.h"
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
#include "Supply.h"
#include "Player.h"
#include "PlayerUi.h"

Player::Player() : Pawn(Factory::FVehicle::EType::E_PLAYER), m_Resource(*Engine::Get().resource()), m_Graphics(*Engine::Get().graphics())
{
	Pawn::Create();
}

Player::~Player()
{
	m_Audioplay = false;
}

void Player::Begin()
{
	auto scene = Engine::Get().application()->GetScene();
	m_EnemyList = scene->GetGameObjects<Enemy>(ELayer::LAYER_3D_ACTOR);
	m_SupplyList = scene->GetGameObjects<Supply>(ELayer::LAYER_3D_STAGE);
	m_Command = scene->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	m_Camera = scene->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	m_Pause = scene->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
	m_DrawSkill = scene->GetGameObject<PlayerUi::DrawSkill>(ELayer::LAYER_2D_UI);
	m_Reload = scene->GetGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	reload().Init();
	Pawn::SetStartPosition(this, D3DXVECTOR3(0.0f, 0.0f, -180.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_EnteringSulpplyPoint = false;
}

void Player::Update()
{
	if(m_Pause->NowPausing()) { return; }
	OnSound();
	Pawn::Update();
	OnCollision();
}

void Player::Event()
{
	if (CollisionEnter())
	{
		for (auto e : m_EnemyList)
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
	if (m_Camera->NotDrawObject(pivot().transform().position(), vehicle().collider(0).GetSphere3().GetRadius())) { return; }
	
	// シェーダーの設定
	m_Resource.SetVertexShader("PixelLighting");
	m_Resource.SetInputLayout("PixelLighting");
	// スキルを使っているか
	if (vehicle().skill().useSkillNow())
	{
		// スキルを使っているときの設定
		m_Resource.SetPixelShader("ToonAnim");
		m_Resource.SetTexture(1, "ToonAnim");
		D3DXVECTOR4 uv = vehicle().skill().uv();
		m_Graphics.SetParameter(uv);
		
	}
	else
	{
		// デフォルトの設定
		m_Resource.SetPixelShader("PixelLighting");
	}

	// 描画
	vehicle().Draw();
}

void Player::Respawn(const D3DXVECTOR3& pos)
{
	m_DrawSkill->Reset();
	Pawn::SetStartPosition(this, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Pawn::RespawnSetMaxHP();
	m_Camera->Update();
	this->Update();
}

void Player::UseSkill()
{
	if (vehicle().skill().alreadyUseble() == false) { return; }
	// スキルを使う
	vehicle().skill().Enable(this);	
	vehicle().skill().PlayEffect(this);
	m_Resource.AudioPlay("Skill");
}

void Player::Shot()
{
	// リロードが終わっていない OR 弾数が0のとき　=> 撃てない
	if (reload().finishReload() == false || m_AmountBullets == 0) 
	{ 
		return; 
	}
	// 弾数を減らして行く
	m_AmountBullets--;

	// 射撃
	vehicle().Shot(pivot().transform());
	// オーディオ
	Engine::Get().resource()->AudioPlay("Shot");
	
	// リロード開始
	reload().Begin();

	// リロードゲージの表示ON
	m_Reload->BeginReload();
}

void Player::ReplenishBullets()
{
	m_ReplenishTime += Fps::Get().deltaTime;
	// 補給に必要な時間 1秒
	float delayTime = 1.0f;

	if (m_ReplenishTime > delayTime)
	{
		m_AmountBullets++;
		// 上限値の設定
		if (m_AmountBullets > m_AmountBuuletsMax)
		{
			m_AmountBullets = m_AmountBuuletsMax;
		}
		m_ReplenishTime = 0;
	}
}


bool Player::isBulletsUpperLimit()
{
	// 弾の数が上限かどうか
	if (m_AmountBullets >= m_AmountBuuletsMax)
	{
		return true; // 上限
	}
	return false; // 上限ではない⇒補給できる
}

bool Player::enterSupplyPoint()
{
	return m_EnteringSulpplyPoint;
}

int32_t Player::amountBullets() const
{
	return m_AmountBullets;
}

void Player::OnCollision()
{
	// 敵との当たり判定
	for(auto enemy : m_EnemyList)
	if (enemy)
	{
		if (Intersect(vehicle().collider(0).GetSphere3(), enemy->vehicle().collider(0).GetSphere3()))
		{
			if (Intersect(vehicle().collider(0).GetOBB3(), enemy->vehicle().collider(0).GetOBB3()))
			{
				D3DXVECTOR3 reflection = moveComponent().velocity() * -1 * 2.0f;
				vehicle().bodyTransform().position() += reflection;
			}
		}
	}

	// 補給地点との当たり判定
	for (auto supply : m_SupplyList)
	{
		if (Intersect(vehicle().collider(0).GetSphere3(), supply->collider().GetSphere3()))
		{
			// ここで通知する
			m_EnteringSulpplyPoint = true;
			
			if (Intersect(vehicle().collider(0).GetOBB3(), supply->collider().GetOBB3()))
			{
				D3DXVECTOR3 hitPosition = vehicle().bodyTransform().position() + moveComponent().velocity();

				D3DXVECTOR3 reflection = moveComponent().velocity() * -1 * 2.0f;
				vehicle().bodyTransform().position() = hitPosition + reflection;
			}
		}
		// 当たっていない
		else
		{
			m_EnteringSulpplyPoint = false;
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
		nowInput = m_Command->GetNowInput(i);
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
