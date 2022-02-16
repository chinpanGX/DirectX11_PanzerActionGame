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
#include "Bullet.h"
#include "Player.h"
#include "PlayerUi.h"

Player::Player() : Pawn(Factory::FVehicle::EType::E_PLAYER), m_Resource(*Engine::Get().GetResource()), m_Graphics(*Engine::Get().GetGraphics())
{
	Pawn::Create();
}

Player::~Player()
{
	m_Audioplay = false;
}

void Player::Begin()
{
	auto scene = Engine::Get().GetApplication()->GetScene();
	m_EnemyList = scene->GetGameObjects<Enemy>(ELayer::LAYER_3D_ACTOR);
	m_SupplyList = scene->GetGameObjects<Supply>(ELayer::LAYER_3D_STAGE);
	m_Command = scene->GetGameObject<GameCommand>(ELayer::LAYER_SYSTEM);
	m_Camera = scene->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	m_Pause = scene->GetGameObject<Pause>(ELayer::LAYER_2D_PAUSE);
	m_DrawSkill = scene->GetGameObject<PlayerUi::DrawSkill>(ELayer::LAYER_2D_UI);
	m_Reload = scene->GetGameObject<PlayerUi::Reload>(ELayer::LAYER_2D_UI);
	m_PlayerReload = std::make_unique<PlayerReload>();
	m_PlayerReload->Init();
	Pawn::SetStartPosition(this, D3DXVECTOR3(0.0f, 0.0f, -180.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_EnteringSulpplyPoint = false;
}

void Player::Update()
{
	if(m_Pause->NowPausing()) { return; }
	OnSound();
	m_PlayerReload->Update();
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
			float attackpt = 0.0f; // 与えるダメージ
			auto bulletList = Engine::Get().GetApplication()->GetScene()->GetGameObjects<Bullet>(ELayer::LAYER_3D_ACTOR);
			for (auto bullet : bulletList)
			{
				// 乱数生成(75 ～ 120)の補正をする
				int rand = myLib::Random::Rand_R(70, 120);
				attackpt = (e->GetVehicle().GetStatus().GetAttack()) + rand * bullet->GetDistdecay() - GetVehicle().GetStatus().GetDefence();			
				// MAX状態のHPを取得する
				float maxHp = GetVehicle().GetStatus().GetMaxHp();
				// 現在のHPから減算
				float nowHp = GetVehicle().GetStatus().GetHp() - attackpt;
				GetVehicle().GetStatus().SetHp(nowHp);
			}
			ResetCollisionEnter();
		}
	}
	Pawn::CheckZeroHp(this);
}

void Player::Draw()
{
	// 描画できるか
	if (m_Camera->NotDrawObject(GetPivot().GetTransform().GetPosition(), GetVehicle().GetCollider(0).GetSphere3().GetRadius())) { return; }
	
	// シェーダーの設定
	m_Resource.SetVertexShader("PixelLighting");
	m_Resource.SetInputLayout("PixelLighting");
	// スキルを使っているか
	if (GetVehicle().GetSkill().GetUseSkillNow())
	{
		// スキルを使っているときの設定
		m_Resource.SetPixelShader("ToonAnim");
		m_Resource.SetTexture(1, "ToonAnim");
		D3DXVECTOR4 uv = GetVehicle().GetSkill().GetTexUV();
		m_Graphics.SetParameter(uv);
		
	}
	// 補給中
	else if(m_Command->NowReplenishBullet())
	{
		m_Resource.SetPixelShader("ToonAnim");
		m_Resource.SetTexture(1, "ToonAnim");
		m_Param.x += 0.5f;
		m_Param.y += 0.05f;
		m_Graphics.SetParameter(m_Param);
	}
	else
	{
		// デフォルトの設定
		m_Resource.SetPixelShader("PixelLighting");
	}

	// 描画
	GetVehicle().Draw();
}

void Player::ResPawn(const D3DXVECTOR3& pos)
{
	m_DrawSkill->Reset();
	GetVehicle().GetSkill().Reset(GetVehicle().GetStatus());
	GetVehicle().GetStatus().Reset();
	m_AmountBullets = m_AmountBuuletsMax;
	SetStartPosition(this, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_Camera->Update();
}

void Player::UseSkill()
{
	if (GetVehicle().GetSkill().GetAlreadyUseble() == false) { return; }
	// スキルを使う
	GetVehicle().GetSkill().Enable(this);	
	GetVehicle().GetSkill().PlayEffect(this);
	m_Resource.AudioPlay("Skill");
}

void Player::Shot()
{
	// リロードが終わっていない OR 弾数が0のとき　=> 撃てない
	if (m_PlayerReload->GetFinishReload() == false || m_AmountBullets == 0) 
	{ 
		return; 
	}
	// 弾数を減らして行く
	m_AmountBullets--;

	// 射撃
	GetVehicle().Shot(GetPivot().GetTransform());
	// オーディオ
	Engine::Get().GetResource()->AudioPlay("Shot");
	
	// リロード開始
	m_PlayerReload->Begin();

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


bool Player::GetIsBulletsUpperLimit()
{
	// 弾の数が上限かどうか
	if (m_AmountBullets >= m_AmountBuuletsMax)
	{
		return true; // 上限
	}
	return false; // 上限ではない⇒補給できる
}

bool Player::GetEnterSupplyPoint()
{
	return m_EnteringSulpplyPoint;
}

int32_t Player::GetAmountBullets() const
{
	return m_AmountBullets;
}

PlayerReload & Player::GetReload() const
{
	return *m_PlayerReload;
}

void Player::CalcuateDamege(Enemy * Enemy)
{
}

void Player::OnCollision()
{
	// 敵との当たり判定
	for(auto enemy : m_EnemyList)
	if (enemy)
	{
		if (Intersect(GetVehicle().GetCollider(0).GetSphere3(), enemy->GetVehicle().GetCollider(0).GetSphere3()))
		{
			if (Intersect(GetVehicle().GetCollider(0).GetOBB3(), enemy->GetVehicle().GetCollider(0).GetOBB3()))
			{
				D3DXVECTOR3 reflection = GetMoveComponent().velocity() * -1 * 2.0f;
				GetVehicle().GetBodyTransform().GetPosition() += reflection;
			}
		}
	}

	// 補給地点との当たり判定
	for (auto supply : m_SupplyList)
	{
		if (Intersect(GetVehicle().GetCollider(0).GetSphere3(), supply->GetCollider().GetSphere3()))
		{
			// ここで通知する
			m_EnteringSulpplyPoint = true;
			
			if (Intersect(GetVehicle().GetCollider(0).GetOBB3(), supply->GetCollider().GetOBB3()))
			{
				D3DXVECTOR3 hitPosition = GetVehicle().GetBodyTransform().GetPosition() + GetMoveComponent().velocity();

				D3DXVECTOR3 reflection = GetMoveComponent().velocity() * -1 * 2.0f;
				GetVehicle().GetBodyTransform().GetPosition() = hitPosition + reflection;
			}

			// ループを抜ける
			break;
		}
		// 当たっていない
		else 
		{
			m_EnteringSulpplyPoint = false;
			m_NowReplenish = false;
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
