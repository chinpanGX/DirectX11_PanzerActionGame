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
#include "NormalBullet.h"
#include "Pawn.h"
#include "GameManager.h"
#include "Factory.h"

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
	m_Status->Update();
	m_Panzer->Update();
	m_Skill->Update(*m_Status);
}

void Vehicle::Draw()
{
	m_Shadow->GetTransform().SetPosition(m_Panzer->GetBody().GetTransform().GetPosition());
	m_Shadow->GetTransform().GetPosition().y = 0.01f;
	m_Shadow->GetTransform().SetScale(8.0f, 0.0f, 10.0f);
	m_Shadow->Draw();
	m_Panzer->Draw();
}

void Vehicle::SetStartPosition(Math::Vector3 pos, Math::Vector3 rot)
{
	this->GetBodyTransform().SetPosition(pos);
	this->GetBodyTransform().SetRotation(rot.x, rot.y, rot.z, 1.0f);
}

void Vehicle::SetStartPosition(Pawn* pawn, Math::Vector3 pos, Math::Vector3 rot)
{
	m_Panzer->Begin();
	pawn->GetVehicle().GetBodyTransform().SetPosition(pos);
	pawn->GetVehicle().GetBodyTransform().SetRotation(rot.x, rot.y, rot.z, 1.0f);
}

// ダメージ計算
void Vehicle::CalcuateDamege(Pawn * Pawn)
{
	float attackpt = 0.0f; // 与えるダメージ
	auto bullet = Engine::Get().GetApplication()->GetScene()->GetGameObjects<NormalBullet>(ELayer::LAYER_3D_ACTOR);
	for (auto b : bullet)
	{
		// 乱数生成(50 ～ 100)の補正をする
		int r = myLib::Random::Rand_R(50, 100);
		attackpt = Pawn->GetVehicle().GetStatus().GetAttack() + r * b->GetDDE() - m_Status->GetDefence();
		CalculateHp(attackpt);
	}
}

// 撃つ
void Vehicle::Shot(const Transform & transform)
{
	// リロードが終わっていないなら撃てない
	if (m_Status->GetFinishReload() == false) { return; }

	float offset = 10.0f; // 補正値
	auto t = transform;
	// 発射位置
	Math::Vector3 pos = t.GetPosition() + t.GetVector(Transform::Vector::Forward) * offset;
	// 飛んでいく方向ベクトル
	Math::Vector3 vector = t.GetVector(Transform::Vector::Forward);
	
	// Bulletのインスタンスを生成する
	auto normalBullet = Engine::Get().GetApplication()->GetScene()->AddGameObject<NormalBullet>(LAYER_3D_ACTOR);
	normalBullet->Create(pos, vector);

	m_Status->ResetReloadTime();
}

// HP計算 
// "param" = AttackPoint : 与えられるダメージ
void Vehicle::CalculateHp(float AttackPoint)
{
	// MAX状態のHPを取得する
	float maxHp = m_Status->GetMaxHp();
	// 現在のHPから減算
	float nowHp = m_Status->GetHp() - AttackPoint;
	m_Status->SetHp(nowHp);
}
#pragma endregion Panzerのアクション

void Vehicle::ColiisionUpdate(int32_t Element, const Math::Vector3 & Position, const Transform & t)
{
	m_BoxComponent[Element]->Update(Position, t);
}

BoxComponent & Vehicle::GetBoxComponent(int32_t Element) const
{
	if (!m_BoxComponent[Element])
	{
		std::domain_error("null");
	}
	return *m_BoxComponent[Element];
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
	if (!m_Status)
	{
		std::domain_error("null");
	}
	return *m_Status;
}

Skill & Vehicle::GetSkill() const
{
	if (!m_Skill)
	{
		std::domain_error("null");
	}
	return *m_Skill;
}

#pragma region proteced_method
void Vehicle::SetPanzer()
{
	Factory::FPanzer fpanzer;
	m_Panzer = fpanzer.Create(m_Tag);
	m_Panzer->Begin();
	Factory::FShadow fshadow;
	m_Shadow = fshadow.Create();
	m_Skill = std::make_unique<Skill>();
}

void Vehicle::SetProperty(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed)
{
	m_Status = std::make_unique<Status>(Country, Cost, Hp, Attack, Defence, Speed, Reload, RotSpeed);
}

Panzer & Vehicle::GetPanzer() const
{
	if (!m_Panzer)
	{
		std::domain_error("null");
	}
	return *m_Panzer;
}

const std::string & Vehicle::GetTag() const
{
	return m_Tag;
}
#pragma endregion proteced_method