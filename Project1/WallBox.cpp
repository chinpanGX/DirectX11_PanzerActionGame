/*--------------------------------------------------------------

	[WallFence.cpp]
	Author : 出合翔太

	トレーニング用の壁

---------------------------------------------------------------*/
#include "Resource.h"
#include "Engine.h"
#include "Application.h"
#include "GameCamera.h"
#include "WallBox.h"
#include <array>

WallBox::WallBox()
{
	m_Transform = Actor::AddComponent<Transform>();
	m_Collider = Actor::AddComponent<Collider>();
}

WallBox::~WallBox()
{
}

void WallBox::Begin()
{
	
}

void WallBox::Update()
{
	Actor::UpdateCollision(*m_Collider);
}

void WallBox::Event()
{
}

void WallBox::Draw()
{
	auto camera = Engine::Get().application()->GetScene()->GetGameObject<GameCamera>(ELayer::LAYER_CAMERA);
	if (camera->NotDrawObject(m_Transform->position(), StageObject::radius()))
	{
		return;
	}

	resource().SetShader("Default");
	UpdateMatrix(*m_Transform);
	resource().SetStaticModel("WallFence");
}

void WallBox::Set(D3DXVECTOR3 Pos, D3DXVECTOR3 Size)
{
	m_Transform->Set(Pos, Size);
	m_Collider->SetOBB3(*m_Transform, m_Transform->scale());
	m_Collider->SetAABB3(*m_Transform, m_Transform->scale());
	CreatePlane();
}

void WallBox::CreatePlane()
{
	// 法線
	std::array<D3DXVECTOR3, 4> normals;
	normals[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	normals[1] = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	normals[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	normals[3] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	D3DXVECTOR3 pos = m_Transform->position();
	D3DXVECTOR3 size = m_Transform->scale();
	
	// x方向
	D3DXVECTOR3 tmp = D3DXVECTOR3(pos.x + size.x, pos.y, pos.z);
	D3DXPlaneFromPointNormal(&m_Plane[0], &tmp, &normals[0]);
	D3DXVECTOR3 tmp = D3DXVECTOR3(pos.x - size.x, pos.y, pos.z);
	D3DXPlaneFromPointNormal(&m_Plane[1], &tmp, &normals[1]);

	// z方向
	D3DXVECTOR3 tmp = D3DXVECTOR3(pos.x, pos.y, pos.z + size.z);
	D3DXPlaneFromPointNormal(&m_Plane[2], &tmp, &normals[2]);
	D3DXVECTOR3 tmp = D3DXVECTOR3(pos.x, pos.y, pos.z - size.z);
	D3DXPlaneFromPointNormal(&m_Plane[2], &tmp, &normals[3]);

}
