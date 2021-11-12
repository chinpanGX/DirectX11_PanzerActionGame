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
	m_Status->Update();
	m_Panzer->Update();
	m_Skill->Update(*m_Status);
}

void Vehicle::Draw()
{
	// 戦車の描画
	m_Panzer->Draw();

	// 影の描画
	m_Shadow->transform().position(m_Panzer->GetBody().transform().position());
	m_Shadow->transform().position().y = 0.01f;
	m_Shadow->transform().scale(8.0f, 0.0f, 10.0f);
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

// ダメージ計算
void Vehicle::CalcuateDamege(Pawn * Pawn)
{
	float attackpt = 0.0f; // 与えるダメージ
	auto bullet = Engine::Get().application()->GetScene()->GetGameObjects<NormalBullet>(ELayer::LAYER_3D_ACTOR);
	for (auto b : bullet)
	{
		// 乱数生成(50 ～ 100)の補正をする
		int r = myLib::Random::Rand_R(50, 100);
		attackpt = Pawn->vehicle().GetStatus().GetAttack() + r * b->GetDDE() - m_Status->GetDefence();
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
	D3DXVECTOR3 pos = t.position() + t.forward() * offset;
	// 飛んでいく方向ベクトル
	D3DXVECTOR3 vector = t.forward();
	
	// Bulletのインスタンスを生成する
	auto normalBullet = Engine::Get().application()->GetScene()->AddGameObject<NormalBullet>(LAYER_3D_ACTOR);
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

// コリジョンの位置を更新
void Vehicle::ColiisionUpdate(int32_t Element, const D3DXVECTOR3 & Position, const Transform & t)
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

Status & Vehicle::GetStatus() const
{
	// nullcheck
	if (!m_Status) { OutputDebugString("m_Status is NullPtr\n"); }
	return *m_Status;
}

Skill & Vehicle::GetSkill() const
{
	// nullcheck
	if (!m_Skill) { OutputDebugString("m_Skill is NullPtr\n"); }
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

	// スキルを生成
	m_Skill = std::make_unique<Skill>();
}

// ステータスを設定
void Vehicle::SetProperty(Status::Country Country, float Cost, float Hp, float Attack, float Defence, float Speed, float Reload, float RotSpeed)
{
	m_Status = std::make_unique<Status>(Country, Cost, Hp, Attack, Defence, Speed, Reload, RotSpeed);
}

Panzer & Vehicle::GetPanzer() const
{
	// nullcheck
	if (!m_Panzer) { OutputDebugString("m_Panzer is NullPtr\n"); }
	return *m_Panzer;
}

const std::string & Vehicle::GetTag() const
{
	return m_Tag;
}
#pragma endregion proteced_method