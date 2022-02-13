/*------------------------------------------------------------

	[vehicle.cpp]
	Author : 出合翔太

	戦車を構成するクラス

-------------------------------------------------------------*/
#include "Body.h"
#include "Turret.h"
#include "MainGun.h"
#include "Shadow.h"
#include "Vehicle.h"
#include "Fps.h"
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Graphics.h"
#include "Fence.h"

Panzer::Panzer(const std::string & PanzerTag) : m_Resource(*Engine::Get().GetResource()), m_Graphics(*Engine::Get().GetGraphics())
{
	m_Body = std::make_unique<Body>(PanzerTag);
	m_Turret = std::make_unique<Turret>(PanzerTag);
	m_Gun = std::make_unique<MainGun>(PanzerTag);
}

Panzer::~Panzer()
{
}

void Panzer::Begin()
{
	m_Body->Begin();
	m_Turret->Begin();
	m_Gun->Begin();
}

void Panzer::Update()
{
	m_Body->Update();
	m_Turret->Update();
	m_Gun->Update();
}

void Panzer::Event()
{
}

void Panzer::Draw()
{
	// マトリクスの計算
	D3DXMATRIX world;
	m_Body->UpdateMatrix(world);
	m_Turret->UpdateMatrix(m_Body->GetWorldMatrix());
	m_Gun->UpdateMatrix(m_Turret->GetWorldMatrix());
	world = m_Gun->GetWorldMatrix();
	m_Graphics.SetWorldMatrix(world);

	m_Body->Draw();
	m_Turret->Draw();
	m_Gun->Draw();
}

#pragma region getter
const Body & Panzer::GetBody() const
{
	if (!m_Body) { OutputDebugString("m_Body is nullptr\n"); }
	return *m_Body;
}

const Turret & Panzer::GetTurret() const
{
	if (!m_Turret) { OutputDebugString("m_Turret is nullptr\n"); }
	return *m_Turret;
}

const MainGun & Panzer::GetMainGun() const
{
	if (!m_Gun) { OutputDebugString("m_Gun is nullptr\n"); }
	return *m_Gun;
}
#pragma region getter