/*------------------------------------------------------------
	
	[Rock.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Vehicle.h"
#include "Player.h"
#include "GameCamera.h"
#include "Rock.h"

Rock::Rock()
{
	m_Transform = AddComponent<Transform>();
}

Rock::~Rock()
{
}

void Rock::Begin()
{
	m_Player = Engine::Get().GetApplication()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);	
	m_Camera = Engine::Get().GetApplication()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
}

void Rock::Update()
{
	m_Length = Math::Abs(D3DXVec3Length(&m_Transform->GetPosition()) - D3DXVec3Length(&m_Player->GetVehicle().GetBodyTransform().GetPosition())) * m_Transform->GetScale().x * 0.5f;
	// 一番近い
	if (m_Length < 500.0f)
	{
		m_DrawModelName = m_ModelName + "_03";
	}
	// 一番遠い
	else if (m_Length > 1000.0f)
	{
		m_DrawModelName = m_ModelName + "_01";
	}
	else 
	{
		m_DrawModelName = m_ModelName + "_02";
	}
	
}

void Rock::Event()
{
}

void Rock::Draw()
{
	if (m_Camera->NotDrawObject(m_Transform->GetPosition(), m_Transform->GetScale().x)) { return; }
	
	GetResource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	GetResource().SetStaticModel(m_DrawModelName);
}

void Rock::Create(const std::string & ModelName, D3DXVECTOR3 Position, D3DXVECTOR3 Size, float DegAngle)
{
	// モデルの名前
	m_ModelName = ModelName;
	// 表示するモデルの名前と番号
	m_DrawModelName = m_ModelName + "_03";

	// トランスフォームの設定
	auto rotation = D3DXVECTOR3(0.0f, Math::ToRadians(DegAngle), 0.0f);
	m_Transform->Set(Position, Size, rotation);
}
