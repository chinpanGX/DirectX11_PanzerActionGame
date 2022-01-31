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
	m_Shadow->transform().position(m_Panzer->GetBody().transform().position());
	m_Shadow->transform().position().y = 0.01f;
	m_Shadow->transform().scale(8.0f, 0.0f, 10.0f);
	m_Skill->Update(*m_Status, m_Panzer->GetBody().transform().position());
}

void Vehicle::Draw()
{
	// 戦車の描画
	m_Panzer->Draw();

	// 影の描画
	m_Shadow->Draw();
}

// スタート位置を決める
void Vehicle::SetStartPosition(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	this->bodyTransform().position(pos);
	this->bodyTransform().rotation(rot.x, rot.y, rot.z, 1.0f);
}

void Vehicle::SetStartPosition(Pawn* pawn, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_Panzer->Begin();
	pawn->vehicle().bodyTransform().position(pos);
	pawn->vehicle().bodyTransform().rotation(rot.x, rot.y, rot.z, 1.0f);
}

// 撃つ
void Vehicle::Shot(const Transform & transform)
{
	auto t = transform;
	// 発射位置
	D3DXVECTOR3 pos = t.position() + t.forward() * m_GunLength;
	// 飛んでいく方向ベクトル
	D3DXVECTOR3 vector = t.forward();
	
	// Bulletのインスタンスを生成する
	auto normalBullet = Engine::Get().application()->GetScene()->AddGameObject<Bullet>(LAYER_3D_ACTOR);
	normalBullet->Create(pos, vector);
}

#pragma endregion Panzerのアクション

// コリジョンの位置を更新
void Vehicle::ColiisionUpdate(int32_t Element, const D3DXVECTOR3 & Position, Transform & t)
{
	m_Collider[Element]->Update(Position, t);
}

Collider & Vehicle::collider(int32_t Element) const
{
	if (!m_Collider[Element])
	{
		std::domain_error("null");
	}
	return *m_Collider[Element];
}

const uint32_t Vehicle::colliderNum() const
{
	return m_Collider.size();
}

Transform & Vehicle::bodyTransform() const
{
	return m_Panzer->GetBody().transform();
}

Transform & Vehicle::turretTransform() const
{
	return m_Panzer->GetTurret().transform();
}

Transform & Vehicle::gunTransform() const
{
	return m_Panzer->GetMainGun().transform();
}

Status & Vehicle::status() const
{
	// nullcheck
	if (!m_Status)
	{
		throw std::domain_error("m_Status is NullPtr");
	}
	return *m_Status;
}

Skill & Vehicle::skill() const
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

void Vehicle::ShotPointOffsetLength(float length)
{
	m_GunLength = length;
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