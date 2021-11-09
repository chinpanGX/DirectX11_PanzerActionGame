/*--------------------------------------------------------------

	[PanzerList.cpp]
	Author : 出合翔太

	戦車のリスト

---------------------------------------------------------------*/
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "Status.h"
#include "Shadow.h"
#include "Factory.h"
#include "SkillList.h"
#include "Skill.h"
#include "PanzerList.h"
#include "Engine.h"
#include "Resource.h"

#pragma region Tiger
Tiger::Tiger() : Vehicle("Tiger")
{
	// リソースのロード
	Engine::Get().GetResource()->LoadModel("TigerBody", "Panzer\\TankBody.obj");
	Engine::Get().GetResource()->LoadModel("TigerTurret", "Panzer\\TankTurret.obj");
	Engine::Get().GetResource()->LoadModel("TigerGun", "Panzer\\TankMainGun.obj");
	// 戦車のパーツを組み立てる
	SetPanzer();
	// プロパティ設定
	SetProperty(Status::Country::DE, 36.0, 1400.0f, 163.0f, 120.0f, 30.0f, 4.0f, 0.4f);
	
	// スキルの設定
	// たまる時間30.0f
	GetSkill().Begin(30.0f);	
	// 攻撃力UP
	GetSkill().SetSkill(std::make_unique<UseSkill::AttackUp>(1.2f));

	// BoxComponentの設定
	m_BoxComponent[0] = std::make_unique<BoxComponent>();
	m_BoxComponent[1] = std::make_unique<BoxComponent>();
	m_BoxComponent[2] = std::make_unique<BoxComponent>();
	m_BoxComponent[0]->SetSphere3(GetPanzer().GetBody().GetTransform(), 6.0f);
	m_BoxComponent[0]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 3.0f, 7.0f));
	m_BoxComponent[1]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(2.0f, 1.0f, 2.0f));
	m_BoxComponent[2]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(0.5f, 0.5f, 3.0f));
}

Tiger::~Tiger()
{
	Engine::Get().GetResource()->UnloadModel("TigerBody");
	Engine::Get().GetResource()->UnloadModel("TigerTurret");
	Engine::Get().GetResource()->UnloadModel("TigerGun");
}

void Tiger::Begin()
{
}

void Tiger::Update()
{
	Vehicle::Update();
}

void Tiger::Event()
{
}

void Tiger::Draw()
{
	Vehicle::Draw();
#if 0
	m_BoxComponent[0]->SystemDraw();
	m_BoxComponent[1]->SystemDraw();
	m_BoxComponent[2]->SystemDraw();
#endif
}
#pragma endregion ティーガー

#pragma region Centurion
Centurion::Centurion() : Vehicle("Centurion")
{
	// リソースのロード
	Engine::Get().GetResource()->LoadModel("CenturionBody", "Panzer\\CenturionBody.obj");
	Engine::Get().GetResource()->LoadModel("CenturionTurret", "Panzer\\CenturionTurret.obj");
	Engine::Get().GetResource()->LoadModel("CenturionGun", "Panzer\\CenturionMainGun.obj");
	// 戦車の設定
	Vehicle::SetPanzer();
	Vehicle::SetProperty(Status::Country::UK, 45.0f, 1350.0f, 248.0f, 114.0f, 50.0f, 6.0f, 0.56f);

	// スキルの設定
	// たまる時間20.0f
	GetSkill().Begin(20.0f);
	// 速度UP
	GetSkill().SetSkill(std::make_unique<UseSkill::SpeedUp>(1.5f));

	// コリジョンの設定
	m_BoxComponent[0] = std::make_unique<BoxComponent>();
	m_BoxComponent[1] = std::make_unique<BoxComponent>();
	m_BoxComponent[2] = std::make_unique<BoxComponent>();
	m_BoxComponent[0]->SetSphere3(GetPanzer().GetBody().GetTransform(), 8.0f);
	m_BoxComponent[0]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 3.0f, 8.0f));
	m_BoxComponent[1]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(2.0f, 1.0f, 2.0f));
	m_BoxComponent[2]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(0.5f, 0.5f, 3.0f));
}

Centurion::~Centurion()
{
	Engine::Get().GetResource()->UnloadModel("CenturionBody");
	Engine::Get().GetResource()->UnloadModel("CenturionTurret");
	Engine::Get().GetResource()->UnloadModel("CenturionGun");
}

void Centurion::Begin()
{
}

void Centurion::Update()
{
	Vehicle::Update();
}

void Centurion::Event()
{
}

void Centurion::Draw()
{
	Vehicle::Draw();
#if 0
	m_BoxComponent[0]->SystemDraw();
	m_BoxComponent[1]->SystemDraw();
	m_BoxComponent[2]->SystemDraw();
#endif
}
#pragma endregion センチュリオン

#pragma region Patton
Patton::Patton() : Vehicle("Patton")
{
	//　リソースのロード
	Engine::Get().GetResource()->LoadModel("PattonBody", "Panzer\\PattonBody.obj");
	Engine::Get().GetResource()->LoadModel("PattonTurret", "Panzer\\PattonTurret.obj");
	Engine::Get().GetResource()->LoadModel("PattonGun", "Panzer\\PattonMainGun.obj");
	// 戦車の設定
	Vehicle::SetPanzer();
	Vehicle::SetProperty(Status::Country::US, 47.0f, 1600.0f, 240.0f, 139.0f, 60.0f, 8.0f, 0.6f);

	// スキルの設定
	// たまる時間40.0f
	GetSkill().Begin(40.0f);
	// 防御力UP
	GetSkill().SetSkill(std::make_unique<UseSkill::DefenceUp>(1.5f));

	// コリジョンの設定
	m_BoxComponent[0] = std::make_unique<BoxComponent>();
	m_BoxComponent[1] = std::make_unique<BoxComponent>();
	m_BoxComponent[2] = std::make_unique<BoxComponent>();
	m_BoxComponent[0]->SetSphere3(GetPanzer().GetBody().GetTransform(), 8.0f);
	m_BoxComponent[0]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 3.0f, 8.0f));
	m_BoxComponent[1]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(2.0f, 1.0f, 2.0f));
	m_BoxComponent[2]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(0.5f, 0.5f, 3.0f));
}

Patton::~Patton()
{
	Engine::Get().GetResource()->UnloadModel("PattonBody");
	Engine::Get().GetResource()->UnloadModel("PattonTurret");
	Engine::Get().GetResource()->UnloadModel("PattonGun");
}

void Patton::Begin()
{
}

void Patton::Update()
{
	Vehicle::Update();
}

void Patton::Event()
{
}

void Patton::Draw()
{
	Vehicle::Draw();
#if 0
	m_BoxComponent[0]->SystemDraw();
	m_BoxComponent[1]->SystemDraw();
	m_BoxComponent[2]->SystemDraw();
#endif
}
#pragma endregion パットン

#pragma region T-34-85
T_34_85::T_34_85() : Vehicle("T-34/85")
{
	// リソースのロード
	Engine::Get().GetResource()->LoadModel("T-34/85Body", "Panzer\\T-34Body.obj");
	Engine::Get().GetResource()->LoadModel("T-34/85Turret", "Panzer\\T-34Turret.obj");
	Engine::Get().GetResource()->LoadModel("T-34/85Gun", "Panzer\\T-34MainGun.obj");
	// 戦車の設定
	Vehicle::SetPanzer();
	Vehicle::SetProperty(Status::Country::RU, 31.0f, 770.0f, 140.0f, 63.0f, 54.0f, 4.0f, 0.6f);

	// スキルの設定
	// たまる時間20.0f
	GetSkill().Begin(20.0f);
	// HP回復
	GetSkill().SetSkill(std::make_unique<UseSkill::HealHp>());
	// 防御力UP
	GetSkill().SetSkill(std::make_unique<UseSkill::DefenceUp>(2.0f));

	// コリジョンの設定
	m_BoxComponent[0] = std::make_unique<BoxComponent>();
	m_BoxComponent[1] = std::make_unique<BoxComponent>();
	m_BoxComponent[2] = std::make_unique<BoxComponent>();
	m_BoxComponent[0]->SetSphere3(GetPanzer().GetBody().GetTransform(), 6.0f);
	m_BoxComponent[0]->SetAABB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 5.0f, 4.0f));
	m_BoxComponent[0]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 4.0f, 7.0f));
	m_BoxComponent[1]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(3.0f, 2.0f, 2.0f));
	m_BoxComponent[2]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(0.5f, 0.5f, 3.0f));
}

T_34_85::~T_34_85()
{
	Engine::Get().GetResource()->UnloadModel("T-34/85Body");
	Engine::Get().GetResource()->UnloadModel("T-34/85Turret");
	Engine::Get().GetResource()->UnloadModel("T-34/85Gun");
}

void T_34_85::Begin()
{
}

void T_34_85::Update()
{
	Vehicle::Update();
}

void T_34_85::Event()
{
}

void T_34_85::Draw()
{
	Vehicle::Draw();
#if 0 
	m_BoxComponent[0]->SystemDraw();
	m_BoxComponent[1]->SystemDraw();
	m_BoxComponent[2]->SystemDraw();
#endif
}
#pragma endregion T-34-85

#pragma region IV-H
IV_H::IV_H() : Vehicle("IV-H")
{
	// リソースのロード
	Engine::Get().GetResource()->LoadModel("IV-HBody", "Panzer\\IVBody.obj");
	Engine::Get().GetResource()->LoadModel("IV-HTurret", "Panzer\\IVTurret.obj");
	Engine::Get().GetResource()->LoadModel("IV-HGun", "Panzer\\IVMainGun.obj");
	// 戦車の設定
	Vehicle::SetPanzer();
	Vehicle::SetProperty(Status::Country::DE, 26.0f, 600.0f, 132.0f, 47.0f, 40.0f, 4.0f, 0.5f);

	// スキルの設定
	// たまる時間40.0f
	GetSkill().Begin(40.0f);
	// HP回復
	GetSkill().SetSkill(std::make_unique<UseSkill::HealHp>());
	// 防御力UP
	GetSkill().SetSkill(std::make_unique<UseSkill::DefenceUp>(1.2f));
	// 攻撃力UP
	GetSkill().SetSkill(std::make_unique<UseSkill::AttackUp>(1.2f));
	
	// コリジョンの設定
	m_BoxComponent[0] = std::make_unique<BoxComponent>();
	m_BoxComponent[1] = std::make_unique<BoxComponent>();
	m_BoxComponent[2] = std::make_unique<BoxComponent>();
	m_BoxComponent[0]->SetSphere3(GetPanzer().GetBody().GetTransform(), 6.0f);
	m_BoxComponent[0]->SetAABB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 5.0f, 4.0f));
	m_BoxComponent[0]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 4.0f, 6.0f));
	m_BoxComponent[1]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(2.0f, 1.0f, 2.0f));
	m_BoxComponent[2]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(0.5f, 0.5f, 1.0f));
}

IV_H::~IV_H()
{
	Engine::Get().GetResource()->UnloadModel("IV-HBody");
	Engine::Get().GetResource()->UnloadModel("IV-HTurret");
	Engine::Get().GetResource()->UnloadModel("IV-HGun");
}

void IV_H::Begin()
{
}

void IV_H::Update()
{
	Vehicle::Update();
}

void IV_H::Event()
{
}

void IV_H::Draw()
{
	Vehicle::Draw();
#if 0 
	m_BoxComponent[0]->SystemDraw();
	m_BoxComponent[1]->SystemDraw();
	m_BoxComponent[2]->SystemDraw();
#endif
}
#pragma endregion IV号H型

Sherman::Sherman() : Vehicle("Sherman")
{
	Engine::Get().GetResource()->LoadModel("ShermanBody", "Panzer\\ShermanBody.obj");
	Engine::Get().GetResource()->LoadModel("ShermanTurret", "Panzer\\ShermanTurret.obj");
	Engine::Get().GetResource()->LoadModel("ShermanGun", "Panzer\\ShermanMainGun.obj");

	// 戦車の設定
	Vehicle::SetPanzer();
	Vehicle::SetProperty(Status::Country::US, 27.0f, 570.0f, 126.0f, 44.0f, 48.0f, 4.0f, 0.6f);

	// スキルの設定
	// たまる時間20.0f
	GetSkill().Begin(20.0f);	
	// 攻撃力UP
	GetSkill().SetSkill(std::make_unique<UseSkill::AttackUp>(1.3f));

	// コリジョンの設定
	m_BoxComponent[0] = std::make_unique<BoxComponent>();
	m_BoxComponent[1] = std::make_unique<BoxComponent>();
	m_BoxComponent[2] = std::make_unique<BoxComponent>();
	m_BoxComponent[0]->SetSphere3(GetPanzer().GetBody().GetTransform(), 6.0f);
	m_BoxComponent[0]->SetAABB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 5.0f, 4.0f));
	m_BoxComponent[0]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(4.0f, 3.0f, 5.0f));
	m_BoxComponent[1]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(2.0f, 1.0f, 2.0f));
	m_BoxComponent[2]->SetOBB3(GetPanzer().GetBody().GetTransform(), Math::Vector3(0.5f, 0.5f, 1.0f));
}

Sherman::~Sherman()
{
	Engine::Get().GetResource()->UnloadModel("Panzer\\ShermanBody.obj");
	Engine::Get().GetResource()->UnloadModel("Panzer\\ShermanTurret.obj");
	Engine::Get().GetResource()->UnloadModel("Panzer\\ShermanMainGun.obj");
}

void Sherman::Begin()
{
}

void Sherman::Update()
{
	Vehicle::Update();
}

void Sherman::Event()
{
}

void Sherman::Draw()
{
	Vehicle::Draw();
#if 0
	m_BoxComponent[0]->SystemDraw();
	m_BoxComponent[1]->SystemDraw();
	m_BoxComponent[2]->SystemDraw();
#endif
}
