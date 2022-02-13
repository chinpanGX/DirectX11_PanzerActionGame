/*--------------------------------------------------------------
	
	[Vehicle.cpp]
	Author : 出合翔太

---------------------------------------------------------------*/
#include "Shadow.h"
#include "Skill.h"
#include "Vehicle.h"
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "Engine.h"
#include "Application.h"
#include "Bullet.h"
#include "Pawn.h"
#include "GameManager.h"
#include "Factory.h"
#include "Utility.h"

Vehicle::Vehicle(std::string Tag) : m_Tag(Tag)
{

}

Vehicle::~Vehicle()
{
}

void Vehicle::Begin()
{
}

void Vehicle::Update()
{
	m_Panzer->Update();
	m_Shadow->GetTransform().SetPosition(m_Panzer->GetBody().GetTransform().GetPosition());
	m_Shadow->GetTransform().GetPosition().y = 0.01f;
	m_Shadow->GetTransform().SetScale(8.0f, 0.0f, 10.0f);
	m_Skill->Update(*m_Status, m_Panzer->GetBody().GetTransform().GetPosition());
}

void Vehicle::Draw()
{
	// 戦車の描画
	m_Panzer->Draw();

	// 影の描画
	m_Shadow->Draw();
}

// スタート位置を決める
void Vehicle::SetStartPosition(const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot)
{
	this->GetBodyTransform().SetPosition(Pos);
	this->GetBodyTransform().SetRotation(Rot.x, Rot.y, Rot.z, 1.0f);
}

void Vehicle::SetStartPosition(Pawn* Pawn, const D3DXVECTOR3& Pos, const D3DXVECTOR3& Rot)
{
	m_Panzer->Begin();
	Pawn->GetVehicle().GetBodyTransform().SetPosition(Pos);
	Pawn->GetVehicle().GetBodyTransform().SetRotation(Rot.x, Rot.y, Rot.z, 1.0f);
}

// 撃つ
void Vehicle::Shot(const Transform & Transform)
{
	auto t = Transform;
	// 発射位置
	D3DXVECTOR3 pos = t.GetPosition() + t.forward() * m_GunLength;
	// 飛んでいく方向ベクトル
	D3DXVECTOR3 vector = t.forward();
	
	// Bulletのインスタンスを生成する
	auto normalBullet = Engine::Get().GetApplication()->GetScene()->AddGameObject<Bullet>(LAYER_3D_ACTOR);
	normalBullet->Create(pos, vector);
}

#pragma endregion Panzerのアクション

// コリジョンの位置を更新
void Vehicle::ColiisionUpdate(int32_t Element, const D3DXVECTOR3 & Position, Transform & Transform)
{
	m_Collider[Element]->Update(Position, Transform);
}

Collider & Vehicle::GetCollider(int32_t Element) const
{
	if (!m_Collider[Element])
	{
		std::domain_error("null");
	}
	return *m_Collider[Element];
}

const uint32_t Vehicle::GetColliderNum() const
{
	return m_Collider.size();
}

Transform & Vehicle::GetBodyTransform() const
{
	return m_Panzer->GetBody().GetTransform();
}

Transform & Vehicle::GetTurretTransform() const
{
	return m_Panzer->GetTurret().GetTransform();
}

Transform & Vehicle::GetGunTransform() const
{
	return m_Panzer->GetMainGun().GetTransform();
}

Status & Vehicle::GetStatus() const
{
	// nullcheck
	if (!m_Status)
	{
		throw std::domain_error("m_Status is NullPtr");
	}
	return *m_Status;
}

Skill & Vehicle::GetSkill() const
{
	// nullcheck
	if (!m_Skill)
	{
		throw std::domain_error("m_Skill is NullPtr");
	}
	return *m_Skill;
}

#pragma region proteced_method
// 戦車をセット
void Vehicle::SetPanzer()
{
	// タグにあった戦車を生成
	Factory::FPanzer fpanzer;
	m_Panzer = fpanzer.Create(m_Tag);
	m_Panzer->Begin();

	// 影を生成
	Factory::FShadow fshadow;
	m_Shadow = fshadow.Create();

	// ステータス
	m_Status = std::make_unique<Status>();

	// スキルを生成
	m_Skill = std::make_unique<Skill>();
	
}

// ステータスを設定
void Vehicle::SetStatus(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed)
{
	m_Status->Set(Country, Cost, Hp, Attack, Defence, Speed, Reload, RotSpeed);
}

void Vehicle::ShotPointOffsetLength(float Length)
{
	m_GunLength = Length;
}

Panzer & Vehicle::panzer() const
{
	// nullcheck
	if (!m_Panzer) 
	{
		throw std::domain_error("m_Panzer is NullPtr");
	}
	return *m_Panzer;
}

const std::string & Vehicle::tag() const
{
	return m_Tag;
}
#pragma endregion proteced_method