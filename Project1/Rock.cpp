/*------------------------------------------------------------
	
	[Rock.cpp]
	Author : 出合翔太

-------------------------------------------------------------*/
#include "Engine.h"
#include "Application.h"
#include "Resource.h"
#include "Vehicle.h"
#include "Player.h"
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
	m_Player = Engine::Get().application()->GetScene()->GetGameObject<Player>(ELayer::LAYER_3D_ACTOR);	
}

void Rock::Update()
{
	m_Length = Math::Abs(D3DXVec3Length(&m_Transform->position()) - D3DXVec3Length(&m_Player->vehicle().bodyTransform().position()));
	if (m_Length < 50.0f)
	{
		m_DrawModelName = m_ModelName + "_03";
	}
	else if(m_Length < 100.0f)
	{
		m_DrawModelName = m_ModelName + "_02";
	}
	else
	{
		m_DrawModelName = m_ModelName + "_01";
	}
}

void Rock::Event()
{
}

void Rock::Draw()
{
	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel(m_DrawModelName);
}

void Rock::Create(const std::string & modelName, D3DXVECTOR3 pos, D3DXVECTOR3 size, float degAngle, bool onCollider)
{
	// モデルの名前
	m_ModelName = modelName;
	// 表示するモデルの名前と番号
	m_DrawModelName = m_ModelName + "_03";

	// トランスフォームの設定
	auto rotation = D3DXVECTOR3(0.0f, Math::ToRadians(degAngle), 0.0f);
	m_Transform->Set(pos, size, rotation);

	// コライダーを追加する
	if (onCollider)
	{
		m_Collider = AddComponent<Collider>();
		m_Collider->SetOBB3(*m_Transform, size);
	}
}
